#include "cqts_dataexport.h"
#include <QGridLayout>
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
    QPushButton *tUndo = new QPushButton(tr("Undo"));
    QPushButton *tOk = new QPushButton(tr("Ok"));
    grid->addWidget(tUndo,1,0);
    grid->addWidget(tOk,1,1);
    connect(tUndo,SIGNAL(pressed()),this,SLOT(close()));
    connect(tOk,SIGNAL(pressed()),this,SLOT(doExport()));
    setLayout(grid);
}

QWidget* CQTs_dataExport::loadClasses(){
    QWidget *mywidget = new QWidget();
    QGridLayout *mygrid = new QGridLayout();
    QString text = tr("Select the classes to export in:");
    mygrid->addWidget(new QLabel(text),0,0,1,2);
    mygrid->addWidget(new QLabel(filename),1,0,1,2);
    int num = engine->classNum();
    datacontainer = new QCheckBox*[num];
    for(int i=0;i<num;i++){
        datacontainer[i] = new QCheckBox(engine->classData(i).myName());
        mygrid->addWidget(datacontainer[i],i+2,0,2,1);
    }
    mywidget->setLayout(mygrid);
    return mywidget;
}

void CQTs_dataExport::doExport(){

    close();
}
