#include "cqts_editor.h"

#include <QFormLayout>
#include <QLayout>
//BAB
cqts_BABeditor::cqts_BABeditor(int oldBAB, QWidget *parent):
    QWidget(parent)
{
    QFormLayout *grid = new QFormLayout(this);

    newSpinBaB = new QSpinBox();
    newSpinBaB->setValue(oldBAB);
    grid->addRow(tr("BaB:"),newSpinBaB);

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
//ST
cqts_STeditor::cqts_STeditor(int oldSTs[3],QWidget *parent):
    QWidget(parent)
{
    QFormLayout *grid = new QFormLayout(this);

    newSpinST = new QSpinBox* [3];
    QString Names[3]={tr("Fortitude"),tr("Reflex"),tr("Will")};
    for (int i = 0; i < 3; ++i) {
        newSpinST[i] = new QSpinBox();
        newSpinST[i]->setValue(oldSTs[i]);
        grid->addRow(Names[i],newSpinST[i]);
    }

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

cqts_STeditor::~cqts_STeditor(){

}

void cqts_STeditor::update(){
    int ST[3];
    for (int i = 0; i < 3; ++i)
        ST[i] = newSpinST[i]->value();

    emit newSTs(ST);
}

//Bio
cqts_Bioeditor::cqts_Bioeditor(charBio old,QWidget *parent):
    QWidget(parent)
{
    QFormLayout *grid = new QFormLayout(this);

    newSpinName = new QLineEdit();
    grid->addRow(tr("Name:"),newSpinName);
    newSpinName->setText(old.Name);
    newSpinSurname = new QLineEdit();
    grid->addRow(tr("Surname:"),newSpinSurname);
    newSpinSurname->setText(old.Surname);
    newSpinAge = new QSpinBox();
    grid->addRow(tr("Age:"),newSpinAge);
    newSpinAge->setValue(old.age);


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

cqts_Bioeditor::~cqts_Bioeditor(){

}

void cqts_Bioeditor::update(){
    charBio bio;
    bio.Name = newSpinName->text();
    bio.Surname = newSpinSurname->text();
    bio.age = newSpinAge->value();

    emit newBio(bio);
}
