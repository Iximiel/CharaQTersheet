#include "charaqtersheet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CharaQTersheet w;
    w.show();

    return a.exec();
}
