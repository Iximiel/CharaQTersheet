#ifndef CQTS_VIEWERS_H
#define CQTS_VIEWERS_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QSpinBox>
#include <QPushButton>
#include "cqts_engine.h"

class CQTs_ClassViewer : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ClassViewer(QWidget *parent = 0);
    explicit CQTs_ClassViewer(CQTs_Class *selected, QWidget *parent = 0);
private:
    QLabel /**LabName,*/*LabHD,*LabRanks,**LabLev,**LabBAB,**LabFort,**LabRef,**LabWill, **LabSpells;
    void initialize();
    int LMax;
signals:

public slots:
    void setLabs(CQTs_Class *selected);
};

class CQTs_ChBioViewer : public QWidget
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

class CQTs_ChAbilitiesViewer : public QWidget
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

class CQTs_ChSkillsViewer : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ChSkillsViewer(CQTs_engine *engine, QWidget *parent = 0);
    //explicit CQTs_ChSkillsViewer(CQTs_Character *selected, QWidget *parent = 0);
private:
    CQTs_engine *eng;//pointer to the engine
    QVector<QLabel*> Labels;//[i*8+j]i is row, j = 0 name, 1, value, 3 abl mod, 5 ranks, 7 mods;
    QPushButton *train;
    void initialize();
signals:

public slots:
    void setLabs(CQTs_Character *selected);
   //void setLab(int sel, int val, bool temporary = false);
    void showOnlyTrained();
};



class CQTs_ChSTViewer : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ChSTViewer(QWidget *parent = 0);
    //explicit CQTs_ChSTViewer(CQTs_Character *selected, QWidget *parent = 0);
private:
    QLabel** LabName, **LabValue,  **LabAb,**LabMod;
    QSpinBox **SpinVarious;
    void initialize();
signals:

public slots:
   void setLabs(CQTs_Character *selected);
   //void setLab(int sel, int val, bool temporary = false);
};

class CQTs_ChBABViever :public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_ChBABViever (QWidget *parent = 0);
    //explicit CQTs_ChBABViever(CQTs_Character *selected, QWidget *parent = 0);
private:
    QLabel** LabName, **LabValue,  **LabAb,**LabMod;
    QSpinBox **SpinVarious;
    void initialize();
signals:

public slots:
   void setLabs(CQTs_Character *selected);
   //void setLab(int sel, int val, bool temporary = false);
};

#endif // CQTS_VIEWERS_H
