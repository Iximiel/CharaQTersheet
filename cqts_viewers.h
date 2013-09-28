#ifndef CQTS_VIEWERS_H
#define CQTS_VIEWERS_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QString>
#include "cqts_engine.h"

class CQTs_Viewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_Viewer(QString title="", QWidget *parent = 0);
private:
    virtual void initialize();
};

class CQTs_ClassViewer : public CQTs_Viewer
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

class CQTs_ChBioViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ChBioViewer(QWidget *parent = 0);
    explicit CQTs_ChBioViewer(CQTs_Class *selected, QWidget *parent = 0);
private:
    QLabel *LabName,*LabSurname,*LabAge;
    void initialize();
signals:

public slots:
   // void setLabs(CQTs_Class *selected);
};

#endif // CQTS_VIEWERS_H
