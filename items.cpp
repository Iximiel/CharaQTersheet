#include "items.h"

//money
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
    money toreturn;
    toreturn.cu = cu+x.cu;
    return toreturn;
}
money money::operator -(money x){
    money toreturn;
    toreturn.cu = cu-x.cu;
    return toreturn;
}
money& money::operator =(money& x){
    if(this!= &x){
    cu = x.cu;
    }
    return *this;
}

QDataStream& operator <<(QDataStream& stream, money val){
    int mcu, mag, mau;
    mau = val.cu/100.;
    mag = (val.cu-mau*100)/10.;
    mcu = (val.cu-mau*100-mag*10);
    if(mcu!=0){
        if(mau!=0)
            stream << mau << tr(" gp ") << mag << tr(" sp ");
        else if (mag!=0)
            stream << mag << tr(" sp ");
        stream << mcu << tr(" cc");
    }else if (mag!=0){
        if(mau!=0)
            stream << mau << tr(" gp ");
        stream << mag << tr(" sp");
    }else{
        stream << mau << tr(" gp");
    }
    return stream;
}

//item

cqts_item::cqts_item(QString mycode,QString myname,int myweight, money myprice){}
cqts_item::cqts_item(QString mycode,QString myname,int myweight, int mcu, int mag, int mau, int mpt){}
money cqts_item::cost(){}
int cqts_item::myWeigh(){}
QString cqts_item::myID(){}
QString cqts_item::myName(){}
bool cqts_item::operator ==(cqts_item otherItem){}
bool cqts_item::operator ==(QString otherCode){}
bool cqts_item::operator <(cqts_item otherItem){}//alphabetical order per name

cqts_itemHandler::cqts_itemHandler(QObject *parent) :
    QObject(parent)
{
}
