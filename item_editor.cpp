#include "item_editor.h"

#include <QFormLayout>

#include <QDebug>

CQTs_ItemFirstPage::CQTs_ItemFirstPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();

    setTitle(QObject::tr("Basic information"));
    form->addRow(QObject::tr("Code:"), lineCode = new QLineEdit());
    form->addRow(QObject::tr("Name:"), lineName = new QLineEdit());
    form->addRow(QObject::tr("Weight:"), spinWeight = new QDoubleSpinBox());
    form->addRow(QObject::tr("Price (copper):"), spinPrice = new QSpinBox());
    spinPrice->setRange(0,999999999);
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
    form->addRow(QObject::tr("AC:"),spinAC = new QSpinBox());
    form->addRow(QObject::tr("Dex Max:"),spinDex = new QSpinBox());
    form->addRow(QObject::tr("Arcane failure:"),spinArcane = new QSpinBox());
    spinArcane->setRange(0,100);
    spinArcane->setSuffix("%");
    form->addRow(QObject::tr("Check penality:"),spinPenalty = new QSpinBox());
    spinPenalty->setRange(-50,0);
    form->addRow(QObject::tr("Type:"),comboType = new QComboBox());
    comboType->addItem(QObject::tr("Light"));
    comboType->addItem(QObject::tr("Medium"));
    comboType->addItem(QObject::tr("Heavy"));
    setLayout(form);
    registerField("a.ac*",spinAC);
    registerField("a.dex",spinDex);
    registerField("a.arcane",spinArcane);
    registerField("a.penalty",spinPenalty);
    registerField("a.type",comboType);
}

int CQTs_ItemArmPage::nextId() const{
    return CQTs_ItemEditor::page_desc;
}
CQTs_ItemShieldPage::CQTs_ItemShieldPage(QWidget *parent):
    QWizardPage(parent)
{
    QFormLayout *form = new QFormLayout();
    setTitle(QObject::tr("Armor information"));
    form = new QFormLayout();
    form->addRow(QObject::tr("AC:"),spinAC = new QSpinBox());
    form->addRow(QObject::tr("Dex Max:"),spinDex = new QSpinBox());
    form->addRow(QObject::tr("Arcane failure:"),spinArcane = new QSpinBox());
    spinArcane->setRange(0,100);
    spinArcane->setSuffix("%");
    form->addRow(QObject::tr("Check penality:"),spinPenalty = new QSpinBox());
    spinPenalty->setRange(-50,0);
    setLayout(form);
    registerField("s.ac*",spinAC);
    registerField("s.dex",spinDex);
    registerField("s.arcane",spinArcane);
    registerField("s.penalty",spinPenalty);
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
    registerField("description",textDescription);
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

void CQTs_ItemEditor::accept(){
    QString code = field("code").toString();
    QString name = field("name").toString();
    double weight = field("weight").toDouble();
    money price = field("price").toInt();
    QString type = "good";
    CQTs_item editedItem(code,"",name,weight,price);
    qDebug() << code;
    qDebug() << name;
    qDebug() << weight;
    qDebug() << price.value();

    if(hasVisitedPage(page_arm)){
        type = "armor";
        int AC = field("a.ac*").toInt();
        int Dex = field("a.dex").toInt();
        int arcane = field("a.arcane").toInt();
        int penalty = field("a.penalty").toInt();
        QString type = field("a.type").toString();
        qDebug() << AC;
        qDebug() << Dex;
        qDebug() << penalty;
        qDebug() << arcane;
        qDebug() << type;

    }

    if(hasVisitedPage(page_shield)){
        type = "shield";
        int AC = field("s.ac*").toInt();
        int Dex = field("s.dex").toInt();
        int arcane = field("s.arcane").toInt();
        int penalty = field("s.penalty").toInt();
        qDebug() << AC;
        qDebug() << Dex;
        qDebug() << penalty;
        qDebug() << arcane;
    }

    if(hasVisitedPage(page_weap)){
        if(type == "good")
            type = "weapon";
        else
            type += "weapon";

        QString damage = field("w.damage*").toString();
        QString critical = field("w.crit*").toString();
        bool bludgeon = field("w.blud").toBool();
        bool piercing = field("w.pier").toBool();
        bool slashing = field("w.slash").toBool();
        int rangesq = field("w.range").toInt();
        bool throwing = field("w.throw").toBool();
        bool projectile = field("w.projectile").toBool();
        qDebug() << damage;
        qDebug() << critical;
        qDebug() << bludgeon << piercing << slashing;
        qDebug() << rangesq;
        qDebug() << throwing << projectile;
    }

    QString desc = field("description").toString();
    if(desc!=""){

    }
    editedItem.set_myType(type);
    emit thisItem(editedItem);
    close();
}
