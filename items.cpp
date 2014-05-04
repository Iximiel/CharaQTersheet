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
money::money(int mau){
    cu = mau*100;
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

cqts_itemsHandler::cqts_itemsHandler(QString filename, QObject *parent) :
    QObject(parent)
{
    loadFromFile(filename);
}

void cqts_itemsHandler::loadFromFile(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0, QString("Information"), QString(tr("Failed to load items")), QMessageBox::Ok);
    }else{
        QXmlStreamReader xml(&file);

    }
}
