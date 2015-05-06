#include "classcreator.h"
#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>

/*CLASSCREATOR*/
CQTs_ClassCreator::CQTs_ClassCreator(QWidget *parent)
    : QWidget(parent)
{
    QLabel *tLabel = new QLabel(tr("Name (in english):"));
    QGridLayout *grid = new QGridLayout();
    int r =0;
    QLineEdit *Line_Name = new  QLineEdit();
    grid->addWidget(Line_Name,r,1);
    grid->addWidget(tLabel,r++,0);
    tLabel = new QLabel(tr("Hit Die:"));
    QComboBox *Combo_HD = new QComboBox();
    QStringList List;
    List <<"d4"<<"d6"<<"d8"<<"d10"<<"d12";
    Combo_HD->addItems(List);
    grid->addWidget(Combo_HD,r,1);
    grid->addWidget(tLabel,r++,0);
    tLabel = new QLabel(tr("Skill Points at Each Level:"));
    List.clear();
    List << "2" << "4" << "6" << "8";
    QComboBox *Combo_Ranks = new QComboBox();
    Combo_Ranks->addItems(List);
    grid->addWidget(Combo_Ranks,r,1);
    grid->addWidget(tLabel,r++,0);
    setLayout(grid);
}

/*SPECIAL EDITOR*/
CQTs_ClassSpecialEdit::CQTs_ClassSpecialEdit(QWidget *parent)
    : QWidget(parent)
{

}
