#include "cqts_editors.h"

#include <QLayout>
#include <QFormLayout>
BABeditor::BABeditor(QWidget *parent):
    QWidget(parent)
{
    QFormLayout *grid = new QFormLayout(this);

    newSpinBaB = new QSpinBox();
    grid->addRow("BaB:",newSpinBaB);

    saveBTT = new QPushButton("&Save");
    undoBTT = new QPushButton("&Undo");
    QHBoxLayout *tLay= new QHBoxLayout();
    tLay->addWidget(undoBTT);
    tLay->addWidget(saveBTT);
    //connect(undoBTT,SIGNAL(clicked()),BaB,SLOT(close()));
    //connect(saveBTT,SIGNAL(clicked()),this,SLOT(updateBaB(int newSpinBaB->value())));
    //connect();
    grid->addRow(tLay);
    setLayout(grid);
}
