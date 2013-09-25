#include "charaqtersheet.h"

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
