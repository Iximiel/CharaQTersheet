#ifndef CQTS_EDITORS_H
#define CQTS_EDITORS_H
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

class BABeditor : public QWidget{
public:
    BABeditor(QWidget *parent = 0);

signals:
    int newBAB(int bab);
private:
    QPushButton *saveBTT, *undoBTT;
    QSpinBox *newSpinBaB;
};

#endif // CQTS_EDITORS_H
