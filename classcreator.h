#ifndef CLASSCREATOR_H
#define CLASSCREATOR_H

#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include "cqts_engine.h"

class CQTs_SkillSelector : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_SkillSelector(CQTs_engine *eng,QWidget *parent = 0);
private:
    CQTs_engine *engine;
signals:

public slots:
};

class CQTs_ClassEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ClassEditor(CQTs_engine *eng,QWidget *parent = 0);
    explicit CQTs_ClassEditor(CQTs_Class oldclass,CQTs_engine *eng,QWidget *parent = 0);
    void setLabels(CQTs_Class oldclass);
private:
    void initialize(CQTs_engine *eng);
    CQTs_Class myClass;
    CQTs_engine *engine;
    QLineEdit *Line_Name;
    QComboBox *Combo_HD, *Combo_BaB, *Combo_Ranks, *Combo_TSFort, *Combo_TSRef, *Combo_TSWill;
    QPushButton *BT_Weapon, *BT_Armor, *BT_Skills;
    CQTs_SkillSelector *SkillSelector;
signals:
    void getClass(CQTs_Class editedclass);
public slots:
    void launchSkillSelector();
    /*void launchArmorSelector();
    void launchWeaponSelector();*/
    void saveAndExit();
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
