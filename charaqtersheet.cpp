#include "charaqtersheet.h"

CharaQTersheet::CharaQTersheet(QWidget *parent)
    : QMainWindow(parent)
{
    //NOTE: the menubar IS a placeholder, for now
    QMenuBar *mainMenu = menuBar(); //an addres for symplify my life
    QMenu *menuFiles = mainMenu->addMenu("&File");
    menuFiles ->addAction("&Save");
    menuFiles ->addAction("&Open");
    menuFiles ->addSeparator();
    menuFiles ->addAction("&Exit");

}

CharaQTersheet::~CharaQTersheet()
{

}
