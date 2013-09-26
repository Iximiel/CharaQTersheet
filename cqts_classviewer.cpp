#include "cqts_classviewer.h"
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QDir>
#include <QStringList>
#include <QDebug>

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

    QComboBox *ComboSel = new QComboBox();

    grid->addWidget(ComboSel,0,1);
    //protocol to get list of files, may export it
    QDir currentDir;
    qDebug() << currentDir.dirName();

    QStringList files;
    files = currentDir.entryList(QStringList("*.ClC"),QDir::Files | QDir::NoSymLinks);
    int total =files.length();
    for (int i = 0; i < total; ++i) {
        qDebug() << files [i];
    }
    setLayout(grid);
}
