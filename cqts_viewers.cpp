#include "cqts_viewers.h"
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
/*ClassViewer*/
CQTs_ClassViewer::CQTs_ClassViewer(QWidget *parent) :
    QGroupBox(tr("Class Viewer"),parent)
{
    initialize();
}

CQTs_ClassViewer::CQTs_ClassViewer(CQTs_Class *selected, QWidget *parent) :
    QGroupBox(tr("Class Viewer"),parent)
{
    initialize();
    setLabs(selected);
}

void CQTs_ClassViewer::initialize(){

    LabName = new QLabel();
    LabBAB = new QLabel();
    LabFort = new QLabel();
    LabRef = new QLabel();
    LabWill = new QLabel();

    QGridLayout *grid = new QGridLayout();

    QLabel *Tlab = new QLabel(tr("Name:"));
    grid->addWidget(Tlab,0,0);
    grid->addWidget(LabName,0,1);

    Tlab = new QLabel(tr("Base Attack Bonus:"));
    grid->addWidget(Tlab,1,0);
    grid->addWidget(LabBAB,1,1);

    QGroupBox *SavesBox= new QGroupBox(tr("Saves:"));
    grid->addWidget(SavesBox,2,0,1,2);
    QGridLayout *grid2 = new QGridLayout();
    Tlab = new QLabel(tr("Fortitude:"));
    grid2->addWidget(Tlab,0,0);
    grid2->addWidget(LabFort,0,1);
    Tlab = new QLabel(tr("Reflexes"));
    grid2->addWidget(Tlab,1,0);
    grid2->addWidget(LabRef,1,1);
    Tlab = new QLabel(tr("Will:"));
    grid2->addWidget(Tlab,2,0);
    grid2->addWidget(LabWill,2,1);
    SavesBox->setLayout(grid2);

    setLayout(grid);
}


void CQTs_ClassViewer::setLabs(CQTs_Class *selected){
    QString bonus[4]={tr("error"),tr("Poor"),tr("Good"),tr("Average")};

    LabName ->setText(selected->className());
    LabBAB ->setText(bonus[selected->classBAB()]);
    LabFort ->setText(bonus[1+selected->STFort()]);
    LabRef ->setText(bonus[1+selected->STRef()]);
    LabWill ->setText(bonus[1+selected->STWill()]);
}
/*BioViewer*/

CQTs_ChBioViewer::CQTs_ChBioViewer(QWidget *parent) :
    QGroupBox(tr("Bio"),parent)
{
    initialize();
}

CQTs_ChBioViewer::CQTs_ChBioViewer(CQTs_Character *selected, QWidget *parent) :
    QGroupBox(tr("Bio"),parent)
{
    initialize();
    setLabs(selected);
}

void CQTs_ChBioViewer::initialize(){

    LabName = new QLabel();
    LabSurname = new QLabel();
    LabAge = new QLabel();

    QGridLayout *grid = new QGridLayout();

    QLabel *Tlab = new QLabel(tr("Name:"));
    grid->addWidget(Tlab,0,0);
    grid->addWidget(LabName,0,1);

    Tlab = new QLabel(tr("Surname:"));
    grid->addWidget(Tlab,1,0);
    grid->addWidget(LabSurname,1,1);

    Tlab = new QLabel(tr("Age:"));
    grid->addWidget(Tlab,2,0);
    grid->addWidget(LabAge,2,1);

    setLayout(grid);
}


void CQTs_ChBioViewer::setLabs(CQTs_Character *selected){
    LabName->setText(selected->getName());
    LabSurname->setText(selected->getSurname());
    LabAge->setNum(selected->getAge());
}

/*AbilitiesViewer*/

CQTs_ChAbilitiesViewer::CQTs_ChAbilitiesViewer(QWidget *parent) :
    QGroupBox(tr("Abilities"),parent)
{
    initialize();
}

CQTs_ChAbilitiesViewer::CQTs_ChAbilitiesViewer(CQTs_Character *selected, QWidget *parent) :
    QGroupBox(tr("Abilities"),parent)
{
    initialize();
    setLabs(selected);
}

void CQTs_ChAbilitiesViewer::initialize(){

    LabName =   new QLabel* [6];
    LabValue =  new QLabel* [12];
    LabMod =    new QLabel* [12];

    QString names[6]={tr("Strength"),tr("Dexterity"),tr("Constitution"),tr("Intelligence"),tr("Wisdom"),tr("Charisma")};

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(new QLabel(tr("Temporary")),0,3,1,2);
    for (int i = 0; i < 6; ++i) {
        grid->addWidget(LabName[i] = new QLabel(names[i]),i+1,0);

        grid->addWidget(LabValue[i] = new QLabel("10"),i+1,1);
        LabValue[i]->setFrameStyle(QFrame::Panel|QFrame::Raised);

        grid->addWidget(LabMod[i] = new QLabel("+0"),i+1,2);
        LabMod[i]->setFrameStyle(QFrame::Panel|QFrame::Sunken);

        grid->addWidget(LabValue[i+6] = new QLabel("10"),i+1,3);
        LabValue[i+6]->setFrameStyle(QFrame::WinPanel|QFrame::Raised);

        grid->addWidget(LabMod[i+6] = new QLabel("+0"),i+1,4);
        LabMod[i+6]->setFrameStyle(QFrame::WinPanel|QFrame::Sunken);
    }


    setLayout(grid);
}

void CQTs_ChAbilitiesViewer::setLab(int sel, int val, bool temporary){
    LabValue[sel+6*temporary]->setNum(val);

    val= (val-10)/2.;
    if(val>0)
        LabMod[sel+temporary*6]->setText("+"+QString::number(val));
    else
        LabMod[sel+temporary*6]->setNum(val);
}

void CQTs_ChAbilitiesViewer::setLabs(CQTs_Character *selected){
    for (int i = 0; i < 6; ++i){
        int val = selected->getAbility( i);
        setLab(i,val,false);
        setLab(i,val,true);
    }
}

/*SkillsViewer*/

CQTs_ChSkillsViewer::CQTs_ChSkillsViewer(QWidget *parent) :
    QGroupBox(tr("Skills"),parent)
{
    initialize();
}

/*CQTs_ChSkillsViewer::CQTs_ChSkillsViewer(CQTs_Character *selected, QWidget *parent) :
    QGroupBox(tr("Skills"),parent)
{
    initialize();
    setLabs(selected);
}*/

void CQTs_ChSkillsViewer::initialize(){
    //could be better if claimed from a conf option
    QGridLayout *grid = new QGridLayout();
    QFile file("Skills_Eng.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
       // qDebug()<<"errore";
        //add an alert!
    }
    else{
        QXmlStreamReader xml(&file);
       for(int i=0;!xml.atEnd();){
            if(xml.name()=="skill"&&xml.isStartElement())
            {
                while(!(xml.name()=="skill"&&xml.isEndElement())){
                    xml.readNext();
                    if(xml.name()=="name"&&xml.isStartElement()){
                        while(!xml.readNext()==6);
                        QString temp=xml.text().toString();
                        QLabel *tLab = new QLabel(temp);
                        LabName.push_back(tLab);
                        grid->addWidget(tLab,i+1,0);
                        grid->addWidget(tLab= new QLabel("0"),1+i,1);
                        tLab->setFrameStyle(QFrame::Panel|QFrame::Raised);
                        grid->addWidget(tLab= new QLabel("="),i+1,2);
                        grid->addWidget(tLab= new QLabel("0"),i+1,3);
                        grid->addWidget(tLab= new QLabel("+"),i+1,4);
                        grid->addWidget(tLab= new QLabel("0"),i+1,5);
                        grid->addWidget(tLab= new QLabel("+"),i+1,6);
                        grid->addWidget(tLab= new QLabel("0"),i+1,7);
                        //qDebug()<<nome<<xml.text();
                        i++;

                    }
                }
            }
            if (xml.hasError()) {
                // do error handling
            }
            xml.readNext();
        }
    }

    setLayout(grid);
}

/*SaveThrowViewer*/

CQTs_ChSTViewer::CQTs_ChSTViewer(QWidget *parent) :
    QGroupBox(tr("Saves"),parent)
{
    initialize();
}

//CQTs_ChSTViewer::CQTs_ChSTViewer(CQTs_Character *selected, QWidget *parent) :
//    QGroupBox(tr("Skills"),parent)
//{
//    initialize();
//    setLabs(selected);
//}

void CQTs_ChSTViewer::initialize(){

    LabName  =   new QLabel* [3];
    LabValue =  new QLabel* [3];
    LabAb   =  new QLabel* [3];
    LabMod =    new QLabel* [3];
    SpinVarious = new QSpinBox* [3];
    QLabel *tLab;

    QGridLayout *grid = new QGridLayout();

    QString Names[3]={tr("Fortitude"),tr("Reflex"),tr("Will")};
    for(int i=0;i<3;i++){
        int j=0;
        grid->addWidget(LabName[i]= new QLabel(Names[i]),i+1,j++);
        grid->addWidget(LabValue[i]= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("="),i+1,j++);
        grid->addWidget(LabAb[i]= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("+"),i+1,j++);
        grid->addWidget(LabMod[i]= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("+"),i+1,j++);
        grid->addWidget(tLab= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("+"),i+1,j++);
        grid->addWidget(SpinVarious[i] = new QSpinBox(),i+1,j++);
        SpinVarious[i]->setRange(0,99);
        //SpinVarious[i]->
    }

    setLayout(grid);
}

void CQTs_ChSTViewer::setLabs(CQTs_Character *selected){
    CQTs_Character::CQT_Abilities statmap[3]={CQTs_Character::CON,CQTs_Character::DEX,CQTs_Character::WIS};
    for (int i = 0; i < 3; ++i){
        int ab=selected->getAbilityMod(statmap[i]);
        int mod=selected->getST(i);
        int val=ab+mod;
        LabMod[i]->setNum(mod);
        LabAb[i]->setNum(ab);
        LabValue[i]->setNum(val);
    }
}

/*CQTs_ChBABViever*/

CQTs_ChBABViever::CQTs_ChBABViever(QWidget *parent) :
QGroupBox(tr("BAB"),parent)
{
initialize();
}
/*
CQTs_ChBABViever::CQTs_ChBABViever(CQTs_Character *selected, QWidget *parent) :
QGroupBox(tr("Attacks"),parent)
{
initialize();
setLabs(selected);
}*/

void CQTs_ChBABViever::initialize(){

    LabName  =   new QLabel* [3];
    LabValue =  new QLabel* [3];
    LabAb   =  new QLabel* [3];
    LabMod =    new QLabel* [3];
    SpinVarious = new QSpinBox* [3];
    QLabel *tLab;

    QGridLayout *grid = new QGridLayout();

    QString Names[3]={tr("Melee"),tr("Ranged"),tr("Grapple")};
    for(int i=0;i<3;i++){
        int j=0;
        grid->addWidget(LabName[i]= new QLabel(Names[i]),i+1,j++);
        grid->addWidget(LabValue[i]= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("="),i+1,j++);
        grid->addWidget(LabAb[i]= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("+"),i+1,j++);
        grid->addWidget(LabMod[i]= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("+"),i+1,j++);
        grid->addWidget(tLab= new QLabel("0"),i+1,j++);
        grid->addWidget(tLab= new QLabel("+"),i+1,j++);
        grid->addWidget(SpinVarious[i] = new QSpinBox(),i+1,j++);
        SpinVarious[i]->setRange(0,99);
        //SpinVarious[i]->
    }

    setLayout(grid);
}


void CQTs_ChBABViever::setLabs(CQTs_Character *selected){
    CQTs_Character::CQT_Abilities statmap[3]={CQTs_Character::CON,CQTs_Character::DEX,CQTs_Character::WIS};
    for (int i = 0; i < 3; ++i){
        int ab=selected->getAbilityMod(statmap[i]);
        int mod=selected->getST(i);
        int val=ab+mod;
        LabMod[i]->setNum(mod);
        LabAb[i]->setNum(ab);
        LabValue[i]->setNum(val);
    }
}
