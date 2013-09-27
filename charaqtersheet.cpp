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
    QDockWidget *dockClass = new QDockWidget;
    dockClass->setWidget(new ClassViewer(dockClass));
    addDockWidget(Qt::LeftDockWidgetArea,dockClass);
}

CharaQTersheet::~CharaQTersheet()
{

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
