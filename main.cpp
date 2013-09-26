#include "charaqtersheet.h"
#include "cqts_classviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //CharaQTersheet w;
    CQTs_Class prova("mnc");
    CQTs_ClassViewer w(&prova);
    w.show();

    return a.exec();
}
