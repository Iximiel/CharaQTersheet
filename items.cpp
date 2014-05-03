#include "items.h"

bool money::operator <(money x){
    int I, X;
    X = x.cu+(x.ag+(x.au+x.pt*10)*10)*10;
    I = cu+(ag+(au+pt*10)*10)*10;
    return I<X;
}

cqts_itemHandler::cqts_itemHandler(QObject *parent) :
    QObject(parent)
{
}
