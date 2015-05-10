//the engine is the "globalresourcepack" of my prog
#ifndef CQTS_ENGINE_H
#define CQTS_ENGINE_H
#include <QString>
#include <QStringList>
#include <QMap>

//container for everithing that will need a tranlsation
//code is the english name, Name is the translated info
class CQTS_infoHolder : public QString//in a qlist this could be find using the code, and next ordered by using myname
{
public:
    CQTS_infoHolder();
    CQTS_infoHolder(QString code);
    void setmyName(QString);
    QString myName();
protected:
    QString Name;
};

bool operator <(CQTS_infoHolder a ,CQTS_infoHolder b);//needed to order alphabetically things

class CQTs_skill : public CQTS_infoHolder
{
public:
    CQTs_skill();
    CQTs_skill(QString code);//search constructor
    CQTs_skill(QString code, bool train);
    void setAbility(int);
    int myAbility();
    bool needsTrain();
    void add_Synergy(QString code, QString description="");//it undertand if is cyrcumstantial or notby himself
private:
    QStringList* synergies;
    QStringList* descSyn;
    int ability;//armor;
    bool trainedOnly;
};


class CQTs_Class : public CQTS_infoHolder
{
public:
    CQTs_Class();
    CQTs_Class(QString code);//search constructor
    CQTs_Class(QString code, bool data[5], int setDV=0, int setRanks=0, int MaxLV=20);
    void setParam(bool data[5], int setDV=0, int setRanks=0, int MaxLV=20);
    int MaxLv();
    int BAB();
    int AP();
    int HP();
    bool STFort();
    bool STRef();
    bool STWill();
    void setSkills(QStringList newSkills);
    CQTs_Class& operator=(CQTs_Class);
private:
    enum{fort=2,ref=3,will=4};
    int Ranks, DV;
    int lmax;//20,10,5,3 so he can understand if is baseclass or not//may be made compatible with d20System in general
    bool info[5];//01:BAB 2:F 3:R 4:W
    QStringList skillList;
    //BAB: 01 good, 10 medium 00 low
    //next: adding class skills and privileges
};

/*as now this is a placeholder,
 *maybe it will evolve in a sort of global
 *constant that will make communication between segments of the program
 */

class CQTs_engine//it holds all data related to the game, like skills, max level and conf files
{
public:
    CQTs_engine();
    int skillNum();
    CQTs_skill skillData(int i);
    int classNum();
    CQTs_Class classData(int i);
    QStringList classNames();
private:
    //QStringList confFiles;// 0 skills 1 skillnames 2 classes 3 classnames
    void loadSkills(QString filename);//need to power up
    void loadSkillNames(QString filename);
    void loadClasses(QString filename);//need to power up
    void loadClassNames(QString filename);
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
