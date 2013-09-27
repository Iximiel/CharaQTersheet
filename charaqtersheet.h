#ifndef CHARAQTERSHEET_H
#define CHARAQTERSHEET_H

#include <QMainWindow>
#include <QMenuBar>
#include <QComboBox>
#include <QDockWidget>
#include "cqts_classviewer.h"

class CharaQTersheet : public QMainWindow
{
    Q_OBJECT

public:
    CharaQTersheet(QWidget *parent = 0);
    ~CharaQTersheet();
//private:
};

class ClassViewer : public QDockWidget
{
   Q_OBJECT
public:
    ClassViewer(QWidget *parent = 0);
    ~ClassViewer();
private:
    CQTs_ClassViewer *viewer;
    QComboBox *comboClass;
public slots:
    void selClass(QString selected);
};

#endif // CHARAQTERSHEET_H
