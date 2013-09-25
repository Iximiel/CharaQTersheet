#include "charaqtersheet.h"

CharaQTersheet::CharaQTersheet(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *mainMenu = menuBar(); //an addres for symplify my life
   // QMenu *menuFiles =
    mainMenu->addMenu("&File");
}

CharaQTersheet::~CharaQTersheet()
{

}
