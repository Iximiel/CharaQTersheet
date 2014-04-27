#ifndef CQTS_EDITOR_H
#define CQTS_EDITOR_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

class cqts_BABeditor : public QWidget
{
    Q_OBJECT
public:
    explicit cqts_BABeditor(int oldBAB,QWidget *parent = 0);
    ~cqts_BABeditor();
signals:
    int newBAB(int bab);
private slots:
    void update();
private:
    QPushButton *saveBTT, *undoBTT;
    QSpinBox *newSpinBaB;
};

class cqts_STeditor : public QWidget
{
    Q_OBJECT
public:
    explicit cqts_STeditor(int oldSTs[3], QWidget *parent = 0);
    ~cqts_STeditor();
signals:
    void newSTs(int* ST);
private slots:
    void update();
private:
    QPushButton *saveBTT, *undoBTT;
    QSpinBox **newSpinST;
};

#endif // CQTS_EDITOR_H
