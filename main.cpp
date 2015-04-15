#include <QApplication>

#include "charaqtersheet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CharaQTersheet w;
    //CQTs_Class *c = new CQTs_Class();
    //CQTs_ClassViewer w();
    w.show();
    return a.exec();
}
