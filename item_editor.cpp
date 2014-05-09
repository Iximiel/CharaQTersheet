#include "item_editor.h"

//item editor
#include <QFormLayout>

CQTs_ItemEditor::CQTs_ItemEditor(QWidget *parent):
    QWizard(parent)
{
    QFormLayout *form = new QFormLayout();
 //   setTabPosition(QTabWidget::West);

    QWizardPage  *tWizardP = new QWizardPage ();//Basic info
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
    tWizardP->setLayout(form);
   // tWizardP->set
    setPage(page_intro,tWizardP);
    //Basic

    tWizardP = new QWizardPage ();//Weapon info
    form = new QFormLayout();
    tWizardP->setLayout(form);
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
    setPage(page_weap,tWizardP);
    //Weapon

    tWizardP = new QWizardPage ();//Armor info
    setPage(page_arm,tWizardP);
    form = new QFormLayout();
    form->addRow("AC:",spinAAC = new QSpinBox());
    form->addRow("Dex Max:",spinADex = new QSpinBox());
    form->addRow("Arcane failure:",spinAArcane = new QSpinBox());
    spinAArcane->setRange(0,100);
    spinAArcane->setSuffix("%");
    form->addRow("Check penality:",spinAPenalty = new QSpinBox());
    spinAPenalty->setRange(-50,0);
    form->addRow("Type:",comboAType = new QComboBox());
    tWizardP->setLayout(form);

    //Armor

    tWizardP = new QWizardPage ();//Shield info
    setPage(page_shield,tWizardP);
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
    tWizardP->setLayout(form);

    //Shield

    tWizardP = new QWizardPage ();//description
    tLay = new QVBoxLayout();
    tWizardP->setLayout(tLay);
    tLay->addWidget(textDescription = new QTextEdit());
    setPage(page_desc,tWizardP);
    //Description

    //connections
    connect(cmdWeapon,SIGNAL(clicked()),this,SLOT(openWeapon()));
    connect(cmdArmor,SIGNAL(clicked()),this,SLOT(openArmor()));
    connect(cmdShield,SIGNAL(clicked()),this,SLOT(openShield()));
}

void CQTs_ItemEditor::openWeapon(){

}
void CQTs_ItemEditor::openArmor(){}
void CQTs_ItemEditor::openShield(){}
void CQTs_ItemEditor::openDescription(){}

