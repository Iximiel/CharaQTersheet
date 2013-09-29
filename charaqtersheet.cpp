#include "charaqtersheet.h"
#include <QGridLayout>
#include <QDockWidget>

CharaQTersheet::CharaQTersheet(QWidget *parent)
    : QMainWindow(parent)
{
    //initializing pointer as NULL
    dockSkills=dockSaves=dockAbilities=dockBio=dockClass=NULL;
    //NOTE: the menubar IS a placeholder, for now
    QMenuBar *mainMenu = menuBar(); //an addres for symplify my life
    QMenu *menuFiles = mainMenu->addMenu(tr("&File"));
    menuFiles ->addAction(tr("&Save"));
    menuFiles ->addAction(tr("&Open"));
    menuFiles ->addSeparator();
    menuFiles ->addAction(tr("&Exit"));
    QMenu *menuTools = mainMenu->addMenu(tr("&Tools"));
    QAction *tAct = menuTools ->addAction(tr("&Classviewer"));
    connect(tAct,SIGNAL(triggered()),this,SLOT(addDockClass()));

    //addDockClass(Qt::LeftDockWidgetArea);
    addDockBio();
    addDockAbilities();
    addDockSaves();
    addDockSkills();
}

CharaQTersheet::~CharaQTersheet()
{

}

void CharaQTersheet::addDockClass(){
    if (dockClass==NULL){
        dockClass = new QDockWidget("Classviewer");
        dockClass->setWidget(new ClassViewer(dockClass));
        addDockWidget(Qt::LeftDockWidgetArea,dockClass);
    }else
        dockClass->show();

}

void CharaQTersheet::addDockBio(){
    dockBio = new QDockWidget("Bio");
    dockBio->setWidget(new CQTs_ChBioViewer(dockBio));
    addDockWidget(Qt::LeftDockWidgetArea,dockBio);
}

void CharaQTersheet::addDockAbilities(){
    dockAbilities = new QDockWidget(tr("Abilities"));
    //dockAbilities->setWidget();
    addDockWidget(Qt::LeftDockWidgetArea,dockAbilities);
}

void CharaQTersheet::addDockSaves(){
    dockSaves = new QDockWidget(tr("Saves"));
    //dockSaves->setWidget();
    addDockWidget(Qt::RightDockWidgetArea,dockSaves);
}

void CharaQTersheet::addDockSkills(){
    dockSkills = new QDockWidget(tr("Skills"));
    //dockSkills->setWidget();
    addDockWidget(Qt::RightDockWidgetArea,dockSkills);
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
