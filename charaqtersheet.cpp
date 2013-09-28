#include "charaqtersheet.h"
#include <QGridLayout>
#include <QDockWidget>

CharaQTersheet::CharaQTersheet(QWidget *parent)
    : QMainWindow(parent)
{
    //NOTE: the menubar IS a placeholder, for now
    QMenuBar *mainMenu = menuBar(); //an addres for symplify my life
    QMenu *menuFiles = mainMenu->addMenu(tr("&File"));
    menuFiles ->addAction(tr("&Save"));
    menuFiles ->addAction(tr("&Open"));
    menuFiles ->addSeparator();
    menuFiles ->addAction(tr("&Exit"));

    addDockClass(Qt::LeftDockWidgetArea);
    addDockBio(Qt::LeftDockWidgetArea);
    addDockAbilities(Qt::LeftDockWidgetArea);
    addDockSaves(Qt::RightDockWidgetArea);
    addDockSkills(Qt::RightDockWidgetArea);
}

CharaQTersheet::~CharaQTersheet()
{

}

void CharaQTersheet::addDockClass(Qt::DockWidgetArea area){
    QDockWidget *dockClass = new QDockWidget("Classviewer");
    dockClass->setWidget(new ClassViewer(dockClass));
    addDockWidget(area,dockClass);
}

void CharaQTersheet::addDockBio(Qt::DockWidgetArea area){
    QDockWidget *dockBio = new QDockWidget("Bio");
    //dockClass->setWidget();
    addDockWidget(area,dockBio);
}

void CharaQTersheet::addDockAbilities(Qt::DockWidgetArea area){
    QDockWidget *dockAbilities = new QDockWidget(tr("Abilities"));
    //dockClass->setWidget();
    addDockWidget(area,dockAbilities);
}

void CharaQTersheet::addDockSaves(Qt::DockWidgetArea area){
    QDockWidget *dockSaves = new QDockWidget(tr("Saves"));
    //dockClass->setWidget();
    addDockWidget(area,dockSaves);
}

void CharaQTersheet::addDockSkills(Qt::DockWidgetArea area){
    QDockWidget *dockSkills = new QDockWidget(tr("Skills"));
    //dockClass->setWidget();
    addDockWidget(area,dockSkills);
}

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
