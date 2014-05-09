#include "item_editor.h"

#include <QFormLayout>

CQTs_ItemFirstPage::CQTs_ItemFirstPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();

    setTitle(QObject::tr("Basic information"));
    form->addRow(QObject::tr("Code:"), lineCode = new QLineEdit());
    form->addRow(QObject::tr("Name:"), lineName = new QLineEdit());
    form->addRow(QObject::tr("Weight:"), spinWeight = new QSpinBox());
    form->addRow(QObject::tr("Price (copper):"), spinPrice = new QSpinBox());
    groupType = new QGroupBox();
    QVBoxLayout *tLay = new QVBoxLayout();
    tLay->addWidget(cmdGood = new QRadioButton(QObject::tr("Good")));
    cmdGood->setChecked(true);
    tLay->addWidget(cmdWeapon = new QRadioButton(QObject::tr("Weapon")));
    tLay->addWidget(cmdArmor = new QRadioButton(QObject::tr("Armor")));
    tLay->addWidget(cmdShield = new QRadioButton(QObject::tr("Shield")));
    groupType->setLayout(tLay);
    form->addRow(QObject::tr("Type:"),groupType);
    setLayout(form);
    registerField("code*", lineCode);
    registerField("name*", lineName);
    registerField("weight", spinWeight);
    registerField("price", spinPrice);
}

int CQTs_ItemFirstPage::nextId() const{
    if(cmdWeapon->isChecked())
        return CQTs_ItemEditor::page_weap;
    if(cmdArmor->isChecked())
        return CQTs_ItemEditor::page_arm;
    if(cmdShield->isChecked())
        return CQTs_ItemEditor::page_shield;
    return CQTs_ItemEditor::page_desc;
}

CQTs_ItemWeapPage::CQTs_ItemWeapPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();
    QVBoxLayout *tLay = new QVBoxLayout();
    setTitle(QObject::tr("Weapon information"));
    form = new QFormLayout();
    setLayout(form);
    form->addRow(QObject::tr("Damage:"), lineWDamage = new QLineEdit());
    form->addRow(QObject::tr("Critical:"), lineWCritical = new QLineEdit());
    tLay = new QVBoxLayout();
    tLay->addWidget(checkWBlud = new QCheckBox(QObject::tr("Bludgeoning")));
    tLay->addWidget(checkWPier = new QCheckBox(QObject::tr("Piercing")));
    tLay->addWidget(checkWSla = new QCheckBox(QObject::tr("Slashing")));
    form->addRow(QObject::tr("Damage Type:"),tLay);
    form->addRow(QObject::tr("Range:(squares)"), spinWRange = new QSpinBox());
    tLay = new QVBoxLayout();
    tLay->addWidget(checkWThrow = new QCheckBox(QObject::tr("Thrown")));
    checkWThrow->setEnabled(false);
    tLay->addWidget(checkWProj = new QCheckBox(QObject::tr("Projectile")));
    checkWProj->setEnabled(false);
    form->addRow(QObject::tr("Rangetype:"),tLay);
    registerField("w.damage*",lineWDamage);
    registerField("w.crit*",lineWCritical);
    registerField("w.blud",checkWBlud);
    registerField("w.pier",checkWPier);
    registerField("w.slash",checkWSla);
    registerField("w.range",spinWRange);
    registerField("w.throw",checkWThrow);
    registerField("w.projectile",checkWProj);
    connect(spinWRange,SIGNAL(valueChanged(int)),this,SLOT(setRanged(int)));
}

void CQTs_ItemWeapPage::setRanged(int range){
    if(range == 0){
        checkWThrow->setEnabled(false);
        checkWProj->setEnabled(false);
    }else{
        checkWThrow->setEnabled(true);
        checkWProj->setEnabled(true);
    }
}


int CQTs_ItemWeapPage::nextId() const{
    return CQTs_ItemEditor::page_desc;
}

CQTs_ItemArmPage::CQTs_ItemArmPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();
    setTitle(QObject::tr("Armor information"));
    form = new QFormLayout();
    form->addRow(QObject::tr("AC:"),spinAAC = new QSpinBox());
    form->addRow(QObject::tr("Dex Max:"),spinADex = new QSpinBox());
    form->addRow(QObject::tr("Arcane failure:"),spinAArcane = new QSpinBox());
    spinAArcane->setRange(0,100);
    spinAArcane->setSuffix("%");
    form->addRow(QObject::tr("Check penality:"),spinAPenalty = new QSpinBox());
    spinAPenalty->setRange(-50,0);
    form->addRow(QObject::tr("Type:"),comboAType = new QComboBox());
    comboAType->addItem(QObject::tr("Light"));
    comboAType->addItem(QObject::tr("Medium"));
    comboAType->addItem(QObject::tr("Heavy"));
    setLayout(form);
}

int CQTs_ItemArmPage::nextId() const{
    return CQTs_ItemEditor::page_desc;
}
CQTs_ItemShieldPage::CQTs_ItemShieldPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();
    setTitle(QObject::tr("Shield information"));
    form = new QFormLayout();
    form->addRow(QObject::tr("AC:"),spinSAC = new QSpinBox());
    form->addRow(QObject::tr("Dex Max(-1 if none):"),spinSDex = new QSpinBox());
    spinSDex->setMinimum(-1);
    spinSDex->setValue(-1);
    form->addRow(QObject::tr("Arcane failure:"),spinSArcane = new QSpinBox());
    spinSArcane->setRange(0,100);
    spinSArcane->setSuffix("%");
    form->addRow(QObject::tr("Check penality:"),spinSPenalty = new QSpinBox());
    spinSPenalty->setRange(-50,0);
    setLayout(form);
}

int CQTs_ItemShieldPage::nextId() const{
    return CQTs_ItemEditor::page_desc;
}

CQTs_ItemDescPage::CQTs_ItemDescPage(QWidget *parent):
    QWizardPage(parent)
{
    QVBoxLayout *tLay = new QVBoxLayout();
    setTitle(QObject::tr("Description"));
    setSubTitle(QObject::tr("Leave blank if you don't want it"));
    tLay = new QVBoxLayout();
    setLayout(tLay);
    tLay->addWidget(textDescription = new QTextEdit());
}




CQTs_ItemEditor::CQTs_ItemEditor(QWidget *parent):
    QWizard(parent)
{
    //Basic info
    setPage(page_intro,new CQTs_ItemFirstPage());
    //Basic

    //Weapon info
    setPage(page_weap,new CQTs_ItemWeapPage());
    //Weapon

    //Armor info
    setPage(page_arm,new CQTs_ItemArmPage());
    //Armor

    //Shield info
    setPage(page_shield,new CQTs_ItemShieldPage());
    //Shield

    //description
    setPage(page_desc,new CQTs_ItemDescPage());
    //Description

    setStartId(page_intro);
}



