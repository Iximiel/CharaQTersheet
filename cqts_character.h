#ifndef CQTS_CHARACTER_H
#define CQTS_CHARACTER_H
#include "cqts_engine.h"
#include <QString>
#include <QMap>
#include <QVector>
#include <QXmlStreamReader>

struct charBio{
    QString Name, Surname;
    QString Race;
    int age;
};

struct level{
    level(){for (int i = 0; i < 6; AbilitiyCNGs[i++]=0);}
    QMap<QString,int> skillRanks;
    int AbilitiyCNGs[6];
    QString thisLVclass;
};

class CQTs_Character{
public:
    CQTs_Character();
    CQTs_Character(CQTs_engine *eng,QString filename);
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
    //bio
    void setName(QString newName);
    void setSurname(QString newSurname);
    void setAge(int newAge);
    void setBio(charBio newBio);
    void Race(QString code);
    QString Race();
    //stats management
    void update();
    void addLevel(QString classCode, QMap<QString,int> ranks, int AbilitiyCNGs[6]);
    void addLevel(QString classCode, QMap<QString,int> ranks);
    //retrocompatibility
    void setLV(int newLV);
    void setHP(int newHP);
    void setBAB(int newBAB);
    //abilities
    int getAbility(CQT_Abilities sel);
    int getAbility(int sel);
    int getAbilityMod(CQT_Abilities sel);
    int getAbilityMod(int sel);
    int* getAbilities();
    void setAbility(CQT_Abilities sel, int newAbility);
    void setAbility(int sel, int newAbility);
    void setAbilities(int newAbilities[6]);
    void setAbilityMod(int lv, CQT_Abilities sel, int newAbilityM);
    void setAbilityMod(int lv, int sel, int newAbilityM);
    void setAbilitiesMod(int lv, int newAbilitiesM[6]);
    //skills
    int getRanks(QString code);
    void setRanks(int lv, QString code, int newRanks);
    void setRanks(int lv, QMap<QString,int> newSkillRanks);
    void setEngine(CQTs_engine* eng);
    //save throws
    int getFortitude();
    int getReflex();
    int getWill();
    int getST(int i);
    void setFortitude(int newSTf);
    void setReflex(int newSTr);
    void setWill(int newSTw);
    void setST(int newSTf,int newSTr,int newSTw);

private:
    CQTs_engine *engine;
    void load003(QXmlStreamReader &xml);//load version 003
    void load005(QXmlStreamReader &xml);//load version 005
    charBio bio;
    QString version;//retrocompatibility
    int LV,HP,BAB,STf,STr,STw;//Armor class will come with inventory
    int Abilities[6];
    QVector<level> levelHistory;

};
#endif // CQTS_CHARACTER_H
