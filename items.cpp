#include "items.h"

#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

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
money& money::operator =(money& x){
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

cqts_item::cqts_item(QString mycode,QString myname,double myweight, money myprice){
    code = mycode;
    name = myname;
    weight = myweight;
    price = myprice;
}
cqts_item::cqts_item(QString mycode,QString myname,double myweight, int mcu, int mag, int mau, int mpt){
    code = mycode;
    name = myname;
    weight = myweight;
    money tprice(mcu, mag, mau, mpt);
    price = tprice;
}
money cqts_item::cost(){return price;}
double cqts_item::myWeigh(){return weight;}
QString cqts_item::myID(){return code;}
QString cqts_item::myName(){return name;}
bool cqts_item::operator ==(cqts_item otherItem){
    return code == otherItem.code;
}
bool cqts_item::operator ==(QString otherCode){
    return code == otherCode;
}
bool cqts_item::operator <(cqts_item otherItem){//alphabetical order per name
    return name<otherItem.name;
}

cqts_itemsHandler::cqts_itemsHandler(QStringList filesData, QStringList filesNames, QObject *parent) :
    QObject(parent)
{
    loadFromFile(filesData);
    loadNamesFromFiles(filesNames);
}

void cqts_itemsHandler::loadFromFile(QStringList filesData){
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
                QString code, engname, type;
                double weight;
                money prize;
                if(xml.name()=="item"&&xml.isStartElement()){
                    code = xml.attributes().value("code").toString();
                    engname = xml.attributes().value("engname").toString();
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
                            if(change == "sylver")
                                mult = 10;
                            else if(change == "copper")
                                mult = 1;
                            while(!xml.readNext()==6);
                            prize = mult * (xml.text().toInt());
                        }
                        if(type == "weapon"){


                        }
                }
                }
                xml.readNext();
            }

        }
    }
}

void cqts_itemsHandler::loadNamesFromFiles(QStringList filesNames){
    for (int i = 0; i < filesNames.size(); ++i) {
        QFile file(filesNames[i]);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::information(0, QString("Information"), (QString(tr("Failed to load item names from "))+filesNames[i]), QMessageBox::Ok);
        }else{
            QXmlStreamReader xml(&file);

        }
    }
}
