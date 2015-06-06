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
    LMax = 20;//used to hide levele in prestige classes
    //LabName = new QLabel();
    LabHD = new QLabel();
    LabRanks = new QLabel();
    LabLev  = new QLabel*[20];
    LabBAB  = new QLabel*[20];
    LabFort = new QLabel*[20];
    LabRef  = new QLabel*[20];
    LabWill = new QLabel*[20];
    LabSpells = new QLabel*[20*10+11];//first 20*10 are spells other are labels
    QGridLayout *grid = new QGridLayout();
    int r = 0;
    QLabel *Tlab;// = new QLabel(tr("Name:"));
    /*grid->addWidget(Tlab,r,0);
    grid->addWidget(LabName,r++,1);*/
    Tlab = new QLabel(tr("Hit Dice:"));
    Tlab->setAlignment(Qt::AlignHCenter);
    grid->addWidget(Tlab,r,0);
    grid->addWidget(LabHD,r++,1);
    Tlab = new QLabel(tr("Skill points per level:"));
    Tlab->setAlignment(Qt::AlignHCenter);
    grid->addWidget(Tlab,r,0);
    grid->addWidget(LabRanks,r++,1);
    QGroupBox *ProgBox= new QGroupBox(tr("Progression:"));
    grid->addWidget(ProgBox,r++,0,1,2);
    //table
    QGridLayout *grid2 = new QGridLayout();
    int row =0;
    LabSpells[20*10] = new QLabel(tr("Spells:"));
    LabSpells[20*10]->setAlignment(Qt::AlignHCenter);
    grid2->addWidget(LabSpells[20*10],row,5,1,10);
    LabSpells[20*10]->hide();
    //next row
    row++;
    Tlab = new QLabel(tr("Level:"));
    Tlab->setAlignment(Qt::AlignHCenter);
    grid2->addWidget(Tlab,row,0);
    Tlab = new QLabel(tr("BAB:"));
    Tlab->setAlignment(Qt::AlignHCenter);
    grid2->addWidget(Tlab,row,1);
    Tlab = new QLabel(tr("Fortitude:"));
    Tlab->setAlignment(Qt::AlignHCenter);
    grid2->addWidget(Tlab,row,2);
    Tlab = new QLabel(tr("Reflexes:"));
    Tlab->setAlignment(Qt::AlignHCenter);
    grid2->addWidget(Tlab,row,3);
    Tlab = new QLabel(tr("Will:"));
    Tlab->setAlignment(Qt::AlignHCenter);
    grid2->addWidget(Tlab,row,4);
    for (int j = 0; j < 10; ++j) {
        LabSpells[20*10+j+1] = new QLabel();
        LabSpells[20*10+j+1]->setNum(j);
        LabSpells[20*10+j+1]->setAlignment(Qt::AlignHCenter);
        LabSpells[20*10+j+1]->hide();
        grid2->addWidget(LabSpells[20*10+j+1],row,5+j);
    }
    //facilitating view
    QPalette pal = palette();
    bool darker = false;
    pal.setColor(QPalette::Background, pal.color(QPalette::Background).darker(120));
    row++;
    for (int i = 0; i < 20; ++i) {
        LabLev[i]   = new QLabel();
        LabBAB[i]   = new QLabel();
        LabFort[i]  = new QLabel();
        LabRef[i]   = new QLabel();
        LabWill[i]  = new QLabel();
        LabLev[i]->setNum(i+1);
        for (int j = 0; j < 10; ++j) {
            LabSpells[10*i+j] = new QLabel("-");
            LabSpells[10*i+j]->setAlignment(Qt::AlignHCenter);
            LabSpells[10*i+j]->hide();
            LabSpells[10*i+j]->setMinimumWidth(20);
            grid2->addWidget(LabSpells[10*i+j],row,5+j);
            if(darker){
                LabSpells[10*i+j]->setAutoFillBackground(true);
                LabSpells[10*i+j]->setPalette(pal);
            }
        }
        LabLev[i]   ->setAlignment(Qt::AlignHCenter);
        LabBAB[i]   ->setAlignment(Qt::AlignHCenter);
        LabFort[i]  ->setAlignment(Qt::AlignHCenter);
        LabRef[i]   ->setAlignment(Qt::AlignHCenter);
        LabWill[i]  ->setAlignment(Qt::AlignHCenter);
        if(darker){
            LabLev[i]   ->setAutoFillBackground(true);
            LabBAB[i]   ->setAutoFillBackground(true);
            LabFort[i]  ->setAutoFillBackground(true);
            LabRef[i]   ->setAutoFillBackground(true);
            LabWill[i]  ->setAutoFillBackground(true);
            LabLev[i]   ->setPalette(pal);
            LabBAB[i]   ->setPalette(pal);
            LabFort[i]  ->setPalette(pal);
            LabRef[i]   ->setPalette(pal);
            LabWill[i]  ->setPalette(pal);

        }
        darker = !darker;

        grid2->addWidget(LabLev[i],row,0);
        grid2->addWidget(LabBAB[i],row,1);
        grid2->addWidget(LabFort[i],row,2);
        grid2->addWidget(LabRef[i],row,3);
        grid2->addWidget(LabWill[i],row,4);
        row++;
    }
    grid2->setHorizontalSpacing(0);
    grid2->setVerticalSpacing(0);
    ProgBox->setLayout(grid2);

    setLayout(grid);
}


void CQTs_ClassViewer::setLabs(CQTs_Class *selected, int altMax){
    bool ispellcaster = selected->isSpellcaster();
    int lmax =selected->MaxLv();
    if((altMax<lmax) && (altMax>0))
        lmax = altMax;
    if(LMax!=lmax){
        LMax = lmax;
        for(int i=0;i<20;++i){
            if(i<LMax){
                LabLev[i]   ->setVisible(true);
                LabBAB[i]   ->setVisible(true);
                LabFort[i]  ->setVisible(true);
                LabRef[i]   ->setVisible(true);
                LabWill[i]  ->setVisible(true);
                for (int j = 0; j < 10; ++j)
                    LabSpells[10*i+j]->setVisible(ispellcaster);
            }else{
                LabLev[i]   ->setVisible(false);
                LabBAB[i]   ->setVisible(false);
                LabFort[i]  ->setVisible(false);
                LabRef[i]   ->setVisible(false);
                LabWill[i]  ->setVisible(false);
                for (int j = 0; j < 10; ++j)
                    LabSpells[10*i+j]->setVisible(false);
            }
        }
    }
    //LabName ->setText(selected->myName());
    LabHD ->setNum(selected->HP());
    LabRanks ->setNum(selected->AP());
    int f =0,r=0,w=0,bab = selected->BAB();
    if(selected->STFort())  f = 2;
    if(selected->STRef())   r = 2;
    if(selected->STWill())  w = 2;
    for (int i = 0; i < LMax; ++i) {
        int dbab,df,dr,dw;
        switch (bab) {
        case 0:
            dbab = (1+i)/2.;
            break;
        case 1:
            dbab = (1+i)*3/4.;
            break;
        case 2:
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
        //setting spells:
        LabSpells[20*10]->setVisible(ispellcaster);
        for (int j = 0; j < 10; ++j) {
            LabSpells[10*i+j]->setVisible(ispellcaster);
            LabSpells[20*10+1+j]->setVisible(ispellcaster);
            if(ispellcaster){
                QString num = "-";
                if(j<selected->SpellPerDay(1+i).size())
                    num=selected->SpellPerDay(1+i)[j];
                LabSpells[10*i+j]->setText(num);
            }
        }
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
    LabSmallDesc = new QLabel();

    QGridLayout *grid = new QGridLayout();

    QLabel *Tlab = new QLabel(tr("Name:"));
    grid->addWidget(Tlab,0,0);
    grid->addWidget(LabName,0,1);

    Tlab = new QLabel(tr("Surname:"));
    grid->addWidget(Tlab,1,0);
    grid->addWidget(LabSurname,1,1);

    grid->addWidget(LabSmallDesc,2,0,1,2);

    setLayout(grid);
}


void CQTs_ChBioViewer::setLabs(CQTs_Character *selected){
    LabName->setText(selected->getName());
    LabSurname->setText(selected->getSurname());
    int Age = selected->getAge();
    QStringList classes = selected->classNames();
    QString classList;
    for(int i=0;i<classes.size();i++){
        if(i!=0)
            classList+=", ";
        classList+=classes[i];
    }

    QString desc = tr("Is a %1 %3 of %2 years")
            .arg(selected->Race())
            .arg(Age)
            .arg(classList);
    LabSmallDesc->setText(desc);
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
    QPalette pal = palette();
    bool darker = false;
    pal.setColor(QPalette::Background, pal.color(QPalette::Background).darker(120));
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(new QLabel(tr("Temporary")),0,3,1,2);
    for (int i = 0; i < 6; ++i) {
        grid->addWidget(LabName[i] = new QLabel(names[i]),i+1,0);

        grid->addWidget(LabValue[i] = new QLabel("10"),i+1,1);
        LabValue[i]->setFrameStyle(QFrame::Panel|QFrame::Raised);
        LabValue[i]->setAlignment(Qt::AlignCenter);

        grid->addWidget(LabMod[i] = new QLabel("+0"),i+1,2);
        LabMod[i]->setFrameStyle(QFrame::Panel|QFrame::Sunken);
        LabMod[i]->setAlignment(Qt::AlignCenter);

        grid->addWidget(LabValue[i+6] = new QLabel("10"),i+1,3);
        LabValue[i+6]->setFrameStyle(QFrame::WinPanel|QFrame::Raised);
        LabValue[i+6]->setAlignment(Qt::AlignCenter);

        grid->addWidget(LabMod[i+6] = new QLabel("+0"),i+1,4);
        LabMod[i+6]->setFrameStyle(QFrame::WinPanel|QFrame::Sunken);
        LabMod[i+6]->setAlignment(Qt::AlignCenter);

        if(darker){
            LabName[i]->setPalette(pal);
            LabValue[i]->setPalette(pal);
            LabMod[i]->setPalette(pal);
            LabValue[i+6]->setPalette(pal);
            LabMod[i+6]->setPalette(pal);
        }
        darker = !darker;
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
        tLab->setAlignment(Qt::AlignCenter);
        Labels.push_back(tLab);//[i*8+0] name

        grid->addWidget(tLab,i+rows,0);
        grid->addWidget(tLab= new QLabel("0"),i+rows,1);
        tLab->setAlignment(Qt::AlignCenter);
        Labels.push_back(tLab);//[i*8+1] d20

        tLab->setFrameStyle(QFrame::Panel|QFrame::Raised);
        grid->addWidget(tLab= new QLabel("="),i+rows,2);
        tLab->setAlignment(Qt::AlignCenter);
        Labels.push_back(tLab);

        grid->addWidget(tLab= new QLabel("0"),i+rows,3);
        tLab->setAlignment(Qt::AlignCenter);
        Labels.push_back(tLab);//[i*8+3] abl mod

        grid->addWidget(tLab= new QLabel("+"),i+rows,4);
        tLab->setAlignment(Qt::AlignCenter);
        Labels.push_back(tLab);

        grid->addWidget(tLab= new QLabel("0"),i+rows,5);
        tLab->setAlignment(Qt::AlignCenter);
        Labels.push_back(tLab);//[i*8+5] ranks

        grid->addWidget(tLab= new QLabel("+"),i+rows,6);
        tLab->setAlignment(Qt::AlignCenter);
        Labels.push_back(tLab);

        grid->addWidget(tLab= new QLabel("0"),i+rows,7);
        tLab->setAlignment(Qt::AlignCenter);
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
        int tot=0, ranks, abl;
        //[i*8+1] d20
        //[i*8+3] abl mod
        //[i*8+5] ranks
        //[i*8+7] var mods
        ranks=selected->getRanks(eng->skillData(i));
        Labels[i*8+5]->setNum(ranks);
        tot+=ranks;
        //if( dummy !=0 ) qDebug() << eng->skillData(i) <<": "<< dummy;
        abl=selected->getAbilityMod(eng->skillData(i).myAbility());
        Labels[i*8+3]->setNum(abl);
        tot+=abl;
        if(eng->skillData(i).needsTrain()&&ranks==0)
            Labels[i*8+1]->setText(tr("can't"));
        else
            Labels[i*8+1]->setNum(tot);
        //Labels[i*8+1]->setToolTip(circumstanzial description);
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
