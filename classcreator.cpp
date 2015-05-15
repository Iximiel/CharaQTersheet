#include "classcreator.h"

#include <QLabel>
//#include <QGridLayout>
#include <QFormLayout>

#ifdef CLASSCREATOR_H
/*CLASSCREATOR*/
CQTs_ClassEditor::CQTs_ClassEditor(CQTs_engine *eng, QWidget *parent)
    : QWidget(parent)
{
    initialize(eng);
}

CQTs_ClassEditor::CQTs_ClassEditor(CQTs_Class oldclass, CQTs_engine *eng, QWidget *parent)
    : QWidget(parent),myClass(oldclass)
{
    //myClass = oldclass;
    initialize(eng);
    setLabels(myClass);
}

void CQTs_ClassEditor::initialize(CQTs_engine *eng){
    engine = eng;
    SkillSelector=NULL;
    SpellSelector=NULL;
    QFormLayout *grid = new QFormLayout();
    QLabel *tLabel;
    //Name
    tLabel = new QLabel(tr("Name (in english):"));
    Line_Name = new  QLineEdit();
    grid->addRow(tLabel,Line_Name);
    //Hit Die
    tLabel = new QLabel(tr("Hit Die:"));
    Combo_HD = new QComboBox();
    QStringList List;
    List <<"d4"<<"d6"<<"d8"<<"d10"<<"d12";
    Combo_HD->addItems(List);
    grid->addRow(tLabel,Combo_HD);
    //Skill points
    tLabel = new QLabel(tr("Skill Points at Each Level:"));
    List.clear();
    List << "2" << "4" << "6" << "8";
    Combo_Ranks = new QComboBox();
    Combo_Ranks->addItems(List);
    grid->addRow(tLabel,Combo_Ranks);
    //BAB
    List.clear();
    List << tr("Poor") << tr("Average") << tr("Good");
    Combo_BaB = new QComboBox();
    Combo_BaB->addItems(List);
    tLabel = new QLabel(tr("Base Attack Bonus:"));
    //Save trows
    List.clear();
    List << tr("Poor") << tr("Good");
    grid->addRow(tLabel,Combo_BaB);
    Combo_TSFort = new QComboBox();
    Combo_TSFort->addItems(List);
    tLabel = new QLabel(tr("Base save: Fortitude:"));
    grid->addRow(tLabel,Combo_TSFort);
    Combo_TSRef = new QComboBox();
    Combo_TSRef->addItems(List);
    tLabel = new QLabel(tr("Base save: Reflexes:"));
    grid->addRow(tLabel,Combo_TSRef);
    Combo_TSWill = new QComboBox();
    Combo_TSWill->addItems(List);
    tLabel = new QLabel(tr("Base save: Will:"));
    grid->addRow(tLabel,Combo_TSWill);
    //infos
    BT_Weapon = new QPushButton(tr("Set Weapons Proficiency"));
    BT_Armor = new QPushButton(tr("Set Armor Proficiency"));
    BT_Skills = new QPushButton(tr("Set Class Skills"));
    BT_Spells = new QPushButton(tr("Set Class Spells"));
    BT_Weapon->setEnabled(false);
    grid->addRow(BT_Weapon);
    BT_Armor->setEnabled(false);
    grid->addRow(BT_Armor);
    grid->addRow(BT_Skills);
    grid->addRow(BT_Spells);
    connect(BT_Skills,SIGNAL(pressed()),this,SLOT(launchSkillSelector()));
    connect(BT_Spells,SIGNAL(pressed()),this,SLOT(launchSpellSelector()));
    QScrollArea *Scroll_Levels = new QScrollArea();
    Scroll_Levels->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grid->addRow(Scroll_Levels);
    QFormLayout *Levelgrid = new QFormLayout();
    Levelgrid->addRow(new QLabel("1:"),new QPushButton(tr("Add Level"),this));
    Scroll_Levels->setLayout(Levelgrid);
    QPushButton *tbutt1 = new QPushButton(tr("Save and Exit"));
    QPushButton *tbutt2 = new QPushButton(tr("Exit"));
    connect(tbutt1,SIGNAL(pressed()),this,SLOT(saveAndExit()));
    connect(tbutt2,SIGNAL(pressed()),this,SLOT(doClose()));
    grid->addRow(tbutt2,tbutt1);
    setLayout(grid);
}

void CQTs_ClassEditor::setLabels(CQTs_Class oldclass){
    myClass = oldclass;
    Line_Name->setText(myClass);
    Combo_HD->setCurrentIndex((myClass.HP()/2)-2);
    Combo_BaB->setCurrentIndex(myClass.BAB());
    Combo_Ranks->setCurrentIndex((myClass.AP()/2)-1);
    Combo_TSFort->setCurrentIndex(myClass.STFort());
    Combo_TSRef->setCurrentIndex(myClass.STRef());
    Combo_TSWill->setCurrentIndex(myClass.STWill());
}

void CQTs_ClassEditor::launchSkillSelector(){
    if(SkillSelector==NULL){
        SkillSelector = new CQTs_SkillSelector(engine);
        connect(SkillSelector,SIGNAL(getSkillList(QStringList)),this,SLOT(takeSkillList(QStringList)));
    }
    SkillSelector->setSkillFromClass(myClass.getSkills());
    SkillSelector->show();

}

void CQTs_ClassEditor::launchSpellSelector(){
    if(SpellSelector==NULL){
        SpellSelector = new CQTs_SpellSelector(engine);
        //connect(SpellSelector,SIGNAL(getSpellList(QStringList)),this,SLOT(takeSkillList(QStringList)));
    }
    //SpellSelector->setSkillFromClass(myClass.getSkills());
    SpellSelector->show();

}

void CQTs_ClassEditor::takeSkillList(QStringList myList){
    myClass.setSkills(myList);
}

void CQTs_ClassEditor::saveAndExit(){
    myClass.setCode(Line_Name->text());
    myClass.setmyName(Line_Name->text());//temporary name
    bool data[5]={0,0,0,0,0};
    if(Combo_BaB->currentIndex()==1)
        data[0]=true;
    else if(Combo_BaB->currentIndex()==2)
        data[1]=true;
    data[2] = Combo_TSFort->currentIndex();
    data[3] = Combo_TSRef->currentIndex();
    data[4] = Combo_TSWill->currentIndex();
    int dv,ranks, lmax;
    /**temp**/
    lmax = 20;
    /****/
    ranks = Combo_Ranks->currentText().toInt();
    dv = Combo_HD->currentText().remove("d").toInt();
    myClass.setParam(data,dv,ranks,lmax);
    //emit getClass(myClass);
    engine->appendClass(myClass);
    close();
    delete this;
}

void CQTs_ClassEditor::doClose(){
    close();
    delete this;
}
/*void CQTs_ClassEditor::launchArmorSelector(){}
void CQTs_ClassEditor::launchWeaponSelector(){}*/

/*Skillselector*/

CQTs_SkillSelector::CQTs_SkillSelector(CQTs_engine *eng,QWidget *parent)
    : QWidget(parent)
{
    engine = eng;
    QGridLayout *mygrid = new QGridLayout();
    mygrid->addWidget(new QLabel(tr("Select your class skills:")),0,0,1,2,Qt::AlignHCenter);
    QScrollArea *scrollskill = new QScrollArea();
    mygrid -> addWidget(scrollskill,1,0,2,2);
    scrollskill->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QFormLayout *grid = new QFormLayout();
    QWidget *areatoscroll = new QWidget();
    int skillsize = engine->skillNum();
    Checks_skills = new QCheckBox*[skillsize];
    for (int i = 0; i < skillsize; ++i) {
        Checks_skills[i] = new QCheckBox(engine->skillData(i));
        grid->addRow(Checks_skills[i]);
    }
    areatoscroll->setLayout(grid);
    scrollskill->setWidget(areatoscroll);
    QPushButton *tbutt1 = new QPushButton(tr("Save and Exit"));
    QPushButton *tbutt2 = new QPushButton(tr("Exit"));
    connect(tbutt1,SIGNAL(pressed()),this,SLOT(saveAndExit()));
    connect(tbutt2,SIGNAL(pressed()),this,SLOT(close()));
    mygrid -> addWidget(tbutt2,3,0);
    mygrid -> addWidget(tbutt1,3,1);
    setLayout(mygrid);
}

void CQTs_SkillSelector::setSkillFromClass(QStringList myclassList){
    int dim = myclassList.size();
    for(int i = 0;i<engine->skillNum();++i)
        Checks_skills[i]->setChecked(false);
    for (int i = 0; i < dim; ++i) {
        int skillID = engine->getSkillNum(myclassList[i]);
        if(skillID>0)
            Checks_skills[skillID]->setChecked(true);
    }

}

void CQTs_SkillSelector::saveAndExit(){
    QStringList thisClassList;
    for (int i = 0; i < engine->skillNum(); ++i) {
        if(Checks_skills[i]->isChecked()){
            QString dummy = engine->skillData(i);
            thisClassList.push_back(dummy);
        }
    }
    emit getSkillList(thisClassList);
    close();
}

//spelleditor
CQTs_SpellSelector::CQTs_SpellSelector(CQTs_engine *eng,QWidget *parent)
    : QWidget(parent)
{
    engine = eng;
    lmax=20;
    QGridLayout *mygrid = new QGridLayout();
    mygrid->addWidget(new QLabel(tr("Select your class spells:")),0,0,1,2,Qt::AlignHCenter);
    QScrollArea *scrollskill = new QScrollArea();
    mygrid -> addWidget(scrollskill,1,0,2,2);
    QGridLayout *grid = new QGridLayout();
    QWidget *areatoscroll = new QWidget();
    Spin_spell = new QSpinBox*[10*lmax];
    for (int i = 0; i < 10; ++i) {
        QLabel* tLab = new QLabel();
        tLab->setNum(i);//center
        grid->addWidget(tLab,0,i+1);
    }
    for (int lv = 0; lv < lmax; ++lv) {
        QLabel* tLab = new QLabel();
        tLab->setNum(lv+1);
        grid->addWidget(tLab,lv+2,0);
        for (int i = 0; i < 10; ++i) {
            Spin_spell[10*lv+i] = new QSpinBox();
            Spin_spell[10*lv+i]->setMinimum(0);
            Spin_spell[10*lv+i]->setMaximum(9);
            grid->addWidget(Spin_spell[10*lv+i],lv+2,i+1);
        }
    }
    areatoscroll->setLayout(grid);
    scrollskill->setWidget(areatoscroll);
    QPushButton *tbutt1 = new QPushButton(tr("Save and Exit"));
    QPushButton *tbutt2 = new QPushButton(tr("Exit"));
    connect(tbutt1,SIGNAL(pressed()),this,SLOT(saveAndExit()));
    connect(tbutt2,SIGNAL(pressed()),this,SLOT(close()));
    mygrid -> addWidget(tbutt2,3,0);
    mygrid -> addWidget(tbutt1,3,1);
    setLayout(mygrid);
}

void CQTs_SpellSelector::setSpellFromClass(QStringList myclassList){
    /* int dim = myclassList.size();
    for(int i = 0;i<engine->skillNum();++i)
        Checks_skills[i]->setChecked(false);
    for (int i = 0; i < dim; ++i) {
        int skillID = engine->getSkillNum(myclassList[i]);
        if(skillID>0)
            Checks_skills[skillID]->setChecked(true);
    }
*/
}

void CQTs_SpellSelector::saveAndExit(){
    /*  QStringList thisClassList;
    for (int i = 0; i < engine->skillNum(); ++i) {
        if(Checks_skills[i]->isChecked()){
            QString dummy = engine->skillData(i);
            thisClassList.push_back(dummy);
        }
    }
    emit getSkillList(thisClassList);*/
    close();
}


#endif
/*SPECIAL EDITOR*/
#ifdef CLASSSPECIALCREATOR_H
CQTs_ClassSpecialEdit::CQTs_ClassSpecialEdit(QWidget *parent)
    : QWidget(parent)
{

}
#endif
