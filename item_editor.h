#ifndef ITEM_EDITOR_H
#define ITEM_EDITOR_H

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

};


class CQTs_ItemEditor : public QWizard
{
    Q_OBJECT
public:
    explicit CQTs_ItemEditor(QWidget *parent = 0);//newItem
    //explicit CQTs_ItemEditor(CQTs_item oldItem, QWidget *parent = 0);//modify Item
private:
    enum {page_intro, page_weap, page_arm, page_shield, page_desc, page_confirm};
    QLineEdit *lineCode, *lineName, *lineWDamage, *lineWCritical;
    QSpinBox *spinWeight,*spinPrice, *spinWRange, *spinAAC, *spinADex, *spinAArcane, *spinAPenalty;
    QSpinBox *spinSAC, *spinSDex, *spinSArcane, *spinSPenalty;
    QComboBox *comboType, *comboAType;
    QCheckBox *checkWBlud, *checkWPier, *checkWSla, *checkWThrow, *checkWProj, *checkAWeapon, *checkSWeapon;
    QTextEdit *textDescription;
    QCommandLinkButton *cmdGood, *cmdWeapon, *cmdArmor, *cmdShield;
signals:
    void thisItem(CQTs_item);
public slots:
    void openWeapon();
    void openArmor();
    void openShield();
    void openDescription();
};

#endif // ITEM_EDITOR_H
