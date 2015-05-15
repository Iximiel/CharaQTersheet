//the engine is the "globalresourcepack" of my prog
#ifndef CQTS_ENGINE_H
#define CQTS_ENGINE_H
#include "cqts_dataholder.h"
#include <QMap>

//container for everithing that will need a tranlsation

class CQTs_engine//it holds all data related to the game, like skills, max level and conf files
{
public:
    CQTs_engine();
    //skills manipulation
    int skillNum();
    int getSkillNum(QString code);
    CQTs_skill skillData(int i);
    //classes manipulation
    int classNum();
    CQTs_Class classData(int i);
    QStringList classNames();
    void appendClass(CQTs_Class newclass);
private:
    //QStringList confFiles;// 0 skills 1 skillnames 2 classes 3 classnames
    void loadFiles(QString filename);
    void loadFromFile(QString filename);
    void loadSkills(QString filename);
    void loadSkillNames(QString filename);
    void loadClasses(QString filename);
    void loadClassNames(QString filename);
    QStringList files;
    QList<CQTs_skill> Skills;
    QList<CQTs_Class> Classes;
};

#endif // CQTS_ENGINE_H

#ifndef CQTS_CHAR
#define CQTS_CHAR
#include <QString>
#include <QMap>

struct charBio{
    QString Name, Surname;
    int age;
};

class CQTs_Character{
public:
    CQTs_Character();
    CQTs_Character(QString filename);
    void saveToFile (QString filename);
    void loadFromFile (QString filename);

    enum CQT_Abilities{STR,DEX,CON,INT,WIS,CHA};
    QString getName();
    QString getSurname();
    int getAge();
    charBio getBio();
    int getLV();
    int getHP();
    int getBAB();
    int getFortitude();
    int getReflex();
    int getWill();
    int getST(int i);
    int getAbility(CQT_Abilities sel);
    int getAbility(int sel);
    int getAbilityMod(CQT_Abilities sel);
    int getAbilityMod(int sel);
    int* getAbilities();
    int getRanks(QString code);

    void setName(QString newName);
    void setSurname(QString newSurname);
    void setAge(int newAge);
    void setBio(charBio newBio);
    void setLV(int newLV);
    void setHP(int newHP);
    void setBAB(int newBAB);
    void setFortitude(int newSTf);
    void setReflex(int newSTr);
    void setWill(int newSTw);
    void setST(int newSTf,int newSTr,int newSTw);
    void setAbility(CQT_Abilities sel, int newAbility);
    void setAbility(int sel, int newAbility);
    void setAbilities(int newAbilities[6]);
    void setRanks(QString code, int newRanks);
    void setRanks(QMap<QString,int> newSkillRanks);

private:
    charBio bio;
    int LV,HP,BAB,STf,STr,STw;//Armor class will come with inventory
    int Abilities[6];
    QMap<QString,int> skillRanks;

};

#endif //CQTS_CHAR

#ifndef UTILITIES
#define UTILITIES
#include <QStringList>

QStringList extensionFind(QString ext, QString dir);
QStringList extensionFind(QString ext);
#endif //UTILITIES
