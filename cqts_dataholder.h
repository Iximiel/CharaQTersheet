#ifndef CQTS_DATAHOLDER
#define CQTS_DATAHOLDER
#include <QString>
#include <QStringList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

void xmlHasError(QXmlStreamReader &xml, QString filename);

//code is the english name, Name is the translated info
class CQTS_infoHolder : public QString//in a qlist this could be find using the code, and next ordered by using myname
{
public:
    CQTS_infoHolder();
    CQTS_infoHolder(QString code);
    void setmyName(QString);
    QString myName();
    void setCode(QString);
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
    CQTs_skill(QXmlStreamReader &xml);
    void setAbility(int);
    int myAbility();
    bool needsTrain();
    QStringList* getSynergies();//get a list of the synergies that apply always this list should be deleted after been used
    //QStringList* getSynergies_circumstantial();
    void add_Synergy(QString code, QString description="");//it undertand if is cyrcumstantial or notby himself
private:
    QStringList* synergies;
    QStringList* descSyn;
    int ability;//armor;
    //bool personal;//this indicates that this skill has to be exported with the character
    //for example a knowledge or a perform skill
    bool trainedOnly;
};

class CQTs_Race : public CQTS_infoHolder
{
 public:
    CQTs_Race();
    CQTs_Race(QString code);//search constructor
    CQTs_Race(QXmlStreamReader &xml);
    int SkillPointBonus();
    int abilityMod(int i);
private:
    int SPbonus;//bonuskillpointsper level
    int abilities[6];
};


class CQTs_Class : public CQTS_infoHolder
{
public:
    CQTs_Class();
    CQTs_Class(QString code);//search constructor
    CQTs_Class(QString code, bool data[5], int setDV=0, int setRanks=0, int MaxLV=20);
    CQTs_Class(QXmlStreamReader &xml);
    void setParam(bool data[5], int setDV=0, int setRanks=0, int MaxLV=20);
    int MaxLv();
    int BAB();
    int AP();
    int HP();
    //saves
    bool STFort();
    bool STRef();
    bool STWill();
    //skills
    void setSkills(QStringList newSkills);
    QStringList getSkills();
    bool isClassSkill(QString code);
    //spells
    void setSpellPerDay(QStringList newSpells);
    QString SpellPerDay(int lv);
    bool isSpellcaster();
    //data
    void writeData(QString filename);
    void writeDatatoXml(QXmlStreamWriter &xml);
    CQTs_Class& operator=(CQTs_Class);
private:
    enum{fort=2,ref=3,will=4};
    int Ranks, DV;
    int lmax;//20,10,5,3 so he can understand if is baseclass or not//may be made compatible with d20System in general
    bool info[5];//01:BAB 2:F 3:R 4:W
    bool spellcaster;
    QStringList skillList;
    QStringList spellNumberList;//spell per level: 0123456789 (baseclasses have max 6 spell on a sigle level!)
    //BAB: 01 good, 10 medium 00 low
    //next: adding class skills and privileges
};


#endif // CQTS_DATAHOLDER

