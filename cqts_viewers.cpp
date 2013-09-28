#include "cqts_viewers.h"
#include <QGridLayout>

CQTs_Viewer::CQTs_Viewer(QString title, QWidget *parent) :
    QGroupBox(title,parent)
{
    initialize();
}

CQTs_ClassViewer::CQTs_ClassViewer(QWidget *parent) :
    CQTs_Viewer(tr("Class Viewer"),parent)
{

}

CQTs_ClassViewer::CQTs_ClassViewer(CQTs_Class *selected, QWidget *parent) :
    CQTs_Viewer(tr("Class Viewer"),parent)
{
    setLabs(selected);
}

void CQTs_ClassViewer::initialize(){

    LabName = new QLabel();
    LabBAB = new QLabel();
    LabFort = new QLabel();
    LabRef = new QLabel();
    LabWill = new QLabel();

    QGridLayout *grid = new QGridLayout();

    QLabel *Tlab = new QLabel(tr("Name:"));
    grid->addWidget(Tlab,0,0);
    grid->addWidget(LabName,0,1);

    Tlab = new QLabel(tr("Base Attack Bonus:"));
    grid->addWidget(Tlab,1,0);
    grid->addWidget(LabBAB,1,1);

    QGroupBox *SavesBox= new QGroupBox(tr("Saves:"));
    grid->addWidget(SavesBox,2,0,1,2);
    QGridLayout *grid2 = new QGridLayout();
    Tlab = new QLabel(tr("Fortitude:"));
    grid2->addWidget(Tlab,0,0);
    grid2->addWidget(LabFort,0,1);
    Tlab = new QLabel(tr("Reflexes"));
    grid2->addWidget(Tlab,1,0);
    grid2->addWidget(LabRef,1,1);
    Tlab = new QLabel(tr("Will:"));
    grid2->addWidget(Tlab,2,0);
    grid2->addWidget(LabWill,2,1);
    SavesBox->setLayout(grid2);

    setLayout(grid);
}


void CQTs_ClassViewer::setLabs(CQTs_Class *selected){
    QString bonus[4]={tr("error"),tr("Poor"),tr("Good"),tr("Average")};

    LabName ->setText(selected->className());
    LabBAB ->setText(bonus[selected->classBAB()]);
    LabFort ->setText(bonus[1+selected->STFort()]);
    LabRef ->setText(bonus[1+selected->STRef()]);
    LabWill ->setText(bonus[1+selected->STWill()]);
}
