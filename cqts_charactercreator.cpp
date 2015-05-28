#include "cqts_charactercreator.h"

#include <QStringList>
#include <QGridLayout>
#include <QFormLayout>
#include <QScrollArea>

//need to do ALL the registerField("className*", classNameLineEdit);

//let it be a wizard
CQTs_CharacterCreator::CQTs_CharacterCreator(CQTs_engine *eng, QWidget *parent)
    : QWizard(parent)
{
    engine = eng;
    setWindowTitle(tr("Create Character"));
    choseClass *pageclass = new choseClass(engine);
    choseAbilities *pageabilities = new choseAbilities(engine);
    choseBio *pagebio = new choseBio(engine);
    choseSkills *pageskills = new choseSkills(engine);

    addPage(pagebio);
    addPage(pageabilities);
    addPage(pageclass);
    addPage(pageskills);
}

void CQTs_CharacterCreator::accept(){
    charBio newBio;
    newBio.Name = field("myName").toString();
    newBio.Surname = field("mySurname").toString();
    newBio.age = field("myAge").toInt();
    int theclass = field("myClass").toInt();
    QString ClassCode = engine->classData(theclass);
    QMap<QString,int> skillRanks;
    int Abilities[6];
    for (int i = 0; i < 6; ++i) {
        QString fieldName = "myAbility" + QString::number(i);
        Abilities[i] = field(fieldName).toInt();
    }

    for(int i=0;i< engine->skillNum();i++){
        QString fieldName = "mySkillN" + QString::number(i);
        int ranks = field(fieldName).toInt();
        if(ranks>0)
            skillRanks.insert(engine->skillData(i),ranks);
    }
    CQTs_Character newChar;
    newChar.setEngine(engine);
    newChar.setBio(newBio);
    newChar.addLevel(ClassCode,skillRanks,Abilities);
    qDebug() << theclass;//dummy
    emit newCharacter(newChar);
    QDialog::accept();
}

/*bio*/
choseBio::choseBio(CQTs_engine* eng, QWidget *parent)
    : QWizardPage(parent)
{
    engine = eng;
    setTitle(tr("Set your basic infos"));
    QFormLayout *form = new QFormLayout();
    form->addRow(tr("Your name:"),LineName = new QLineEdit());
    form->addRow(tr("Your surname:"),LineSurname = new QLineEdit());
    form->addRow(tr("Your age:"),SpinAge = new QSpinBox());
    SpinAge->setMaximum(9999);
    registerField("myName",LineName);
    registerField("mySurname",LineSurname);
    registerField("myAge",SpinAge);
    setLayout(form);
}

/*Abilities*/
choseAbilities::choseAbilities(CQTs_engine *eng, QWidget *parent)
    : QWizardPage(parent)
{
    engine = eng;
    SpinAbilities = new QSpinBox*[6];
    QFormLayout *form = new QFormLayout();
    QString names[6]={tr("Strength"),tr("Dexterity"),tr("Constitution"),tr("Intelligence"),tr("Wisdom"),tr("Charisma")};
    for (int i = 0; i < 6; ++i) {
        QString fieldName = "myAbility" + QString::number(i);
        form->addRow(new QLabel(names[i]),SpinAbilities[i] = new QSpinBox());
        SpinAbilities[i]->setMaximum(20);//need to add races
        SpinAbilities[i]->setMinimum(1);//need to add races
        SpinAbilities[i]->setValue(8);
        connect(SpinAbilities[i],SIGNAL(valueChanged(int)),this,SLOT(UpdatePoints()));
        registerField(fieldName,SpinAbilities[i]);
    }
    LabelPoints = new QLabel("0");
    form->addRow(new QLabel(tr("Points spent:")),LabelPoints);
    LabelPoints->setAlignment(Qt::AlignCenter);
    setLayout(form);
}

void choseAbilities::UpdatePoints(){
    int pointspent = 0;
    for (int i = 0; i < 6; ++i) {
        int ability = SpinAbilities[i]->value();
        while(ability>14){
            ability--;
            pointspent+=(ability-10)/2.;
        }

        pointspent += ability - 8;
    }
    LabelPoints->setNum(pointspent);
}

/*class*/
choseClass::choseClass(CQTs_engine *eng, QWidget *parent)
    : QWizardPage(parent)
{
    engine = eng;
    setTitle(tr("Set first class"));
    QStringList listclass = engine->classNames();
    QGridLayout *grid = new QGridLayout();
    comboClass = new QComboBox();
    comboClass->addItems(listclass);
    QLabel *TLab = new QLabel(tr("Choose your first class:"));
    TLab->setWordWrap(true);
    grid->addWidget(TLab,0,0);
    grid->addWidget(comboClass,0,1);
    viewer = new CQTs_ClassViewer();
    grid->addWidget(viewer,1,0,2,2);

    setLayout(grid);

    registerField("myClass",comboClass);
    //connections
    connect(comboClass,SIGNAL(currentIndexChanged(int)),this,SLOT(selClass(int)));
    if (listclass.size()>0){
        comboClass->currentIndexChanged(0);
    }

}

void choseClass::selClass(int selected){
    CQTs_Class classSel = engine->classData(selected);
    viewer->setLabs(&classSel,5);
}

/*skills*/
choseSkills::choseSkills(CQTs_engine* eng, QWidget *parent)
    : QWizardPage(parent)
{
    engine = eng;
    setTitle(tr("Set your skillponts"));

    QWidget *container = new QWidget();
    QScrollArea *scroll = new QScrollArea();
    //setting up layouts
    QVBoxLayout *maingrid = new QVBoxLayout();
    QGridLayout *secgrid = new QGridLayout();
    labelSpent = new QLabel();
    labelSpent->setAlignment(Qt::AlignRight);
    maingrid->addWidget(labelSpent);
    maingrid->addWidget(scroll);
    spinSkills = new QSpinBox*[engine->skillNum()];
    labelResult = new QLabel*[engine->skillNum()];
    int r = 0;
    secgrid->addWidget(new QLabel(tr("Skill")),r,0);
    secgrid->addWidget(new QLabel(tr("Points:")),r,1);
    secgrid->addWidget(new QLabel(tr("Ranks:")),r,2);
    for(int i=0 ; i < engine->skillNum() ; i++){
        int c = 0;
        spinSkills[i] = new QSpinBox();
        spinSkills[i]->setMaximum(4);
        secgrid->addWidget(new QLabel(engine->skillData(i).myName()),++r,c++);
        secgrid->addWidget(spinSkills[i],r,c++);
        secgrid->addWidget(labelResult[i] = new QLabel(),r,c++);
        labelResult[i]->setNum(0);
        labelResult[i]->setAlignment(Qt::AlignHCenter);
        QString fieldName = "mySkillN" + QString::number(i);
        registerField(fieldName,spinSkills[i]);
        connect(spinSkills[i],SIGNAL(valueChanged(int)),this,SLOT(calcRanks()));
    }
    setLayout(maingrid);
    container->setLayout(secgrid);
    scroll->setWidget(container);
    maxranks = -1;
}

void choseSkills::initializePage(){
    int theclass = field("myClass").toInt();
    CQTs_Class tempclass = engine->classData(theclass);
    int INTmod = field("myAbility3").toInt();//get int mod;
    INTmod = (INTmod-10)/2.;
    maxranks = (tempclass.AP()+INTmod)*4;
    int spent = 0;
    for(int i=0 ; i < engine->skillNum() ; i++){
        QPalette myPalette =palette();
        if(tempclass.isClassSkill(engine->skillData(i)))
            myPalette.setColor(QPalette::Base, myPalette.color(QPalette::Background).darker(120));
        spinSkills[i]->setPalette(myPalette);
        spent+=spinSkills[i]->value();
    }
    labelSpent->setText(tr("Point spent:")
                + QString::number(spent) + "/" + QString::number(maxranks));

}

bool choseSkills::isComplete() const{
    int spent = 0;
    for(int i=0 ; i < engine->skillNum() ; i++)
        spent+=spinSkills[i]->value();
    return spent == maxranks;
}

void choseSkills::calcRanks(){
    int theclass = field("myClass").toInt();
    CQTs_Class tempclass = engine->classData(theclass);
    int spent = 0;
    for(int i=0 ; i < engine->skillNum() ; i++){
        int val = spinSkills[i]->value();
        if(tempclass.isClassSkill(engine->skillData(i)))
            labelResult[i]->setNum(val);
        else
            labelResult[i]->setNum(val/2.);
        spent+=val;
    }
    labelSpent->setText(tr("Point spent:")
                + QString::number(spent) + "/" + QString::number(maxranks));
    emit completeChanged();
}
