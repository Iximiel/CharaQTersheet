#include "cqts_classviewer.h"
#include "cqts_engine.h"
#include <QLabel>
#include <QGridLayout>
#include<iostream>

CQTs_ClassViewer::CQTs_ClassViewer(QWidget *parent) :
    QGroupBox(tr("Class Viewer"),parent)
{
    QGridLayout *grid = new QGridLayout();

    QLabel *Tlab = new QLabel(tr("Class:"));
    grid->addWidget(Tlab,0,0);

    Tlab = new QLabel(tr("Base Attack bonus:"));
    grid->addWidget(Tlab,1,0);

    QGroupBox *SavesBox= new QGroupBox(tr("Saves:"));
    grid->addWidget(SavesBox,2,0,1,2);
    QGridLayout *grid2 = new QGridLayout();
    Tlab = new QLabel(tr("Fortitude:"));
    grid2->addWidget(Tlab,0,0);
    Tlab = new QLabel(tr("Reflexes"));
    grid2->addWidget(Tlab,1,0);
    Tlab = new QLabel(tr("Will:"));
    grid2->addWidget(Tlab,2,0);
    SavesBox->setLayout(grid2);

    ComboSel = new QComboBox();
    grid->addWidget(ComboSel,0,1);

    connect(ComboSel,SIGNAL(currentIndexChanged(int)),this,SLOT(selected(int)));

    ComboSel->addItems(extensionFind("*.ClC"));
    setLayout(grid);
}

void CQTs_ClassViewer::selected(int id){
std::cout << id<<std::endl;
}
