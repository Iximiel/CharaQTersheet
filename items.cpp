#include "items.h"

#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <QLayout>
#include <QGridLayout>


#include <QDebug>
//money
money::money(){
    cu=0;
}

money::money(int mcu, int mag, int mau, int mpt){
    cu = mcu+mag*10+mau*100+mpt*1000;
}

bool money::operator <(money x){
    return cu<x.cu;
}

money money::operator +(money x){
    cu = cu+x.cu;
    return *this;
}
money money::operator -(money x){
    cu = cu-x.cu;
    return *this;
}
money& money::operator =(money x){
    if(this!= &x){
        cu = x.cu;
    }
    return *this;
}

money& money::operator =(int x){
    cu = x;
    return *this;
}

QString money::value(){
    QString toreturn="";
    QString gp = QObject::tr("gp"), sp = QObject::tr("sp"), cc = QObject::tr("cc");
    int Mcu, Mag, Mau;
    Mau = cu/100.;
    Mag = (cu-Mau*100)/10.;
    Mcu = (cu-Mau*100-Mag*10);
    QString mau = QString::number(Mau),mag = QString::number(Mag),mcu = QString::number(Mcu);
    if(Mcu!=0){
        if(Mau!=0)
            toreturn += mau + " "+ gp +" " + mag + " " + sp + " ";
        else if (Mag!=0)
            toreturn += mag + " " + sp + " ";
        toreturn += mcu + " "+cc;
    }else if (Mag!=0){
        if(Mau!=0)
            toreturn += mau + " " + gp + " ";
        toreturn += mag + " " + sp;
    }else{
        toreturn += mau + " "+ gp;
    }
    return toreturn;
}

//item

CQTs_item::CQTs_item(){
    code = "";
    type = "";
    name = "";
    weight = 0;
    price = 0;
}

CQTs_item::CQTs_item(QString mycode,QString mytype,QString myname,double myweight, money myprice){
    code = mycode;
    type = mytype;
    name = myname;
    weight = myweight;
    price = myprice;
}
CQTs_item::CQTs_item(QString mycode,QString mytype,QString myname,double myweight, int mcu, int mag, int mau, int mpt){
    code = mycode;
    type = mytype;
    name = myname;
    weight = myweight;
    money tprice(mcu, mag, mau, mpt);
    price = tprice;
}

money CQTs_item::cost(){return price;}
double CQTs_item::myWeigh(){return weight;}
QString CQTs_item::myID(){return code;}
QString CQTs_item::myName(){return name;}

void CQTs_item::set_cost(money newPrice){price = newPrice;}
void CQTs_item::set_myWeigh(double newWeight){weight = newWeight;}
void CQTs_item::set_myID(QString newCode){code = newCode;}
void CQTs_item::set_myName(QString newName){name = newName;}

CQTs_item& CQTs_item::operator = (CQTs_item x){
    if(this!= &x){
        code = x.code;
        name = x.name;
        type = x.type;
        weight = x.weight;
        price = x.price;

    }
    return *this;
}

bool CQTs_item::operator ==(CQTs_item otherItem){
    return code == otherItem.code;
}
bool CQTs_item::operator ==(QString otherCode){
    return code == otherCode;
}
bool CQTs_item::operator <(CQTs_item otherItem){//alphabetical order per name
    return name<otherItem.name;
}

CQTs_itemsHandler::CQTs_itemsHandler(QStringList filesData, QStringList filesNames, QObject *parent) :
    QObject(parent)
{
    loadFromFile(filesData);
    loadNamesFromFiles(filesNames);
}

void CQTs_itemsHandler::loadFromFile(QStringList filesData){
    for (int i = 0; i < filesData.size(); ++i) {
        QFile file(filesData[i]);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::information(0, QString("Information"), (QString(tr("Failed to load items from "))+filesData[i]), QMessageBox::Ok);
        }else{
            QXmlStreamReader xml(&file);
            while(!(xml.name()=="items"&&xml.isStartElement())){
                xml.readNext();
            }

            while(!(xml.name()=="items"&&xml.isEndElement())){
                QString code, type;
                double weight=0;
                money prize;
                if(xml.name()=="item"&&xml.isStartElement()){
                    code = xml.attributes().value("code").toString();
                    type = xml.attributes().value("type").toString();
                    while(!(xml.name()=="item"&&xml.isEndElement())){
                        xml.readNext();
                        if(xml.name()=="weight"&&xml.isStartElement()){
                            while(!xml.readNext()==6);
                            weight= (xml.text().toDouble());
                        }
                        if(xml.name()=="price"&&xml.isStartElement()){
                            QString change = xml.attributes().value("money").toString();
                            //if is "sylver" or "copper" change the thing
                            int mult = 100;
                            if(change == "sp")
                                mult = 10;
                            else if(change == "cp")
                                mult = 1;
                            while(!xml.readNext()==6);
                            prize = mult * (xml.text().toInt());
                        }//type should be like "maintypesecondarytypespecifications" likw "weapon2h" or "armorweaponmagic"
                        /*if(type.contains("weapon")){//i will use "weapon1h", "weapon2h", "weapon2hrng", or "weaponarmor" for spiked things
                            if(xml.name()=="weapon"&&xml.isStartElement()){
                                //QString wptype = xml.attributes().value("wptype").toString();
                                QString damage = xml.attributes().value("damage").toString();
                                QString crit = xml.attributes().value("critical").toString();
                                if(type.contains("rng"))
                                    int range = xml.attributes().value("rangeinc").toInt();;//number of squares (translation friendly! :) )
                            }

                        }
                        if(type.contains("armor")){
                            if(xml.name()=="armor"&&xml.isStartElement()){
                                int AC =  xml.attributes().value("AC").toInt();
                                int dex =  xml.attributes().value("dexmax").toInt();
                                int arcanefail =  xml.attributes().value("arcane").toInt();
                                int armorcheck =  xml.attributes().value("checkpenalty").toInt();
                                bool limitspeed =  xml.attributes().value("speed").toInt();

                            }
                        }
                        if(type.contains("shield")){
                            if(xml.name()=="shield"&&xml.isStartElement()){
                                int AC =  xml.attributes().value("AC").toInt();
                                int dex =  xml.attributes().value("dexmax").toInt();
                                int arcanefail =  xml.attributes().value("arcane").toInt();
                                int armorcheck =  xml.attributes().value("checkpenalty").toInt();
                            }
                        }*/
                    }
                    CQTs_item tItem(code,type,code,weight,prize);
                    items.append(tItem);
                }
                xml.readNext();
                if(xml.hasError()){
                    qDebug() <<xml.errorString();
                    qDebug() << xml.lineNumber() << xml.columnNumber();
                    break;
                }
            }
        }
    }
}


void CQTs_itemsHandler::loadNamesFromFiles(QStringList filesNames){
    for (int i = 0; i < filesNames.size(); ++i) {
        QFile file(filesNames[i]);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::information(0, QString("Information"), (QString(tr("Failed to load item names from "))+filesNames[i]), QMessageBox::Ok);
        }else{
            QXmlStreamReader xml(&file);

        }
    }
}

int CQTs_itemsHandler::itemsNum(){return items.size();}
QString CQTs_itemsHandler::getName(int i){
    if(i> items.size())
        return "error";
    return items[i].myName();}
QString CQTs_itemsHandler::getCost(int i){
    if(i> items.size())
        return "-1";
    return items[i].cost().value();}
double CQTs_itemsHandler::getWeight(int i){
    if(i> items.size())
        return 0.;
    return items[i].myWeigh();}
CQTs_item CQTs_itemsHandler::getItem(int i){
    if(i> items.size())
        return CQTs_item("error");
    return items[i];
}

//bag thinked to be used by a pg

CQTs_bag::CQTs_bag(CQTs_item myID, QWidget *parent):
    QWidget(parent)
{
    bagID = myID;
    setWindowTitle(bagID.myName());

    QVBoxLayout *mainLay = new QVBoxLayout();
    setLayout(mainLay);

    QWidget *tWidget = new QWidget ();

    ScrollMain =  new QScrollArea();
    /*
    tabPockets = new QTabWidget();
    tabPockets->addTab(ScrollMain,"Bag");
    mainLay->addWidget(tabPockets);
    */
    mainLay->addWidget(ScrollMain);
    itemgrid = new QGridLayout();
    itemgrid->addWidget(new QLabel("Names"),0,0);
    itemgrid->addWidget(new QLabel("Weights"),0,1);
    tWidget->setLayout(itemgrid);
    ScrollMain->setWidget(tWidget);
    ScrollMain->setWidgetResizable(true);
    QLayout *tLay = new QHBoxLayout();

    tLay ->addWidget(new QLabel("Weight inside:"));
    tLay ->addWidget(labTotalWeight = new QLabel("0"));
    mainLay->addLayout(tLay);
}

void CQTs_bag::put_inside(CQTs_item newItem){
    if(!(newItem =="error")){
        int from = inside.size();
        while(inside.contains(newItem)){//"protection" from copies
            newItem.set_myName(newItem.myName()+"*"); //the * is temporary
            newItem.set_myID(newItem.myID()+"*");
        }
        inside.append(newItem);
        update(from);
    }
}

void CQTs_bag::put_inside(QList<CQTs_item> newItems){
    int from = inside.size();
    inside.append(newItems);
    update(from);
}

void CQTs_bag::update(int from){
    for (int i = from; i < inside.size(); ++i) {
        itemgrid->addWidget(new QLabel(inside[i].myName()),i+1,0);
        itemgrid->addWidget(new QLabel(QString::number(inside[i].myWeigh())),i+1,1);
    }
    uptateWeight();
}

double CQTs_bag::totalWeight(){
    double newWeight = 0;
    for (int i = 0; i < inside.size(); ++i) {
        newWeight+=inside[i].myWeigh();
    }
    return newWeight;
}

void CQTs_bag::uptateWeight(){
    labTotalWeight->setNum(totalWeight());
}

//item editor
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
CQTs_ItemEditor::CQTs_ItemEditor(QWidget *parent):
    QTabWidget(parent)
{
    QFormLayout *form = new QFormLayout();
    QWidget *tWidget = new QWidget();//Basic info
    form->addRow("Code:", new QLineEdit());
    form->addRow("Name:", new QLineEdit());
    form->addRow("Weight:", new QSpinBox());
    form->addRow("Price (copper):", new QSpinBox());
    form->addRow("Type:",new QComboBox());
    tWidget->setLayout(form);
    addTab(tWidget,"Basic");
    //Basic
    tWidget = new QWidget();//Weapon info
    form = new QFormLayout();
    tWidget->setLayout(form);
    form->addRow("Damage:",new QLineEdit());
    form->addRow("Critical:",new QLineEdit());
    form->addRow("Range:",new QLineEdit());
    form->addRow("Rangetype:",new QComboBox());
    IDweapon = addTab(tWidget,"Weapon");
    //setTabEnabled(IDweapon,false);

    //Weapon
    tWidget = new QWidget();//Armor info
    IDarmor = addTab(tWidget,"Armor");
    form = new QFormLayout();
    tWidget->setLayout(form);
    //setTabEnabled(IDarmor,false);

    //Armor
    tWidget = new QWidget();//Shield info
    IDshield = addTab(tWidget,"Shield");
    form = new QFormLayout();
    tWidget->setLayout(form);
    //setTabEnabled(IDshield,false);

    //Shield
    QTextEdit *textDescription = new QTextEdit();//description
    addTab(textDescription,"Description");
    //Description

}

//viewer thinked to show ALL the items in a itemhandler

CQTs_ItemViewer::CQTs_ItemViewer(QWidget *parent):
    QWidget(parent)
{
    QScrollArea *Scroll =  new QScrollArea();
    QLayout *tlay = new QHBoxLayout();
    tlay->addWidget(Scroll);
    setLayout(tlay);
    QStringList Items, Names;
    Items.push_back("E:/Users/Iximiel/Documents/GitHub/CharaQTersheet-MinGW/goods.xml");
    itemsHandler = new CQTs_itemsHandler(Items,Names);
    QWidget *toScroll = new QWidget();
    QGridLayout *grid = new QGridLayout();
    int row = 0;//number of row for legend
    for (int i = 0; i < itemsHandler->itemsNum(); ++i) {
        QLabel* tLab = new QLabel(itemsHandler->getName(i));
        tLab->setMaximumHeight(15);
        grid->addWidget(tLab,i+row,0);
        tLab = new QLabel(itemsHandler->getCost(i));
        grid->addWidget(tLab,i+row,1);
        tLab = new QLabel(QString::number(itemsHandler->getWeight(i)));
        grid->addWidget(tLab,i+row,2);
    }
    toScroll->setLayout(grid);
    Scroll->setWidget(toScroll);
    Scroll->setWidgetResizable(true);

}
