#ifndef CQTS_CHARACTERCREATOR_H
#define CQTS_CHARACTERCREATOR_H
#include "cqts_engine.h"
#include "cqts_character.h"
#include "cqts_viewers.h"
#include <QWizard>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

class choseBio : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseBio(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
    QLineEdit *LineName, *LineSurname;
    QSpinBox *SpinAge;
};

class choseAbilities : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseAbilities(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
    QLabel *LabelPoints;
    QSpinBox **SpinAbilities;
private slots:
    void UpdatePoints();
};

class choseClass : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseClass(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
    QComboBox *comboClass;
    CQTs_ClassViewer *viewer;
public slots:
    void selClass(int selected);
signals:
    void getClass(QString selected);
};

class choseSkills : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseSkills(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
    QSpinBox **spinSkills;
    QLabel **labelResult;
    QString myclass;
public slots:
    void selClass(QString selected);
    void calcRanks();
};

class CQTs_CharacterCreator : public QWizard
{
    Q_OBJECT
public:
    explicit CQTs_CharacterCreator(CQTs_engine* eng, QWidget *parent = 0);
    void accept();
private:
    CQTs_engine *engine;
};

#endif // CQTS_CHARACTERCREATOR_H
