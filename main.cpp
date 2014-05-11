//#include "charaqtersheet.h"

#include "items.h"
#include "item_editor.h"
#include <QApplication>
#include <QDebug>

#include "cqts_engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // CQTs_ItemViewer w;
    QStringList Items, Names;
    //Items.push_back("E:/Users/Iximiel/Documents/GitHub/CharaQTersheet-MinGW/goods.xml");
    Items.push_back("/home/iximiel/ProgettiQt/CharaQTersheet/xml/goods.xml");
    CQTs_itemsHandler h(Items,Names);
    CQTs_bag w(h.getItem(0));
    for (int i = 1; i < 10; ++i) {
        w.put_inside(h.getItem(i));
    }
    //CQTs_ItemEditor w;
    //CharaQTersheet w;
    w.show();
    //CQTs_Character prova("/home/iximiel/ProgettiQt/build-CharaQTersheet-Debug/testcharacter2.xml");
    return a.exec();
}
