#ifndef CHARAQTERSHEET_H
#define CHARAQTERSHEET_H

#include <QMainWindow>
#include <QMenuBar>
#include <QComboBox>
#include "cqts_viewers.h"
#include "cqts_classcreator.h"
#include "cqts_engine.h"

class CharaQTersheet : public QMainWindow
{
    Q_OBJECT

public:
    CharaQTersheet(QWidget *parent = 0);
    ~CharaQTersheet();
public slots:
    void newCharacter();
    void newLevel();
    void getnewCharacter(CQTs_Character* newchar);
    //docks
    void addDockClass();
    void addDockBio();
    void addDockBAB();
    void addDockAbilities();
    void addDockSaves();
    void addDockSkills();
    void updateLabs();
    void DM_Mode();
    //character
    void loadChar();
    void saveChar();
    //editor
    void editBio();
    /*void editBAB();
    void editSkills();
    void editSaves();
    void editAbilities();*/

    void updateBio(charBio newBio);
    /*void updateBAB(int newBAB);
    void updateSkills();
    void updateSaves(int* STs);
    void updateAbilities(int *abls);*/
    //various exports:
    void exportClasses();
    void launchClassCreator();
private:
    CQTs_engine *engine;
    CQTs_Character *character;
    QDockWidget *dockSkills, *dockSaves, *dockAbilities, *dockBio, *dockBAB, *dockClass;
    CQTs_ChBioViewer *viewerBio;
    CQTs_ChAbilitiesViewer *viewerAbilities;
    CQTs_ChSTViewer *viewerST;
    CQTs_ChSkillsViewer *viewerSkills;
    CQTs_ChBABViever *viewerBAB;
};

class ClassViewer : public QWidget
{
   Q_OBJECT
public:
    explicit ClassViewer(CQTs_engine *engine, QWidget *parent = 0);
    ~ClassViewer();
private:
    CQTs_engine *engine;
    CQTs_ClassViewer *viewer;
    QComboBox *comboClass;
public slots:
    void selClass(int selected);
};

#endif // CHARAQTERSHEET_H
