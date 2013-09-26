#include "cqts_classviewer.h"
#include <QLabel>
#include <QGridLayout>

CQTs_ClassViewer::CQTs_ClassViewer(QWidget *parent) :
    QGroupBox(tr("Class Viewer"),parent)
{
    QGridLayout *grid = new QGridLayout();

    QLabel *Tlab = new QLabel(tr("Name:"));
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

    setLayout(grid);
}

