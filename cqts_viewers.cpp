#include "cqts_viewers.h"
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QPushButton>
#include <QScrollArea>
#include <QGroupBox>
#include <QDebug>

/*ClassViewer*/
CQTs_ClassViewer::CQTs_ClassViewer(QWidget *parent) :
    QWidget(parent)
{
    initialize();
}

CQTs_ClassViewer::CQTs_ClassViewer(CQTs_Class *selected, QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setLabs(selected);
}

void CQTs_ClassViewer::initialize(){

    LabName = new QLabel();
    LabHD = new QLabel();
    LabRanks = new QLabel();
    LabBAB  = new QLabel*[20];
    LabFort = new QLabel*[20];
    LabRef  = new QLabel*[20];
    LabWill = new QLabel*[20];

    QGridLayout *grid = new QGridLayout();

    QLabel *Tlab = new QLabel(tr("Name:"));
    grid->addWidget(Tlab,0,0);
    grid->addWidget(LabName,0,1);
    Tlab = new QLabel(tr("Hit Dice:"));
    grid->addWidget(Tlab,1,0);
    grid->addWidget(LabHD,1,1);
    Tlab = new QLabel(tr("Skill points per level:"));
    grid->addWidget(Tlab,2,0);
    grid->addWidget(LabRanks,2,1);
    QGroupBox *ProgBox= new QGroupBox(tr("Progression:"));
    grid->addWidget(ProgBox,3,0,1,2);
    QGridLayout *grid2 = new QGridLayout();
    Tlab = new QLabel(tr("Level:"));
    grid2->addWidget(Tlab,0,0);
    Tlab = new QLabel(tr("BAB:"));
    grid2->addWidget(Tlab,0,1);
    Tlab = new QLabel(tr("Fortitude:"));
    grid2->addWidget(Tlab,0,2);
    Tlab = new QLabel(tr("Reflexes:"));
    grid2->addWidget(Tlab,0,3);
    Tlab = new QLabel(tr("Will:"));
    grid2->addWidget(Tlab,0,4);
    for (int i = 0; i < 20; ++i) {
        LabBAB[i]   = new QLabel();
        LabFort[i]  = new QLabel();
        LabRef[i]   = new QLabel();
        LabWill[i]  = new QLabel();
        Tlab = new QLabel();
        Tlab->setNum(i+1);
        grid2->addWidget(Tlab,i+1,0);
        grid2->addWidget(LabBAB[i],i+1,1);
        grid2->addWidget(LabFort[i],i+1,2);
        grid2->addWidget(LabRef[i],i+1,3);
        grid2->addWidget(LabWill[i],i+1,4);
    }
    ProgBox->setLayout(grid2);

    setLayout(grid);
}


void CQTs_ClassViewer::setLabs(CQTs_Class *selected){
    int LMax = selected->MaxLv();
    LabName ->setText(selected->myName());
    int f =0,r=0,w=0,bab = selected->BAB();
    qDebug()<<bab;
    if(selected->STFort())  f = 2;
    if(selected->STRef())   r = 2;
    if(selected->STWill())  w = 2;
    for (int i = 0; i < LMax; ++i) {
        int dbab,df,dr,dw;
        switch (bab) {
        case 1:
            dbab = (1+i)/2.;
            break;
        case 2:
            dbab = (1+i)*3/4.;
            break;
        case 3:
            dbab = (1+i);
            break;
        }
        if(f==2) df = 2.+(i+1)/2.;
        else df = (i+1)/3.;
        if(r==2) dr = 2.+(i+1)/2.;
        else dr = (i+1)/3.;
        if(w==2) dw = 2.+(i+1)/2.;
        else dw = (i+1)/3.;
        LabBAB[i]  ->setNum(dbab);
        LabFort[i] ->setNum(df);
        LabRef[i]  ->setNum(dr);
        LabWill[i] ->setNum(dw);
    }
}
/*BioViewer*/

CQTs_ChBioViewer::CQTs_ChBioViewer(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setMaximumHeight(100);
}

CQTs_ChBioViewer::CQTs_ChBioViewer(CQTs_Character *selected, QWidget *parent) :
    QWidget(parent)
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
    QWidget(parent)
{
    initialize();
    setMaximumHeight(200);
}

CQTs_ChAbilitiesViewer::CQTs_ChAbilitiesViewer(CQTs_Character *selected, QWidget *parent) :
    QWidget(parent)
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

CQTs_ChSkillsViewer::CQTs_ChSkillsViewer(CQTs_engine* engine, QWidget *parent) :
    QWidget(parent)
{
    eng = engine;
    initialize();
}

/*CQTs_ChSkillsViewer::CQTs_ChSkillsViewer(CQTs_Character *selected, QWidget *parent) :
    QGroupBox(tr("Skills"),parent)
{
    initialize();
    setLabs(selected);
}
*/

void CQTs_ChSkillsViewer::initialize(){
    train = new QPushButton(tr("Show only trained"));
    train->setCheckable(true);
    connect(train,SIGNAL(released()),this,SLOT(showOnlyTrained()));
    // grid->addWidget(train,0,0,1,3);
    QVBoxLayout *vl  = new QVBoxLayout();
    vl->addWidget(train);
    QWidget *container = new QWidget();

    QScrollArea *scroll = new QScrollArea();

    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int rows=0;// number of rows before the skill list
    QGridLayout *grid = new QGridLayout();




    for (int i = 0; i < eng->skillNum(); ++i) {
        QLabel *tLab = new QLabel(eng->skillData(i).myName());

        //qDebug()<<"nome"<<tLab->text();
        Labels.push_back(tLab);//[i*8+0] name
        grid->addWidget(tLab,i+rows,0);
        grid->addWidget(tLab= new QLabel("0"),i+rows,1);
        Labels.push_back(tLab);//[i*8+1] d20
        tLab->setFrameStyle(QFrame::Panel|QFrame::Raised);
        grid->addWidget(tLab= new QLabel("="),i+rows,2);
        Labels.push_back(tLab);
        grid->addWidget(tLab= new QLabel("0"),i+rows,3);
        Labels.push_back(tLab);//[i*8+3] abl mod
        grid->addWidget(tLab= new QLabel("+"),i+rows,4);
        Labels.push_back(tLab);
        grid->addWidget(tLab= new QLabel("0"),i+rows,5);
        Labels.push_back(tLab);//[i*8+5] ranks
        grid->addWidget(tLab= new QLabel("+"),i+rows,6);
        Labels.push_back(tLab);
        grid->addWidget(tLab= new QLabel("0"),i+rows,7);
        Labels.push_back(tLab);//[i*8+7] var mods
    }
    container->setLayout(grid);
    scroll->setWidget(container);
    scroll->setWidgetResizable(true);
    scroll->setMinimumWidth(300);
    vl->addWidget(scroll);
    setLayout(vl);
}

void CQTs_ChSkillsViewer::showOnlyTrained(){
    if(train->isChecked()){
        for (int i = 0; i < eng->skillNum(); ++i) {
            if(eng->skillData(i).needsTrain()){
                if((Labels[8*i+5]->text()).toInt()==0){
                    for (int j = 0; j < 8; ++j)
                        Labels[8*i+j]->hide();
                }
            }
        }
        train->setText(tr("Show all"));
    }else{
        for (int i = 0; i < eng->skillNum(); ++i) {
            if(Labels[8*i]->isHidden()){
                for (int j = 0; j < 8; ++j)
                    Labels[8*i+j]->show();
            }
            train->setText(tr("Show only trained"));
        }
    }
}

void CQTs_ChSkillsViewer::setLabs(CQTs_Character *selected){
    for (int i = 0; i < eng->skillNum(); ++i) {
        Labels[i*8+5]->setNum(selected->getRanks(eng->skillData(i)));
        if( selected->getRanks(eng->skillData(i)) !=0 )
        {qDebug() << eng->skillData(i) <<": "<< selected->getRanks(eng->skillData(i));}
        Labels[i*8+3]->setNum(selected->getAbilityMod(eng->skillData(i).myAbility()));
    }
}

/*SaveThrowViewer*/

CQTs_ChSTViewer::CQTs_ChSTViewer(QWidget *parent) :
    QWidget(parent)
{
    initialize();
    setMaximumHeight(100);
}

//CQTs_ChSTViewer::CQTs_ChSTViewer(CQTs_Character *selected, QWidget *parent) :
//    QWidget(parent)
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
    QWidget(parent)
{
    initialize();
    setMaximumHeight(100);
}
/*
CQTs_ChBABViever::CQTs_ChBABViever(CQTs_Character *selected, QWidget *parent) :
QWidget(parent)
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
    CQTs_Character::CQT_Abilities statmap[3]={CQTs_Character::STR,CQTs_Character::DEX,CQTs_Character::STR};
    for (int i = 0; i < 3; ++i){
        int ab=selected->getAbilityMod(statmap[i]);
        int mod=selected->getBAB();
        int val=ab+mod;
        LabMod[i]->setNum(mod);
        LabAb[i]->setNum(ab);
        LabValue[i]->setNum(val);
    }
}
