//the engine is the "globalresorcepack" of my prog
#ifndef CQTS_ENGINE_H
#define CQTS_ENGINE_H
#include <QString>
#include <QStringList>
#include <QMap>
/*as now this is a placeholder,
 *maybe it will evolve in a sort of global
 *constant that will make communication between segments of the program
 */
class CQTs_skill : public QString//in a qlist this could be find using the code, and next ordered by using myname
{
public:
    CQTs_skill();
    CQTs_skill(QString code, bool train);
    static CQTs_skill finder (QString code);
    void setmyName(QString);
    QString myName();
    bool needsTrain();
    bool operator <(CQTs_skill b);
private:
    QString Name;
//    QStringList synergies;
//    int armor;
    bool trainedOnly;
};

class CQTs_engine//it holds all data related to the game, like skills, max level and conf files
{
public:
    CQTs_engine();
    int skillNum();
    CQTs_skill skillData(int i);
private:
    //QStringList confFiles;// 0 skills 1 skillnames
    void loadSkills();
    void loadSkillNames();
    QList<CQTs_skill> Skills;
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

class CQTs_Character
{
public:
    CQTs_Character(QString filename);
    void saveToFile (QString filename);
    void loadFromFile (QString filename);

    enum CQT_Abilities{STR,DEX,CON,INT,WIS,CHA};
    QString getName();
    QString getSurname();
    int getAge();
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
    int getRanks(QString code);
private:
    charBio bio;
    int LV,HP,BAB,STf,STr,STw;//Armor class will come with inventory
    int Abilities[6];
    QMap<QString,int> skillRanks;
};

#endif //CQTS_CHAR

#ifndef CQTS_CLASS
#define CQTS_CLASS
#include <QString>

class CQTs_Class
{
public:
    CQTs_Class(QString classLink);
    QString className();
    int classBAB();
    bool STFort();
    bool STRef();
    bool STWill();
private:
    QString Name;
    int lmax;//20,10,5,3 so he can understand if is baseclass or not//may be made compatible with d20System in general
    int BAB;//tell me core stats: binary: xxxxx FRWBA FRW 1/0 each (good or bad) BA(b):00 01 10
    bool fort, ref, will;
    //next: adding class skills and privileges
};

#endif //CQTS_CLASS

#ifndef UTILITIES
#define UTILITIES
#include <QStringList>

QStringList extensionFind(QString ext, QString dir);
QStringList extensionFind(QString ext);
#endif //UTILITIES
