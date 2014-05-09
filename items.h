#ifndef ITEMS_H
#define ITEMS_H
#include <QString>
#include <QObject>
#include <QList>
#include <QXmlStreamWriter>

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
    CQTs_item();
    CQTs_item(QString mycode,QString mytype="" ,QString myname="" ,double myweight=0, money myprice=0);
    CQTs_item(QString mycode,QString mytype,QString myname,double myweight, int mcu, int mag, int mau, int mpt = 0);
    money cost();
    double myWeigh();
    QString myID();
    QString myName();
    void set_cost(money newPrice);
    void set_myWeigh(double newWeight);
    void set_myID(QString newCode);
    void set_myName(QString newName);

    CQTs_item& operator = (CQTs_item);
    bool operator ==(CQTs_item otherItem);
    bool operator ==(QString otherCode);
    bool operator <(CQTs_item otherItem);//alphabetical order per name

    //load write A SINGLE item
    //static void write_item(QXmlStreamWriter& xmlstream,CQTs_item itemtoadd);
    static CQTs_item read_Item(QXmlStreamReader &xmlstream);
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
    int itemsNum();
    QString getName(int i);
    QString getCost(int i);
    double getWeight(int i);
    CQTs_item getItem(int i);
signals:

public slots:

private:
    QList<CQTs_item> items;
};

#include <QScrollArea>
#include <QTabWidget>
#include <QLayout>
#include <QLabel>
#include <QWidget>

class CQTs_bag : public QWidget
{
    Q_OBJECT
public:
    CQTs_bag(CQTs_item myID, QWidget *parent=0);
    void update(int from);
    void uptateWeight();
    double totalWeight();
    //QList<CQTs_item> look_weapons();
    //QList<CQTs_item> look_goods();
    //QList<CQTs_item> look_armors();
public slots:
    void put_inside(CQTs_item newItem);
    void put_inside(QList<CQTs_item> newItems);//adds a list of items
private:
    CQTs_item bagID;
    //QTabWidget *tabPockets;
    QLabel *labTotalWeight;
    QList<CQTs_item> inside;
    QScrollArea *ScrollMain;
    QGridLayout *itemgrid;
};

#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

class CQTs_ItemEditor : public QTabWidget
{
    Q_OBJECT
public:
    explicit CQTs_ItemEditor(QWidget *parent = 0);
private:
    int IDweapon, IDarmor, IDshield;
    QLineEdit *lineCode, *lineName, *lineWDamage, *lineWCritical;
    QSpinBox *spinWeight,*spinPrice, *spinWRange, *spinAAC, *spinADex, *spinAArcane, *spinAPenalty;
    QSpinBox *spinSAC, *spinSDex, *spinSArcane, *spinSPenalty;
    QComboBox *comboType, *comboAType;
    QCheckBox *checkWBlud, *checkWPier, *checkWSla, *checkWThrow, *checkWProj, *checkAWeapon, *checkSWeapon;
    QTextEdit *textDescription;
signals:
    void thisItem(CQTs_item);
public slots:
    void openTab(int ID);
    void alsoWeapon(bool yes);
};

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
