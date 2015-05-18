#ifndef CQTS_CHARACTER_H
#define CQTS_CHARACTER_H
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
    QStringList classLevels;//history of classes

};
#endif // CQTS_CHARACTER_H
