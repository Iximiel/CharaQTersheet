#ifndef CQTS_CHARACTERCREATOR_H
#define CQTS_CHARACTERCREATOR_H
#include "cqts_engine.h"
#include "cqts_character.h"
#include "cqts_viewers.h"
#include <QWizard>
#include <QWizardPage>
#include <QLabel>

class choseClass : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseClass(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
    QLabel *LabHD, *LabRanks,*LabBAB, *LabFort, *LabRef, *LabWill;
    QLabel **LabSpells;
    CQTs_ClassViewer *viewer;
public slots:
    void selClass(int selected);
};

class CQTs_CharacterCreator : public QWizard
{
    Q_OBJECT
public:
    explicit CQTs_CharacterCreator(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
signals:

public slots:
};

#endif // CQTS_CHARACTERCREATOR_H
