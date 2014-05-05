#ifndef ITEMS_H
#define ITEMS_H
#include <QString>
#include <QObject>
#include <QList>

struct money{
    money();
    money(int mcu, int mag=0, int mau=0, int mpt=0);
    int cu;
    money operator +(money);
    money operator -(money);
    bool operator <(money);
    money& operator =(money);
    money& operator =(int x);
    QString value();
};

class cqts_item{
public:
    cqts_item(QString mycode,QString mytype ,QString myname,double myweight, money myprice);
    cqts_item(QString mycode,QString mytype,QString myname,double myweight, int mcu, int mag, int mau, int mpt = 0);
    money cost();
    double myWeigh();
    QString myID();
    QString myName();
    cqts_item& operator = (cqts_item);
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
    explicit cqts_itemsHandler(QStringList filesData, QStringList filesNames, QObject *parent = 0);
    void loadFromFile(QStringList filenames);
    void loadNamesFromFiles(QStringList filenames);
signals:

public slots:

private:
    QList<cqts_item> items;
};

#endif // ITEMS_H
