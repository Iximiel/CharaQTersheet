#ifndef ITEMS_H
#define ITEMS_H
#include <QString>
#include <QObject>
struct money{
    money();
    money(int mcu, int mag, int mau, int mpt=0);
    money(int mau);
    int cu;
    friend QDataStream& operator <<(QDataStream& stream, money val);
    money operator +(money);
    money operator -(money);
    bool operator <(money);
    money &operator =(money &);
};

class cqts_item{
public:
    cqts_item(QString mycode,QString myname,double myweight, money myprice);
    cqts_item(QString mycode,QString myname,double myweight, int mcu, int mag, int mau, int mpt = 0);
    money cost();
    double myWeigh();
    QString myID();
    QString myName();
    bool operator ==(cqts_item otherItem);
    bool operator ==(QString otherCode);
    bool operator <(cqts_item otherItem);//alphabetical order per name
private:
    QString code, name;
    double weight;//, volume;
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
