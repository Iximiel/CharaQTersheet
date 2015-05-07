#include "classcreator.h"

#include <QLabel>
//#include <QGridLayout>
#include <QFormLayout>


/*CLASSCREATOR*/
CQTs_ClassEditor::CQTs_ClassEditor(CQTs_engine *eng, QWidget *parent)
    : QWidget(parent)
{
    engine = eng;
    initialize();
}

CQTs_ClassEditor::CQTs_ClassEditor(CQTs_Class oldclass, CQTs_engine *eng, QWidget *parent)
    : QWidget(parent)
{
    engine = eng;
    initialize();
    setLabels(oldclass);
}

void CQTs_ClassEditor::initialize(){
    QLabel *tLabel = new QLabel(tr("Name (in english):"));
    QFormLayout *grid = new QFormLayout();
    //Name
    Line_Name = new  QLineEdit();
    grid->addRow(tLabel,Line_Name);
    //Hit Die
    tLabel = new QLabel(tr("Hit Die:"));
    Combo_HD = new QComboBox();
    QStringList List;
    List <<"d4"<<"d6"<<"d8"<<"d10"<<"d12";
    Combo_HD->addItems(List);
    grid->addRow(tLabel,Combo_HD);
    //Skill points
    tLabel = new QLabel(tr("Skill Points at Each Level:"));
    List.clear();
    List << "2" << "4" << "6" << "8";
    Combo_Ranks = new QComboBox();
    Combo_Ranks->addItems(List);
    grid->addRow(tLabel,Combo_Ranks);
    //BAB
    List.clear();
    List << tr("Poor") << tr("Average") << tr("Good");
    Combo_BaB = new QComboBox();
    Combo_BaB->addItems(List);
    tLabel = new QLabel(tr("Base Attack Bonus:"));
    //Save trows
    List.clear();
    List << tr("Poor") << tr("Good");
    grid->addRow(tLabel,Combo_BaB);
    Combo_TSFort = new QComboBox();
    Combo_TSFort->addItems(List);
    tLabel = new QLabel(tr("Base save: Fortitude:"));
    grid->addRow(tLabel,Combo_TSFort);
    Combo_TSRef = new QComboBox();
    Combo_TSRef->addItems(List);
    tLabel = new QLabel(tr("Base save: Reflexes:"));
    grid->addRow(tLabel,Combo_TSRef);
    Combo_TSWill = new QComboBox();
    Combo_TSWill->addItems(List);
    tLabel = new QLabel(tr("Base save: Will:"));
    grid->addRow(tLabel,Combo_TSWill);
    //infos
    BT_Weapon = new QPushButton(tr("Set Weapons Proficiency"));
    BT_Armor = new QPushButton(tr("Set Armor Proficiency"));
    BT_Skills = new QPushButton(tr("Set Class Skills"));
    BT_Weapon->setEnabled(false);
    grid->addRow(BT_Weapon);
    BT_Armor->setEnabled(false);
    grid->addRow(BT_Armor);
    grid->addRow(BT_Skills);
    QScrollArea *Scroll_Levels = new QScrollArea();
    grid->addRow(Scroll_Levels);
    QFormLayout *Levelgrid = new QFormLayout();
    Levelgrid->addRow(new QLabel("1:"),new QPushButton(tr("Add Level")));
    Scroll_Levels->setLayout(Levelgrid);
    QPushButton *tbutt1 = new QPushButton(tr("Save and Exit"));
    QPushButton *tbutt2 = new QPushButton(tr("Exit"));
    connect(tbutt1,SIGNAL(pressed()),this,SLOT(saveAndExit()));
    connect(tbutt2,SIGNAL(pressed()),this,SLOT(close()));
    grid->addRow(tbutt2,tbutt1);
    setLayout(grid);
}

void CQTs_ClassEditor::setLabels(CQTs_Class oldclass){

}

void CQTs_ClassEditor::launchSkillSelector(){}
void CQTs_ClassEditor::saveAndExit(){
    QString code = Line_Name->text();
    bool data[5]={0,0,0,0,0};
    int dv,ranks, lmax;
    /**temporaneo**/
    lmax = 20;
    /****/
    ranks = Combo_Ranks->currentText().toInt();
    dv = Combo_HD->currentText().toInt();
    CQTs_Class newclass(code,data,dv,ranks,lmax);
    emit getClass(newclass);
    close();
}
/*void CQTs_ClassEditor::launchArmorSelector(){}
void CQTs_ClassEditor::launchWeaponSelector(){}*/

/*SPECIAL EDITOR*/
CQTs_ClassSpecialEdit::CQTs_ClassSpecialEdit(QWidget *parent)
    : QWidget(parent)
{

}
