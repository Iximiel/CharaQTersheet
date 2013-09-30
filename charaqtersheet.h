#ifndef CHARAQTERSHEET_H
#define CHARAQTERSHEET_H

#include <QMainWindow>
#include <QMenuBar>
#include <QComboBox>
#include "cqts_viewers.h"

class CharaQTersheet : public QMainWindow
{
    Q_OBJECT

public:
    CharaQTersheet(QWidget *parent = 0);
    ~CharaQTersheet();
public slots:
    void addDockClass();
    void addDockBio();
    void addDockAbilities();
    void addDockSaves();
    void addDockSkills();
    void loadChar();
    void saveChar();
private:
    CQTs_Character *character;
    QDockWidget *dockSkills, *dockSaves, *dockAbilities, *dockBio, *dockClass;
    CQTs_ChBioViewer *viewerBio;
    CQTs_ChAbilitiesViewer *viewerAbilities;
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
