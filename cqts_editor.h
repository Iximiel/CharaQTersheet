#ifndef CQTS_EDITOR_H
#define CQTS_EDITOR_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include "cqts_engine.h"
#include "cqts_character.h"

class cqts_BABeditor : public QWidget
{
    Q_OBJECT
public:
    explicit cqts_BABeditor(int oldBAB,QWidget *parent = 0);
    ~cqts_BABeditor();
signals:
    int newBAB(int bab);
private slots:
    void update();
private:
    QPushButton *saveBTT, *undoBTT;
    QSpinBox *newSpinBaB;
};

class cqts_STeditor : public QWidget
{
    Q_OBJECT
public:
    explicit cqts_STeditor(int oldSTs[3], QWidget *parent = 0);
    ~cqts_STeditor();
signals:
    void newSTs(int* ST);
private slots:
    void update();
private:
    QPushButton *saveBTT, *undoBTT;
    QSpinBox **newSpinST;
};

class cqts_Bioeditor : public QWidget
{
    Q_OBJECT
public:
    explicit cqts_Bioeditor(charBio old, QWidget *parent = 0);
    ~cqts_Bioeditor();
signals:
    void newBio(charBio nbio);
private slots:
    void update();
private:
    QPushButton *saveBTT, *undoBTT;
    QSpinBox *newSpinAge;
    QLineEdit *newSpinName, *newSpinSurname;
};

class cqts_AbilitiesEditor : public QWidget
{
    Q_OBJECT
public:
    explicit cqts_AbilitiesEditor(int oldAbl[6], QWidget *parent = 0);
    ~cqts_AbilitiesEditor();
signals:
    void newAbl(int* Abl);
private slots:
    void update();
private:
    QPushButton *saveBTT, *undoBTT;
    QSpinBox **newSpinAbl;
};

class cqts_SkillsEditor : public QWidget
{
    Q_OBJECT
public:
    explicit cqts_SkillsEditor(CQTs_Character *selected, CQTs_engine *engine, QWidget *parent = 0);
    ~cqts_SkillsEditor();
signals:
    void newSkills(QMap<QString,int> newskills);
private slots:
    void update();
private:
    CQTs_engine *eng;
    QPushButton *saveBTT, *undoBTT;
    QSpinBox **newSpinSkills;
};

#endif // CQTS_EDITOR_H
