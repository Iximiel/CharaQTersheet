//the engine is the "globalresorcepack" of my prog
#ifndef CQTS_ENGINE_H
#define CQTS_ENGINE_H
#include <QString>
#include <QMap>
/*as now this is a placeholder,
 *maybe it will evolve in a sort of global
 *constant that will make communication between segments of the program
 */
class CQTs_skill
{
public:
    CQTs_skill();
    CQTs_skill(QString name);
    QString myName();
private:
    QString Name;
    //int ranks;
};

class CQTs_engine
{
public:
    CQTs_engine();
private:
    QList<QString> skilladdress;
    QMap<QString,CQTs_skill> Skills;
};

#endif // CQTS_ENGINE_H

#ifndef CQTS_CHAR
#define CQTS_CHAR
#include <QString>

struct charBio{
    QString Name, Surname;
    int age;
};

class CQTs_Character
{
public:
    CQTs_Character(QString filename);
    void saveToFile (QString filename);
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
    int getAbilityMod(int sel);


private:
    charBio bio;
    int LV,HP,BAB,STf,STr,STw;
    int Abilities[6];
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
    int BAB;//tell me core stats: binary: xxxxx FRWAB FRW 1/0 each (good or bad) BAB:00 01 10
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
