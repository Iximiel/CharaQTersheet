#include "cqts_editor.h"

#include <QFormLayout>
#include <QLayout>

cqts_BABeditor::cqts_BABeditor(int oldBAB, QWidget *parent):
    QWidget(parent)
{
    QFormLayout *grid = new QFormLayout(this);

    newSpinBaB = new QSpinBox();
    newSpinBaB->setValue(oldBAB);
    grid->addRow("BaB:",newSpinBaB);

    saveBTT = new QPushButton("&Save");
    undoBTT = new QPushButton("&Undo");
    QHBoxLayout *tLay= new QHBoxLayout();
    tLay->addWidget(undoBTT);
    tLay->addWidget(saveBTT);
    connect(undoBTT,SIGNAL(clicked()),this,SLOT(close()));
    connect(saveBTT,SIGNAL(clicked()),this,SLOT(update()));
    grid->addRow(tLay);
    setLayout(grid);
}

cqts_BABeditor::~cqts_BABeditor(){

}

void cqts_BABeditor::update(){
    emit newBAB(newSpinBaB->value());
}
/*
int cqts_BABeditor::newBAB(int bab){
    return bab;
}*/
