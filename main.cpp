#include "charaqtersheet.h"
#include "cqts_viewers.h"
#include "items.h"
#include <QApplication>
#include <QDebug>

#include "cqts_engine.h"

int main(int argc, char *argv[])
{
    money asd(7,9,50,5),sad(500),das(0,6,0);
    qDebug() << asd.value();
    qDebug() << das.value();
    qDebug() << sad.value();
    QApplication a(argc, argv);
   // CharaQTersheet w;
    //CQTs_Class prova("mnc");
    //CQTs_ClassViewer w(&prova);
    //ClassViewer w;
   // w.show();
    //CQTs_Character prova("/home/iximiel/ProgettiQt/build-CharaQTersheet-Debug/testcharacter2.xml");
    return 0;//a.exec();
}
