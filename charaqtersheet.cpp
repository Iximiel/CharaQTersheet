#include "charaqtersheet.h"
#include <QGridLayout>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>

CharaQTersheet::CharaQTersheet(QWidget *parent)
    : QMainWindow(parent)
{
    //loading the engine:
    character = new CQTs_Character("testcharacter.xml");
    engine = new CQTs_engine();
    //initializing pointer as NULL
    dockSkills=dockSaves=dockAbilities=dockBio=dockBAB=dockClass=NULL;

    QAction *tAct;
    QMenuBar *mainMenu = menuBar(); //an addres for symplify my life
    QMenu *menuFiles = mainMenu->addMenu(tr("&File"));
    tAct = menuFiles ->addAction(tr("&Save"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(saveChar()));
    tAct = menuFiles ->addAction(tr("&Open"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(loadChar()));

    menuFiles ->addSeparator();

    tAct = menuFiles ->addAction(tr("&Exit"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(close()));
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

    //addDockClass(Qt::LeftDockWidgetArea);
    addDockBio();
    addDockAbilities();
    addDockSaves();
    addDockBAB();
    addDockSkills();
}

CharaQTersheet::~CharaQTersheet()
{

}

void CharaQTersheet::addDockClass(){
    if (dockClass==NULL){
        dockClass = new QDockWidget("Classviewer");
        dockClass->setWidget(new ClassViewer(dockClass));
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
        CQTs_ChBABViever *viewerBAB = new CQTs_ChBABViever(dockBAB);
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
        CQTs_ChSkillsViewer *viewerSkills = new CQTs_ChSkillsViewer(engine);
        dockSkills->setWidget(viewerSkills);
        addDockWidget(Qt::RightDockWidgetArea,dockSkills);
    }else
        dockSkills->show();
}

void CharaQTersheet::loadChar(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Character File"), QString(),
                tr("Character Files (*.chc *CHC);;All Files (*.*)"));
    character = new CQTs_Character(fileName);
    viewerBio->setLabs(character);
    viewerAbilities->setLabs(character);
    viewerST->setLabs(character);
    //viewerSkills->setLabs(character);
}

void CharaQTersheet::saveChar(){
    QMessageBox::information(0, QString("Information"), QString("Save funcion is useless, for now"), QMessageBox::Ok);
}

/*Classviewer*/
ClassViewer::ClassViewer(QWidget *parent)
    : QWidget(parent)
{
    QStringList listclass = extensionFind("*.ClC");
    QGridLayout *grid = new QGridLayout();
    comboClass = new QComboBox();
    comboClass->addItems(listclass);
    QLabel *TLab = new QLabel(tr("Search:"));
    grid->addWidget(TLab,0,0);
    grid->addWidget(comboClass,0,1);
    viewer = new CQTs_ClassViewer();
    grid->addWidget(viewer,1,0,2,2);
    setLayout(grid);

    //connections
    connect(comboClass,SIGNAL(currentTextChanged(QString)),this,SLOT(selClass(QString)));
}

ClassViewer::~ClassViewer()
{

}

void ClassViewer::selClass(QString selected){
    CQTs_Class *classSel = new CQTs_Class(selected);
    viewer->setLabs(classSel);
}
