#include "cqts_dataexport.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>

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
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to save your classes")), QMessageBox::Ok);
    }else{
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("classes");//opening classes
        int num = engine->classNum();
        for(int i=0;i<num;i++){
            if(datacontainer[i]->isChecked()){
                engine->classData(i).writeDatatoXml(xml);
            }
        }
        xml.writeEndElement();//classes
        xml.writeEndDocument();
    }
    close();
    delete this;
}
