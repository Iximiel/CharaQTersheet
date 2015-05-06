#include "classcreator.h"
#include <QLabel>
//#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>

/*CLASSCREATOR*/
CQTs_ClassEditor::CQTs_ClassEditor(QWidget *parent)
    : QWidget(parent)
{
    QLabel *tLabel = new QLabel(tr("Name (in english):"));
    QFormLayout *grid = new QFormLayout();
    QLineEdit *Line_Name = new  QLineEdit();
    grid->addRow(tLabel,Line_Name);
    tLabel = new QLabel(tr("Hit Die:"));
    QComboBox *Combo_HD = new QComboBox();
    QStringList List;
    List <<"d4"<<"d6"<<"d8"<<"d10"<<"d12";
    Combo_HD->addItems(List);
    grid->addRow(tLabel,Combo_HD);
    tLabel = new QLabel(tr("Skill Points at Each Level:"));
    List.clear();
    List << "2" << "4" << "6" << "8";
    QComboBox *Combo_Ranks = new QComboBox();
    Combo_Ranks->addItems(List);
    grid->addRow(tLabel,Combo_Ranks);
    setLayout(grid);
}

/*SPECIAL EDITOR*/
CQTs_ClassSpecialEdit::CQTs_ClassSpecialEdit(QWidget *parent)
    : QWidget(parent)
{

}
