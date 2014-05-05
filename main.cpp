//#include "charaqtersheet.h"

#include "items.h"
#include <QApplication>
#include <QDebug>

#include "cqts_engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CQTs_ItemViewer w;
    //CharaQTersheet w;
    w.show();
    //CQTs_Character prova("/home/iximiel/ProgettiQt/build-CharaQTersheet-Debug/testcharacter2.xml");
    return a.exec();
}
