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

class CQTs_item{
public:
    CQTs_item(QString mycode,QString mytype ,QString myname,double myweight, money myprice);
    CQTs_item(QString mycode,QString mytype,QString myname,double myweight, int mcu, int mag, int mau, int mpt = 0);
    money cost();
    double myWeigh();
    QString myID();
    QString myName();
    CQTs_item& operator = (CQTs_item);
    bool operator ==(CQTs_item otherItem);
    bool operator ==(QString otherCode);
    bool operator <(CQTs_item otherItem);//alphabetical order per name
private:
    QString code, name, type;
    double weight;//, volume;
    money price;

};


class CQTs_itemsHandler : public QObject
{
    Q_OBJECT
public:
    explicit CQTs_itemsHandler(QStringList filesData, QStringList filesNames, QObject *parent = 0);
    void loadFromFile(QStringList filenames);
    void loadNamesFromFiles(QStringList filenames);
signals:

public slots:

private:
    QList<CQTs_item> items;
};
#include <QWidget>
class CQTs_ItemViewer : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ItemViewer(QWidget *parent = 0);
private:
    //QLabel *LabName,*LabBAB,*LabFort,*LabRef,*LabWill;
    CQTs_itemsHandler *itemsHandler;
    //void initialize();
signals:

public slots:
  //  void setLabs(CQTs_Class *selected);
};


#endif // ITEMS_H
