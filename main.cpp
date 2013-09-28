#include "charaqtersheet.h"
#include "cqts_viewers.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CharaQTersheet w;
    //CQTs_Class prova("mnc");
    //CQTs_ClassViewer w(&prova);
    //ClassViewer w;
    w.show();
    CQTs_Character prova("character");

    return a.exec();
}
