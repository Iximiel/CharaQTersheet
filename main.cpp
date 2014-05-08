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
    CQTs_bag w(h.getItem(0));
    for (int i = 1; i < 10; ++i) {
        w.put_inside(h.getItem(i));
    }

    //CharaQTersheet w;
    w.show();
    //CQTs_Character prova("/home/iximiel/ProgettiQt/build-CharaQTersheet-Debug/testcharacter2.xml");
    return a.exec();
}
