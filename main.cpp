#include <QApplication>

#include "charaqtersheet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //CharaQTersheet w;
    //CQTs_Class *c = new CQTs_Class();
    CQTs_ClassViewer *w = new CQTs_ClassViewer();
    CQTs_engine engi;// = new CQTs_engine();
    CQTs_Class tclass = (engi.classData(0));
    w->setLabs(&tclass);
    w->show();
    return a.exec();
}
