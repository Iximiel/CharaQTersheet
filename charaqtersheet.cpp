#include "charaqtersheet.h"
#include <QGridLayout>
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

}

CharaQTersheet::~CharaQTersheet()
{

}


ClassViewer::ClassViewer(QWidget *parent)
    : QDockWidget(parent)
{
    QStringList listclass = extensionFind("*.ClC");
    QGridLayout *grid = new QGridLayout(this);
    comboClass = new QComboBox();
    comboClass->addItems(listclass);
    QLabel *TLab = new QLabel(tr("Search:"));
    grid->addWidget(TLab,0,0);
    grid->addWidget(comboClass,0,1);
    setLayout(grid);
}

ClassViewer::~ClassViewer()
{

}

void ClassViewer::selClass(QString selected){

}
