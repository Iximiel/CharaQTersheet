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
    QVBoxLayout *tLay = new QVBoxLayout();
    tLay->addWidget(cmdGood = new QCommandLinkButton("Good"));
    tLay->addWidget(cmdWeapon = new QCommandLinkButton("Weapon"));
    tLay->addWidget(cmdArmor = new QCommandLinkButton("Armor"));
    tLay->addWidget(cmdShield = new QCommandLinkButton("Shield"));
    form->addRow("Type:",tLay);
    setLayout(form);
    connect(cmdWeapon,SIGNAL(clicked()),this,SLOT(openWeapon()));
    connect(cmdArmor,SIGNAL(clicked()),this,SLOT(openArmor()));
    connect(cmdShield,SIGNAL(clicked()),this,SLOT(openShield()));
}

int CQTs_ItemFirstPage::nextId(){
    return next;
}

void CQTs_ItemFirstPage::openWeapon(){
    next = CQTs_ItemEditor::page_weap;
    validatePage();
    nextId();
}
void CQTs_ItemFirstPage::openArmor(){
    next = CQTs_ItemEditor::page_arm;
    nextId();
}
void CQTs_ItemFirstPage::openShield(){
    next = CQTs_ItemEditor::page_shield;
    nextId();
}
void CQTs_ItemFirstPage::openDescription(){
    next = CQTs_ItemEditor::page_shield;
    nextId();
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



