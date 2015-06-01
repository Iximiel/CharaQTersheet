#include <QApplication>
#include <QDebug>
#include <QTranslator>

#include "charaqtersheet.h"
#include "cqts_charactercreator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QTranslator translator;
    translator.load("charaqtersheet_it");
    a.installTranslator(&translator);*/
    CharaQTersheet w;

 /*   CQTs_engine *engine = new CQTs_engine();
    CQTs_CharacterCreator w(engine);

    CQTs_Class prova;
    prova = engine->classData(10);
    CQTs_ClassEditor w(prova,engine);
    //CQTs_Class *c = new CQTs_Class();
    CQTs_ClassViewer *w = new CQTs_ClassViewer();
    CQTs_engine engi;// = new CQTs_engine();
    CQTs_Class tclass = (engi.classData(0));
    w->setLabs(&tclass);
    w->show();*/
    w.show();
    return a.exec();
}
