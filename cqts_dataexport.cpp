#include "cqts_dataexport.h"
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>

CQTs_dataExport::CQTs_dataExport(QString file, CQTs_engine *eng, CQTsdata setup, QWidget *parent)
    : QWidget(parent),filename(file)
{
    engine = eng;
    todo = setup;
    if(todo == CQTs_CLASSES){
        loadClasses();
    }
}

void CQTs_dataExport::loadClasses(){
    QGridLayout *grid = new QGridLayout();
    QString text = tr("Select the classes to export in ") + filename;
    grid->addWidget(new QLabel(text),0,0,0,2);
    for(int i=0;i<engine->classNum();i++){

    }
}
