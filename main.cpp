#include "charaqtersheet.h"
#include "cqts_classviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //CharaQTersheet w;
    CQTs_ClassViewer w;
    w.show();

    return a.exec();
}
