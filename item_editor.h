#ifndef ITEM_EDITOR_H
#define ITEM_EDITOR_H

#include "items.h"

#include <QWizard>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QWizard>
#include <QWizardPage>
#include <QCheckBox>
#include <QCommandLinkButton>

class CQTs_ItemFirstPage : public QWizardPage{
    Q_OBJECT
public:
    CQTs_ItemFirstPage(QWidget *parent =0);
    int nextId();
private:
    int next;
    QLineEdit *lineCode, *lineName;
    QSpinBox *spinWeight,*spinPrice, *spinWRange;
    QComboBox *comboType;
    QCommandLinkButton *cmdGood, *cmdWeapon, *cmdArmor, *cmdShield;
public slots:
    void openWeapon();
    void openArmor();
    void openShield();
    void openDescription();
};

class CQTs_ItemWeapPage : public QWizardPage{
    Q_OBJECT
public:
    CQTs_ItemWeapPage(QWidget *parent =0);
private:
    QLineEdit *lineWDamage, *lineWCritical;
    QSpinBox *spinWRange;
    QComboBox *comboType;
    QCheckBox *checkWBlud, *checkWPier, *checkWSla, *checkWThrow, *checkWProj;
};

class CQTs_ItemArmPage : public QWizardPage{
    Q_OBJECT
public:
    CQTs_ItemArmPage(QWidget *parent =0);
private:
    QSpinBox *spinAAC, *spinADex, *spinAArcane, *spinAPenalty;
    QComboBox *comboAType;
    QCheckBox *checkAWeapon;
};

class CQTs_ItemShieldPage : public QWizardPage{
    Q_OBJECT
public:
    CQTs_ItemShieldPage(QWidget *parent =0);
private:
    QSpinBox *spinSAC, *spinSDex, *spinSArcane, *spinSPenalty;
    QCheckBox *checkSWeapon;

};

class CQTs_ItemDescPage : public QWizardPage{
    Q_OBJECT
public:
    CQTs_ItemDescPage(QWidget *parent =0);
private:
    QTextEdit *textDescription;

};


class CQTs_ItemEditor : public QWizard
{
    Q_OBJECT
public:
    explicit CQTs_ItemEditor(QWidget *parent = 0);//newItem
    enum {page_intro, page_weap, page_arm, page_shield, page_desc, page_confirm};
    //explicit CQTs_ItemEditor(CQTs_item oldItem, QWidget *parent = 0);//modify Item
private:
    QLineEdit *lineCode, *lineName, *lineWDamage, *lineWCritical;
    QSpinBox *spinWeight,*spinPrice, *spinWRange, *spinAAC, *spinADex, *spinAArcane, *spinAPenalty;
    QSpinBox *spinSAC, *spinSDex, *spinSArcane, *spinSPenalty;
    QComboBox *comboType, *comboAType;
    QCheckBox *checkWBlud, *checkWPier, *checkWSla, *checkWThrow, *checkWProj, *checkAWeapon, *checkSWeapon;
    QTextEdit *textDescription;
    QCommandLinkButton *cmdGood, *cmdWeapon, *cmdArmor, *cmdShield;
signals:
    void thisItem(CQTs_item);
};

#endif // ITEM_EDITOR_H
