#include "cqts_charactercreator.h"
#include <QStringList>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
//let it be a wizard
CQTs_CharacterCreator::CQTs_CharacterCreator(CQTs_engine *eng, QWidget *parent)
    : QWidget(parent)
{
    engine = eng;
    QStringList listclass = engine->classNames();
    QGridLayout *grid = new QGridLayout();
    QComboBox *comboClass = new QComboBox();
    comboClass->addItems(listclass);
    QLabel *TLab = new QLabel(tr("Search:"));
    grid->addWidget(TLab,0,0);
    grid->addWidget(comboClass,0,1);
    //viewer = new CQTs_ClassViewer();
    //grid->addWidget(viewer,1,0,2,2);
    setLayout(grid);
}
    /*if (listclass.size()>0){
        selClass(0);
    }
    //connections
    //connect(comboClass,SIGNAL(currentIndexChanged(int)),this,SLOT(selClass(int)));
}
/*
void ClassViewer::selClass(int selected){
    CQTs_Class classSel = engine->classData(selected);
    viewer->setLabs(&classSel);
}*/

