#include "cqts_classviewer.h"
#include <QLabel>
#include <QComboBox>

CQTs_ClassViewer::CQTs_ClassViewer(QWidget *parent) :
    QGroupBox(tr("Class Viewer"),parent)
{
    QLabel Sel(tr("Class:"));
    QComboBox ComboSel();

}
