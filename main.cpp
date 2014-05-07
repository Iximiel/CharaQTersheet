//#include "charaqtersheet.h"

#include "items.h"
#include <QApplication>
#include <QDebug>

#include "cqts_engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList Items, Names;
    Items.push_back("E:/Users/Iximiel/Documents/GitHub/CharaQTersheet-MinGW/goods.xml");
    CQTs_itemsHandler h(Items,Names);
    CQTs_bag w;
    w.put_inside(h.getItem(6));
    w.put_inside(h.getItem(55));
    w.put_inside(h.getItem(8));
    w.put_inside(h.getItem(63));
    w.put_inside(h.getItem(6));
    //CharaQTersheet w;
    w.show();
    //CQTs_Character prova("/home/iximiel/ProgettiQt/build-CharaQTersheet-Debug/testcharacter2.xml");
    return a.exec();
}
