#ifndef ITEMS_H
#define ITEMS_H

#include <QObject>
struct money{
    money(int mcu, int mag, int mau, int mpt=0);
    money(int mau);
    int cu;
    friend QDataStream& operator <<(QDataStream& stream, money val);
    money operator +(money);
    money operator -(money);
    bool operator <(money);
};

class cqts_item{
public:
    cqts_item(QString mycode,QString myname,int myweight, money myprice);
    cqts_item(QString mycode,QString myname,int myweight, int mcu, int mag, int mau, int mpt);
    money cost();
    int myWeigh();
    QString myID();
    QString myName();
    bool operator ==(cqts_item otherItem);
    bool operator ==(QString otherCode);
    bool operator <(cqts_item otherItem);//alphabetical order per name
private:
    QString code, name;
    int weight;//, volume;
    money price;
};


class cqts_itemHandler : public QObject
{
    Q_OBJECT
public:
    explicit cqts_itemHandler(QObject *parent = 0);

signals:

public slots:

};

#endif // ITEMS_H
