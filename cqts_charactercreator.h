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

//#define NOFIELDFORSKILL

class choseBio : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseBio(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
    QLineEdit *LineName, *LineSurname;
    QSpinBox *SpinAge;
    QComboBox *comboRace;
};

class choseAbilities : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseAbilities(CQTs_engine* eng, CQTs_Character *character=NULL, QWidget *parent = 0);
    void initializePage();
private:
    CQTs_engine *engine;
    QLabel *LabelPoints;
    QSpinBox **SpinAbilities;
    bool newChar;
    int nudeAbilities[6];
private slots:
    void UpdatePoints();
};

class choseClass : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseClass(CQTs_engine* eng, CQTs_Character *character=NULL, QWidget *parent = 0);
private:
    CQTs_engine *engine;
    QComboBox *comboClass;
    CQTs_ClassViewer *viewer;
    CQTs_Character *changingChar;
public slots:
    void selClass(int selected);
};

class choseSkills : public QWizardPage
{
    Q_OBJECT
public:
    explicit choseSkills(CQTs_engine* eng, CQTs_Character *character=NULL, QWidget *parent = 0);

    void initializePage();
    bool isComplete() const;
private:
    int maxranks;
    CQTs_engine *engine;
    QSpinBox **spinSkills;
    QLabel **labelResult,*labelSpent;
    CQTs_Character *myCharacter;
public slots:
    void calcRanks();
};

class CQTs_CharacterCreator : public QWizard
{
    Q_OBJECT
public:
    explicit CQTs_CharacterCreator(CQTs_engine* eng, QWidget *parent = 0);
    explicit CQTs_CharacterCreator(CQTs_engine* eng, CQTs_Character *character, QWidget *parent = 0);
    void accept();
signals:
    void newCharacter(CQTs_Character *newChar);
    void newLevel();
private:
    CQTs_engine *engine;
    CQTs_Character *mychar;
};

#endif // CQTS_CHARACTERCREATOR_H
