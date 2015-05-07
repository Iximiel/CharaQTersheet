#ifndef CLASSCREATOR_H
#define CLASSCREATOR_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include "cqts_engine.h"

class CQTs_ClassEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ClassEditor(CQTs_engine *eng,QWidget *parent = 0);
    explicit CQTs_ClassEditor(CQTs_Class oldclass,CQTs_engine *eng,QWidget *parent = 0);
private:
    void initialize();
    CQTs_engine *engine;
    CQTs_Class myclass;
    QLineEdit *Line_Name;
    QComboBox *Combo_HD, *Combo_BaB, *Combo_Ranks, *Combo_TSFort, *Combo_TSRef, *Combo_TSWill;
    QPushButton *BT_Weapon, *BT_Armor, *BT_Skills;
signals:

public slots:
};

#endif // CLASSCREATOR_H

#ifndef CLASSSPECIALCREATOR_H
#define CLASSSPECIALCREATOR_H

#include <QWidget>

class CQTs_ClassSpecialEdit : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ClassSpecialEdit(QWidget *parent = 0);

signals:

public slots:
};

#endif // CLASSSPECIALCREATOR_H