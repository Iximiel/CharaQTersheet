#include "cqts_viewers.h"
#include <QGridLayout>
#include <QFile>
#include <QTextStream>

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

//CQTs_ChSkillsViewer::CQTs_ChSkillsViewer(CQTs_Character *selected, QWidget *parent) :
//    QGroupBox(tr("Skills"),parent)
//{
//    initialize();
//    setLabs(selected);
//}

void CQTs_ChSkillsViewer::initialize(){
    QFile file("Skills.txt");
    QGridLayout *grid = new QGridLayout();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){

    //add an alert!
       }
       else{
        QTextStream in(&file);
        for (int i=0;!in.atEnd();i++){
            QString temp=in.readLine();
            QLabel *tLab = new QLabel(temp);
            LabName.push_back(tLab);
            grid->addWidget(tLab,i,0);
            grid->addWidget(tLab= new QLabel("0"),i,1);
            tLab->setFrameStyle(QFrame::Panel|QFrame::Raised);
            grid->addWidget(tLab= new QLabel("="),i,2);
            grid->addWidget(tLab= new QLabel("0"),i,3);
            grid->addWidget(tLab= new QLabel("+"),i,4);
            grid->addWidget(tLab= new QLabel("0"),i,5);
            grid->addWidget(tLab= new QLabel("+"),i,6);
            grid->addWidget(tLab= new QLabel("0"),i,7);

        }
    }

    setLayout(grid);
}
