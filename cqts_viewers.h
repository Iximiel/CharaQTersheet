#ifndef CQTS_VIEWERS_H
#define CQTS_VIEWERS_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QString>
#include <QVector>
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

class CQTs_ChBioViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ChBioViewer(QWidget *parent = 0);
    explicit CQTs_ChBioViewer(CQTs_Character *selected, QWidget *parent = 0);
private:
    QLabel *LabName,*LabSurname,*LabAge;
    void initialize();
signals:

public slots:
   void setLabs(CQTs_Character *selected);
};

class CQTs_ChAbilitiesViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ChAbilitiesViewer(QWidget *parent = 0);
    explicit CQTs_ChAbilitiesViewer(CQTs_Character *selected, QWidget *parent = 0);
private:
    QLabel **LabName, **LabValue, **LabMod;
    void initialize();
signals:

public slots:
   void setLabs(CQTs_Character *selected);
   void setLab(int sel, int val, bool temporary = false);
};

class CQTs_ChSkillsViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ChSkillsViewer(QWidget *parent = 0);
    //explicit CQTs_ChSkillsViewer(CQTs_Character *selected, QWidget *parent = 0);
private:
    QVector<QLabel*> LabName;//, LabValue, LabMod;
    void initialize();
signals:

public slots:
   //void setLabs(CQTs_Character *selected);
   //void setLab(int sel, int val, bool temporary = false);
};



class CQTs_ChSTViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ChSTViewer(QWidget *parent = 0);
    //explicit CQTs_ChSTViewer(CQTs_Character *selected, QWidget *parent = 0);
private:
    QLabel** LabName, **LabValue, **LabMod;
    void initialize();
signals:

public slots:
   //void setLabs(CQTs_Character *selected);
   //void setLab(int sel, int val, bool temporary = false);
};

#endif // CQTS_VIEWERS_H
