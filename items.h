#ifndef ITEMS_H
#define ITEMS_H
#include <QString>
#include <QObject>
#include <QList>

struct money{
    money();
    money(int mcu, int mag, int mau, int mpt=0);
    money(int mau);
    int cu;
    money operator +(money);
    money operator -(money);
    bool operator <(money);
    money &operator =(money &);
    QString value();
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
    QString code, name, type;
    double weight;//, volume;
    money price;

};


class cqts_itemsHandler : public QObject
{
    Q_OBJECT
public:
    explicit cqts_itemsHandler(QString filename, QObject *parent = 0);
    void loadFromFile(QString filename);
signals:

public slots:

private:
    QList<cqts_item> items;
};

#endif // ITEMS_H
