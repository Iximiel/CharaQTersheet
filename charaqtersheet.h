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
    void addDockClass(Qt::DockWidgetArea area);
    void addDockBio(Qt::DockWidgetArea area);
    void addDockAbilities(Qt::DockWidgetArea area);
    void addDockSaves(Qt::DockWidgetArea area);
    void addDockSkills(Qt::DockWidgetArea area);
//private:
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
