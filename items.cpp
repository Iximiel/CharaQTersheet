#include "items.h"
#include <QtCore>

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

QDataStream& operator <<(QDataStream& stream, money val){
    QString gp = QObject::tr("gp"), sp = QObject::tr("sp"), cc = QObject::tr("cc");
    int mcu, mag, mau;
    mau = val.cu/100.;
    mag = (val.cu-mau*100)/10.;
    mcu = (val.cu-mau*100-mag*10);
    if(mcu!=0){
        if(mau!=0)
            stream << mau << " "<< gp <<" " << mag << " " <<sp<<" ";
        else if (mag!=0)
            stream << mag << " " <<sp<<" ";
        stream << mcu << " "<<cc;
    }else if (mag!=0){
        if(mau!=0)
            stream << mau << " "<< gp <<" ";
        stream << mag << " " <<sp;
    }else{
        stream << mau << " "<< gp;
    }
    return stream;
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
bool cqts_item::operator <(cqts_item otherItem){
    return name<otherItem.name;
}//alphabetical order per name

cqts_itemHandler::cqts_itemHandler(QObject *parent) :
    QObject(parent)
{
}
