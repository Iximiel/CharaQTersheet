#include "cqts_charactercreator.h"

#include <QStringList>
#include <QGridLayout>
#include <QFormLayout>
#include <QScrollArea>

//need to do ALL the registerField("className*", classNameLineEdit);

//let it be a wizard
CQTs_CharacterCreator::CQTs_CharacterCreator(CQTs_engine *eng, QWidget *parent)
    : QWizard(parent)
{
    engine = eng;
    setWindowTitle(tr("Create Character"));
    choseClass *pageclass = new choseClass(engine);
    choseBio *pagebio = new choseBio(engine);
    choseSkills *pageskills = new choseSkills(engine);
    addPage(pagebio);
    addPage(pageclass);
    addPage(pageskills);
}

void CQTs_CharacterCreator::accept(){
    QString Name = field("myName").toString();
    QString Surname = field("mySurname").toString();
    int Age = field("myAge").toInt();
    QString ClassCode = field("myClass").toString();
    QDialog::accept();
}

/*bio*/
choseBio::choseBio(CQTs_engine* eng, QWidget *parent)
    : QWizardPage(parent)
{
    engine = eng;
    setTitle(tr("Set your basic infos"));
    QFormLayout *form = new QFormLayout();
    form->addRow(tr("Your name:"),LineName = new QLineEdit());
    form->addRow(tr("Your surname:"),LineSurname = new QLineEdit());
    form->addRow(tr("Your age:"),SpinAge = new QSpinBox());
    SpinAge->setMaximum(9999);
    registerField("myName",LineName);
    registerField("mySurname",LineSurname);
    registerField("myAge",SpinAge);
    setLayout(form);
}
/*class*/
choseClass::choseClass(CQTs_engine *eng, QWidget *parent)
    : QWizardPage(parent)
{
    engine = eng;
    setTitle(tr("Set first class"));
    QStringList listclass = engine->classNames();
    QGridLayout *grid = new QGridLayout();
    comboClass = new QComboBox();
    comboClass->addItems(listclass);
    QLabel *TLab = new QLabel(tr("Choose your first class:"));
    TLab->setWordWrap(true);
    grid->addWidget(TLab,0,0);
    grid->addWidget(comboClass,0,1);
    viewer = new CQTs_ClassViewer();
    grid->addWidget(viewer,1,0,2,2);

    setLayout(grid);

    registerField("myClass",comboClass);
    //connections
    connect(comboClass,SIGNAL(currentIndexChanged(int)),this,SLOT(selClass(int)));
    if (listclass.size()>0){
        selClass(0);
    }

}

void choseClass::selClass(int selected){
    CQTs_Class classSel = engine->classData(selected);
    viewer->setLabs(&classSel,5);
}

/*skills*/
choseSkills::choseSkills(CQTs_engine* eng, QWidget *parent){
    engine = eng;
    setTitle(tr("Set your skillponts"));

    QWidget *container = new QWidget();
    QScrollArea *scroll = new QScrollArea();
    //setting up layouts
    QVBoxLayout *maingrid = new QVBoxLayout();
    QFormLayout *secgrid = new QFormLayout();
    maingrid->addWidget(scroll);
    spinSkills = new QSpinBox*[engine->skillNum()];
    for(int i=0 ; i < engine->skillNum() ; i++){
        spinSkills[i] = new QSpinBox();
        spinSkills[i]->setMaximum(4);
        secgrid->addRow(engine->skillData(i).myName(),spinSkills[i]);
        QString field = "mySkillN" + QString::number(i);
        registerField(field,spinSkills[i]);
    }
    setLayout(maingrid);
    container->setLayout(secgrid);
    scroll->setWidget(container);
}
