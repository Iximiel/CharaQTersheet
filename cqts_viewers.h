#ifndef CQTS_CLASSVIEWER_H
#define CQTS_CLASSVIEWER_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include "cqts_engine.h"


class CQTs_ClassViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ClassViewer(QWidget *parent = 0);
    explicit CQTs_ClassViewer(CQTs_Class *selected, QWidget *parent = 0);
private:
    QLabel *LabName,*LabBAB,*LabFort,*LabRef,*LabWill;
    void initialize();
signals:

public slots:
    void setLabs(CQTs_Class *selected);
};

#endif // CQTS_CLASSVIEWER_H
