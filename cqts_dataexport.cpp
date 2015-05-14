#include "cqts_dataexport.h"
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

CQTs_dataExport::CQTs_dataExport(QString file, CQTs_engine *eng, CQTsdata setup, QWidget *parent)
    : QWidget(parent),filename(file)
{
    engine = eng;
    todo = setup;
    QGridLayout *grid = new QGridLayout();
    if(todo == CQTs_CLASSES){
        grid->addWidget(loadClasses(),0,0,1,2);
    }
    grid->addWidget(new QPushButton(tr("Undo")),1,0);
    grid->addWidget(new QPushButton(tr("Ok")),1,1);
    setLayout(grid);
}

QWidget *CQTs_dataExport::loadClasses(){
    QWidget *mywidget = new QWidget();
    QGridLayout *mygrid = new QGridLayout();
    QString text = tr("Select the classes to export in ");
    mygrid->addWidget(new QLabel(text),0,0,1,2);
    mygrid->addWidget(new QLabel(filename),1,0,1,2);
    for(int i=0;i<engine->classNum();i++){
        mygrid->addWidget(new QCheckBox(engine->classData(i).myName()),i+2,0,2,1);
    }
    mywidget->setLayout(mygrid);
    return mywidget;
}
