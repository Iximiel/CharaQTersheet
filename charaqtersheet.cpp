#include "charaqtersheet.h"
#include <QGridLayout>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "cqts_editor.h"
#include "cqts_character.h"
#include "cqts_dataexport.h"
#include "cqts_charactercreator.h"
#include "classcreator.h"

CharaQTersheet::CharaQTersheet(QWidget *parent)
    : QMainWindow(parent)
{
    //loading the engine:
    engine = new CQTs_engine();
    //initializing pointer as NULL
    dockSkills=dockSaves=dockAbilities=dockBio=dockBAB=dockClass=NULL;
    character = NULL;

    QAction *tAct;
    QMenuBar *mainMenu = menuBar(); //an addres for symplify my life
    //files menu
    QMenu *menuFiles = mainMenu->addMenu(tr("&File"));
    tAct = menuFiles ->addAction(tr("&Save"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(saveChar()));
    tAct = menuFiles ->addAction(tr("&Open"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(loadChar()));

    menuFiles ->addSeparator();

    tAct = menuFiles ->addAction(tr("&Exit"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(close()));

    //tools menu
    QMenu *menuTools = mainMenu->addMenu(tr("&Tools"));
    tAct = menuTools ->addAction(tr("&Abilities"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(addDockAbilities()));
    tAct = menuTools ->addAction(tr("&Saves"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(addDockSaves()));
    tAct = menuTools ->addAction(tr("&Skills"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(addDockSkills()));

    menuTools->addSeparator();

    tAct = menuTools ->addAction(tr("&Bio"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(addDockBio()));

    menuTools->addSeparator();

    tAct = menuTools ->addAction(tr("&Classviewer"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(addDockClass()));

    //menu editor
    QMenu *menuEdits = mainMenu->addMenu(tr("&Edit"));
    tAct = menuEdits ->addAction(tr("&BAB"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(editBAB()));
    tAct = menuEdits ->addAction(tr("&Saves"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(editSaves()));
    tAct = menuEdits ->addAction(tr("&Abilities"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(editAbilities()));
    tAct = menuEdits ->addAction(tr("&Bio"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(editBio()));
    tAct = menuEdits ->addAction(tr("&Skills"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(editSkills()));

    //menu DM
    QMenu *menuDM = mainMenu->addMenu(tr("&DM"));
    tAct = menuDM ->addAction(tr("&Launch Class Creator"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(launchClassCreator()));
    tAct = menuDM ->addAction(tr("&Export classes"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(exportClasses()));

    menuDM->addSeparator();

    tAct = menuDM ->addAction(tr("&Launch Skill Creator"));
    tAct->setEnabled(false);
    //connect(tAct,SIGNAL(triggered()),this,SLOT(launchClassCreator()));
    tAct = menuDM ->addAction(tr("&Export skills"));
    tAct->setEnabled(false);
    //connect(tAct,SIGNAL(triggered()),this,SLOT(exportClasses()));

    //addDockClass(Qt::LeftDockWidgetArea);
    addDockBio();
    addDockAbilities();
    addDockSaves();
    addDockBAB();
    addDockSkills();
}

CharaQTersheet::~CharaQTersheet()
{
    delete engine;
}

void CharaQTersheet::addDockClass(){
    if (dockClass==NULL){
        dockClass = new QDockWidget("Classviewer");
        dockClass->setWidget(new ClassViewer(engine,dockClass));
        addDockWidget(Qt::RightDockWidgetArea,dockClass);
        dockClass->setFloating(true);
    }else
        dockClass->show();
}

void CharaQTersheet::addDockBio(){
    if(dockBio==NULL){
        dockBio = new QDockWidget("Bio");
        viewerBio = new CQTs_ChBioViewer(dockBio);
        dockBio->setWidget(viewerBio);
        addDockWidget(Qt::TopDockWidgetArea,dockBio);
    }else
        dockBio->show();
}

void CharaQTersheet::addDockAbilities(){
    if(dockAbilities==NULL){
        dockAbilities = new QDockWidget(tr("Abilities"));
        viewerAbilities = new CQTs_ChAbilitiesViewer();
        dockAbilities->setWidget(viewerAbilities);
        addDockWidget(Qt::LeftDockWidgetArea,dockAbilities);
    }else
        dockAbilities->show();
}

void CharaQTersheet::addDockBAB(){
    if(dockBAB==NULL){
        dockBAB = new QDockWidget("BAB");
        viewerBAB = new CQTs_ChBABViever(dockBAB);
        dockBAB->setWidget(viewerBAB);
        addDockWidget(Qt::LeftDockWidgetArea,dockBAB);
    }else
        dockBAB->show();
}


void CharaQTersheet::addDockSaves(){
    if(dockSaves==NULL){
        dockSaves = new QDockWidget(tr("Saves"));
        viewerST = new CQTs_ChSTViewer();
        dockSaves->setWidget(viewerST);
        addDockWidget(Qt::LeftDockWidgetArea,dockSaves);
    }else
        dockSaves->show();
}

void CharaQTersheet::addDockSkills(){
    if(dockSkills==NULL){
        dockSkills = new QDockWidget(tr("Skills"));
        viewerSkills = new CQTs_ChSkillsViewer(engine);
        dockSkills->setWidget(viewerSkills);
        addDockWidget(Qt::RightDockWidgetArea,dockSkills);
    }else
        dockSkills->show();
}

void CharaQTersheet::loadChar(){
    int ret = QMessageBox::Yes;
    if(character!=NULL){
        QMessageBox msgBox;
        msgBox.setText(tr("A character is active."));
        msgBox.setInformativeText(tr("Do you want to load another one(existig modifies will be discarded)?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        ret = msgBox.exec();
    }
    switch (ret) {
    case QMessageBox::Yes:
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Character File"), QString(),
                                                        tr("Character Files (*.chc *.CHC *.xml);;All Files (*.*)"));
        character = new CQTs_Character(fileName);
        viewerBio->setLabs(character);
        viewerAbilities->setLabs(character);
        viewerST->setLabs(character);
        viewerSkills->setLabs(character);
        viewerBAB->setLabs(character);
        break;
    }
}

void CharaQTersheet::saveChar(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Character File"), QString(),
                                                    tr("Character Files (*.chc *.CHC *.xml);;All Files (*.*)"));
    if(fileName!=""){
        character->saveToFile(fileName);
    }
}

void CharaQTersheet::exportClasses(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Classes"), QString(),
                                                    tr("xml Files (*.xml);;All Files (*.*)"));
    if(fileName!=""){
        CQTs_dataExport *data = new CQTs_dataExport(fileName,engine,CQTs_dataExport::CQTs_CLASSES);
        data->show();
    }
}
void CharaQTersheet::launchClassCreator(){
    CQTs_ClassEditor *editor = new CQTs_ClassEditor(engine);
    editor->show();
}


void CharaQTersheet::newCharacter(){
    CQTs_CharacterCreator *CharCreator = new CQTs_CharacterCreator(engine);
    character = new CQTs_Character();
}

void CharaQTersheet::editBAB(){
    if(character==NULL)
        newCharacter();

    cqts_BABeditor *BaB = new cqts_BABeditor(character->getBAB());
    connect(BaB,SIGNAL(newBAB(int)),this,SLOT(updateBAB(int)));
    BaB->show();
}
void CharaQTersheet::updateBAB(int newBAB){
    if(character==NULL)
        newCharacter();
    character->setBAB(newBAB);
    viewerBAB->setLabs(character);
}

void CharaQTersheet::editBio(){
    if(character==NULL)
        newCharacter();
    cqts_Bioeditor *Bio = new cqts_Bioeditor(character->getBio());
    connect(Bio,SIGNAL(newBio(charBio)),this,SLOT(updateBio(charBio)));
    Bio->show();
}
void CharaQTersheet::updateBio(charBio newBio){
    if(character==NULL)
        newCharacter();
    character->setBio(newBio);
    viewerBio->setLabs(character);
}

void CharaQTersheet::editSkills(){
    if(character==NULL)
        newCharacter();
    cqts_SkillsEditor *Skills = new cqts_SkillsEditor(character,engine);
    connect(Skills,SIGNAL(newSkills(QMap<QString,int>)),this,SLOT(updateSkills(QMap<QString,int>)));
    Skills->show();
}
void CharaQTersheet::updateSkills(QMap<QString,int> newskills){//need to be changed!
    if(character==NULL)
        newCharacter();
    //character->setRanks(newskills);
    viewerSkills->setLabs(character);
}

void CharaQTersheet::editSaves(){
    if(character==NULL)
        newCharacter();
    int sts[3];
    for (int i = 0; i < 3; ++i)
        sts[i]= character->getST(i);

    cqts_STeditor *STs = new cqts_STeditor(sts);
    connect(STs,SIGNAL(newSTs(int*)),this,SLOT(updateSaves(int*)));
    STs->show();
}
void CharaQTersheet::updateSaves(int* STs){
    character->setST(STs[0],STs[1],STs[2]);
    viewerST->setLabs(character);
}

void CharaQTersheet::editAbilities(){
    if(character==NULL)
        newCharacter();
    cqts_AbilitiesEditor *Abl = new cqts_AbilitiesEditor(character->getAbilities());
    connect(Abl,SIGNAL(newAbl(int*)),this,SLOT(updateAbilities(int*)));
    Abl->show();
}
void CharaQTersheet::updateAbilities(int* abls){
    if(character==NULL)
        newCharacter();
    character->setAbilities(abls);
    viewerAbilities->setLabs(character);
    viewerST->setLabs(character);
    viewerSkills->setLabs(character);
    viewerBAB->setLabs(character);
}


/*Classviewer*/
ClassViewer::ClassViewer(CQTs_engine *eng, QWidget *parent)
    : QWidget(parent)
{
    engine = eng;
    QStringList listclass = engine->classNames();
    QGridLayout *grid = new QGridLayout();
    comboClass = new QComboBox();
    comboClass->addItems(listclass);
    QLabel *TLab = new QLabel(tr("Search:"));
    grid->addWidget(TLab,0,0);
    grid->addWidget(comboClass,0,1);
    viewer = new CQTs_ClassViewer();
    grid->addWidget(viewer,1,0,2,2);
    setLayout(grid);
    if (listclass.size()>0){
        selClass(0);
    }
    //connections
    connect(comboClass,SIGNAL(currentIndexChanged(int)),this,SLOT(selClass(int)));
}

ClassViewer::~ClassViewer()
{

}

void ClassViewer::selClass(int selected){
    CQTs_Class classSel = engine->classData(selected);
    viewer->setLabs(&classSel);
}
