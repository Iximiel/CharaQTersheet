#ifndef CHARAQTERSHEET_H
#define CHARAQTERSHEET_H

#include <QMainWindow>
#include <QMenuBar>
#include <QComboBox>
#include "cqts_viewers.h"
#include "cqts_engine.h"

class CharaQTersheet : public QMainWindow
{
    Q_OBJECT

public:
    CharaQTersheet(QWidget *parent = 0);
    ~CharaQTersheet();
public slots:
    void newCharacter();
    //docks
    void addDockClass();
    void addDockBio();
    void addDockBAB();
    void addDockAbilities();
    void addDockSaves();
    void addDockSkills();
    //character
    void loadChar();
    void saveChar();
    //editor
    void editBAB();
    void editBio();
    void editSkills();
    void editSaves();
    void editAbilities();

    void updateBAB(int newBAB);
    void updateBio(charBio newBio);
    void updateSkills();
    void updateSaves(int* STs);
    void updateAbilities(int abls[6]);
private:
    CQTs_engine *engine;
    CQTs_Character *character;
    QDockWidget *dockSkills, *dockSaves, *dockAbilities, *dockBio, *dockBAB, *dockClass;
    CQTs_ChBioViewer *viewerBio;
    CQTs_ChAbilitiesViewer *viewerAbilities;
    CQTs_ChSTViewer *viewerST;
    CQTs_ChSkillsViewer *viewerSkills;
};

class ClassViewer : public QWidget
{
   Q_OBJECT
public:
    explicit ClassViewer(QWidget *parent = 0);
    ~ClassViewer();
private:
    CQTs_ClassViewer *viewer;
    QComboBox *comboClass;
public slots:
    void selClass(QString selected);
};

#endif // CHARAQTERSHEET_H
