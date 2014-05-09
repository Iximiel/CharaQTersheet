#include "item_editor.h"

#include <QFormLayout>

CQTs_ItemFirstPage::CQTs_ItemFirstPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();
    form->addRow("Code:", lineCode = new QLineEdit());
    form->addRow("Name:", lineName = new QLineEdit());
    form->addRow("Weight:", spinWeight = new QSpinBox());
    form->addRow("Price (copper):", spinPrice = new QSpinBox());
    groupType = new QGroupBox();
    QVBoxLayout *tLay = new QVBoxLayout();
    tLay->addWidget(cmdGood = new QRadioButton("Good"));
    cmdGood->setChecked(true);
    tLay->addWidget(cmdWeapon = new QRadioButton("Weapon"));
    tLay->addWidget(cmdArmor = new QRadioButton("Armor"));
    tLay->addWidget(cmdShield = new QRadioButton("Shield"));
    groupType->setLayout(tLay);
    form->addRow("Type:",groupType);
    setLayout(form);
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

    form = new QFormLayout();
    setLayout(form);
    form->addRow("Damage:", lineWDamage = new QLineEdit());
    form->addRow("Critical:", lineWCritical = new QLineEdit());
    tLay = new QVBoxLayout();
    tLay->addWidget(checkWBlud = new QCheckBox("Bludgeoning"));
    tLay->addWidget(checkWPier = new QCheckBox("Piercing"));
    tLay->addWidget(checkWSla = new QCheckBox("Slashing"));
    form->addRow("Damage Type:",tLay);
    form->addRow("Range:(squares)", spinWRange = new QSpinBox());
    tLay = new QVBoxLayout();
    tLay->addWidget(checkWThrow = new QCheckBox("Thrown"));
    tLay->addWidget(checkWProj = new QCheckBox("Projectile"));
    form->addRow("Rangetype:",tLay);
}

int CQTs_ItemWeapPage::nextId() const{
    return CQTs_ItemEditor::page_desc;
}

CQTs_ItemArmPage::CQTs_ItemArmPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();
    form = new QFormLayout();
    form->addRow("AC:",spinAAC = new QSpinBox());
    form->addRow("Dex Max:",spinADex = new QSpinBox());
    form->addRow("Arcane failure:",spinAArcane = new QSpinBox());
    spinAArcane->setRange(0,100);
    spinAArcane->setSuffix("%");
    form->addRow("Check penality:",spinAPenalty = new QSpinBox());
    spinAPenalty->setRange(-50,0);
    form->addRow("Type:",comboAType = new QComboBox());
    setLayout(form);
}

int CQTs_ItemArmPage::nextId() const{
    return CQTs_ItemEditor::page_desc;
}
CQTs_ItemShieldPage::CQTs_ItemShieldPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();
    form = new QFormLayout();
    form->addRow("AC:",spinSAC = new QSpinBox());
    form->addRow("Dex Max(-1 if none):",spinSDex = new QSpinBox());
    spinSDex->setMinimum(-1);
    spinSDex->setValue(-1);
    form->addRow("Arcane failure:",spinSArcane = new QSpinBox());
    spinSArcane->setRange(0,100);
    spinSArcane->setSuffix("%");
    form->addRow("Check penality:",spinSPenalty = new QSpinBox());
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

    //connections

}



