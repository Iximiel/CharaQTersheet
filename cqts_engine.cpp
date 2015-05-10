#include "cqts_engine.h"
#include <QFile>
#include <QDir>

#include <QMessageBox>
#include <QStringList>
#include <algorithm>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>
#include <QDebug>

//infoholder
CQTS_infoHolder::CQTS_infoHolder():
    QString()
{
    Name  = QString();
}

CQTS_infoHolder::CQTS_infoHolder(QString code):
    QString(code)
{
    Name  = QString();
}

QString CQTS_infoHolder::myName(){
    return Name;
}

void CQTS_infoHolder::setmyName(QString name){
    Name  = name;
}

bool operator <(CQTS_infoHolder a , CQTS_infoHolder b){return a.myName()<b.myName();}

//Skillhandler
CQTs_skill::CQTs_skill():CQTS_infoHolder(){
    trainedOnly = false;
    synergies=NULL;
    descSyn=NULL;
}

CQTs_skill::CQTs_skill(QString code):
    CQTS_infoHolder(code)
{
    trainedOnly = false;
    synergies=NULL;
    descSyn=NULL;
}

CQTs_skill::CQTs_skill(QString code, bool train):
    CQTS_infoHolder(code)
{
    trainedOnly = train;
    synergies=NULL;
    descSyn=NULL;
}

void CQTs_skill::setAbility(int abl){
    ability = abl;
}
bool CQTs_skill::needsTrain()
{ return trainedOnly;}

int CQTs_skill::myAbility()
{return ability;}

void CQTs_skill::add_Synergy(QString code, QString description){
    if(synergies==NULL)
        synergies = new QStringList();
    if(descSyn==NULL)
        descSyn = new QStringList();
    synergies->push_back(code);
    descSyn->push_back(description);
}

/*****class handler*****/
CQTs_Class::CQTs_Class():
    CQTS_infoHolder(){
    for (int i = 0; i < 5; ++i) {
        info[i] = false;
    }
    lmax = 0;
}

CQTs_Class::CQTs_Class(QString code):
    CQTS_infoHolder(code)
{
    for (int i = 0; i < 5; ++i) {
        info[i] = false;
    }
    lmax = 0;
}

CQTs_Class::CQTs_Class(QString code, bool data[5], int setDV, int setRanks, int MaxLV):
    CQTS_infoHolder(code)
{
    setParam(data, setDV, setRanks, MaxLV);
}

void CQTs_Class::setParam(bool data[5], int setDV, int setRanks, int MaxLV){
    Ranks =setRanks;
    DV = setDV;
    std::copy(data,data+5,info);
    lmax = MaxLV;
}

void CQTs_Class::writeData(){
    QFile file("filename.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to save your class")), QMessageBox::Ok);
    }else{
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("class");
        QString dummy = "";
        xml.writeAttribute("code",dummy);
        int bab = info[0]*2+info[1];
        dummy.setNum(bab);
        xml.writeAttribute("bab",dummy);
        dummy.setNum(info[fort]);
        xml.writeAttribute("fort",dummy);
        dummy.setNum(info[ref]);
        xml.writeAttribute("ref",dummy);
        dummy.setNum(info[will]);
        xml.writeAttribute("will",dummy);
        dummy.setNum(lmax);
        xml.writeAttribute("lmax",dummy);
        if(skillList.size()>0){
            xml.writeStartElement("classskills");
            for (int i = 0; i < skillList.size(); ++i) {
                xml.writeStartElement("skill");
                xml.writeAttribute("code",skillList[i]);
                xml.writeEndElement();//skill
            }
            xml.writeEndElement();//classskills
        }
        xml.writeStartElement("progression");
        dummy.setNum(Ranks);
        xml.writeAttribute("skillpoints",dummy);
        dummy.setNum(DV);
        xml.writeAttribute("dv",dummy);
        /*levelprogression here*/
        xml.writeEndElement();//progression
        xml.writeEndElement();//class
        xml.writeEndDocument();
    }
}

void CQTs_Class::setSkills(QStringList newSkills){
    skillList.clear();
    skillList.append(newSkills);
}

CQTs_Class& CQTs_Class::operator=(CQTs_Class x){
    clear();
    append(x);
    Name = x.Name;
    Ranks = x.Ranks;
    DV = x.DV;
    lmax = x.lmax;
    std::copy(x.info,x.info+5,info);
    return *this;
}

int CQTs_Class::BAB()
{return info[1]*2+info[0];}

int CQTs_Class::AP(){
    return Ranks;
}

int CQTs_Class::HP(){
    return DV;
}

int CQTs_Class::MaxLv()
{return lmax;}

bool CQTs_Class::STFort()
{return info[fort];}

bool CQTs_Class::STRef()
{return info[ref];}

bool CQTs_Class::STWill()
{return info[will];}

/*****engine******/

CQTs_engine::CQTs_engine(){
    loadSkills("Skills_data.xml");//I'm using english names as codes for the skills
    loadClasses("BaseClasses.xml");//I'm using english names as codes for the skills
    //loadSkillNames("Skills_Ita.xml");//I will add a menu!
    std::sort(Skills.begin(),Skills.end());
    std::sort(Classes.begin(),Classes.end());
}

void CQTs_engine::loadSkills(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to load skills data")), QMessageBox::Ok);
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){

            if(xml.name()=="skill"&&xml.isStartElement())
            {
                QString code;
                int abl;//, arm;
                bool train;

                code = xml.attributes().value("code").toString();
                abl = xml.attributes().value("ability").toInt();
                //arm = xml.attributes().value("armor").toInt();
                train = xml.attributes().value("onlytrained").toInt();
                CQTs_skill tSkill(code,train);
                tSkill.setAbility(abl);
                tSkill.setmyName(code);//in case skillnames are not loaded

                while(!(xml.name()=="skill"&&xml.isEndElement())){
                    xml.readNext();
                    if(xml.name()=="synergy"&&xml.isStartElement()){//get synergies
                        QString SynCode = xml.attributes().value("syncode").toString();
                        QString desc = xml.attributes().value("circumstantial").toString();
                        tSkill.add_Synergy(SynCode,desc);
                    }
                }
                Skills.append(tSkill);
            }
            if (xml.hasError()) {
                QString ERROR=QObject::tr("Error in file:%4\n%1\nLine %2, column %3")
                        .arg(xml.errorString())
                        .arg(xml.lineNumber())
                        .arg(xml.columnNumber())
                        .arg(filename);
                QMessageBox::information(0, QString(QObject::tr("Error")), ERROR, QMessageBox::Ok);
                break;
            }
            xml.readNext();
        }
    }
    file.close();
}

void CQTs_engine::loadSkillNames(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to load skill names")), QMessageBox::Ok);
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){
            if(xml.name()=="skill"&&xml.isStartElement())
            {
                QString code,name;
                code = xml.attributes().value("code").toString();
                name = xml.attributes().value("translation").toString();
                int id = Skills.indexOf(CQTs_skill(code));//(CQTs_skill::finder(code)));
                if(id!=-1)
                {
                    Skills[id] .setmyName(name);
                }
            }
            if (xml.hasError()) {
                QString ERROR=QObject::tr("Error in file: %4\n%1\nLine %2, column %3")
                        .arg(xml.errorString())
                        .arg(xml.lineNumber())
                        .arg(xml.columnNumber())
                        .arg(filename);
                QMessageBox::information(0, QString(QObject::tr("Error")), ERROR, QMessageBox::Ok);
                break;
            }
            xml.readNext();
        }
        file.close();
    }
}

int CQTs_engine::skillNum(){return Skills.size();}
CQTs_skill CQTs_engine::skillData(int i){return Skills[i];}

int CQTs_engine::classNum(){return Classes.size();}
CQTs_Class CQTs_engine::classData(int i){return Classes[i];}

void CQTs_engine::loadClasses(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to load classes data")), QMessageBox::Ok);
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){

            if(xml.name()=="class"&&xml.isStartElement())
            {
                QString code;
                int bab, lmax;
                bool bab1=false,bab2=false,f,r,w;

                code = xml.attributes().value("code").toString();
                bab = xml.attributes().value("bab").toInt();
                if(bab==1)
                    bab1=true;
                else if(bab==2)
                    bab2=true;

                f = xml.attributes().value("fort").toInt();
                r = xml.attributes().value("ref").toInt();
                w = xml.attributes().value("will").toInt();
                lmax = xml.attributes().value("lmax").toInt();
                bool data[5] = {bab1,bab2,f,r,w};
                int dv = 0, ranks = 0;
                QStringList skillList;
                if(!xml.isEndElement()){
                    do{
                        xml.readNext();
                        if(xml.name()=="classskills"&&xml.isStartElement()){
                            do{
                                xml.readNext();
                                if(xml.name()=="skill"&&xml.isStartElement()){
                                    QString skillcode = xml.attributes().value("code").toString();
                                    skillList.push_back(skillcode);
                                }
                            }while(!(xml.name()=="classskills"&&xml.isEndElement()));
                        }
                        if(xml.name()=="progression"&&xml.isStartElement()){//load progression
                            dv = xml.attributes().value("dv").toInt();
                            ranks = xml.attributes().value("skillpoints").toInt();
                            do{
                                xml.readNext();
                                if(xml.name()=="level"&&xml.isStartElement()){
                                    //level progression
                                }
                            }while(!(xml.name()=="progression"&&xml.isEndElement()));
                        }
                    }while(!(xml.isEndElement()&&xml.name()=="class"));
                }
                CQTs_Class tClass(code,data,dv,ranks,lmax);
                tClass.setmyName(code);//in case classnames are not loaded
                tClass.setSkills(skillList);
                //protection from copies:
                while(Classes.contains(tClass)){
                    tClass.append("*");
                }
                Classes.append(tClass);
            }
            if (xml.hasError()) {
                QString ERROR=QObject::tr("Error in file:%4\n%1\nLine %2, column %3")
                        .arg(xml.errorString())
                        .arg(xml.lineNumber())
                        .arg(xml.columnNumber())
                        .arg(filename);
                QMessageBox::information(0, QString(QObject::tr("Error")), ERROR, QMessageBox::Ok);
                break;
            }
            xml.readNext();
        }
    }
    file.close();
}

QStringList CQTs_engine::classNames(){
    QStringList toreturn;
    int nclasses=Classes.size();
    for (int i = 0; i < nclasses; ++i) {
        toreturn.push_back(Classes[i].myName());
    }return toreturn;
}

void CQTs_engine::loadClassNames(QString filename){}


/*****character handler*****/
/*CharacterFile structure:
 *Name
 *Surname
 *age
 *lv
 *str \t dex \t con \t int \t wis \t cha
 *hp
 *bab
 *fort \t ref \t will
 *endoffile
 */

CQTs_Character::CQTs_Character()
{
    bio.age=LV=HP=BAB=STf=STr=STw=0;
    for (int i = 0; i < 6;Abilities[i++]=10 );
    bio.Surname=bio.Name="";
}

CQTs_Character::CQTs_Character(QString filename)
{
    bio.age=LV=HP=BAB=STf=STr=STw=0;
    for (int i = 0; i < 6;Abilities[i++]=10 );
    bio.Surname=bio.Name="";
    loadFromFile(filename);
}

void CQTs_Character::loadFromFile(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        bio.Name=bio.Surname="error";

        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to load character information")), QMessageBox::Ok);
    }else{
        QXmlStreamReader xml(&file);
        while(!(xml.name()=="character"&&xml.isStartElement())){
            xml.readNext();
        }

        while(!(xml.name()=="character"&&xml.isEndElement())){//i want this to work like a paper sheet, i will adda chronology after that
            if(xml.name()=="bio"&&xml.isStartElement()){
                while(!(xml.name()=="bio"&&xml.isEndElement())){//get the bio info
                    xml.readNext();
                    if(xml.name()=="name"&&xml.isStartElement()){//get the name
                        while(!xml.readNext()==6);
                        bio.Name = (xml.text().toString());
                    }
                    if(xml.name()=="surname"&&xml.isStartElement()){//get the surname
                        while(!xml.readNext()==6);
                        bio.Surname = (xml.text().toString());
                    }
                    if(xml.name()=="age"&&xml.isStartElement()){//get the age
                        while(!xml.readNext()==6);
                        bio.age = (xml.text().toInt());
                    }
                }
            }
            if(xml.name()=="data"&&xml.isStartElement()){//get varios data, like pnp for now
                while(!(xml.name()=="data"&&xml.isEndElement())){
                    xml.readNext();
                    if(xml.name()=="hp"&&xml.isStartElement()){
                        while(!xml.readNext()==6);
                        HP= (xml.text().toInt());
                    }
                    if(xml.name()=="bab"&&xml.isStartElement()){
                        while(!xml.readNext()==6);
                        BAB= (xml.text().toInt());
                    }
                    if(xml.name()=="fort"&&xml.isStartElement()){
                        while(!xml.readNext()==6);
                        STf= (xml.text().toInt());
                    }
                    if(xml.name()=="ref"&&xml.isStartElement()){
                        while(!xml.readNext()==6);
                        STr = (xml.text().toInt());
                    }
                    if(xml.name()=="will"&&xml.isStartElement()){
                        while(!xml.readNext()==6);
                        STw= (xml.text().toInt());
                    }
                    if(xml.name()=="abilities"&&xml.isStartElement()){
                        while(!(xml.name()=="abilities"&&xml.isEndElement())){
                            if(xml.name()=="ability"&&xml.isStartElement()){
                                QString code = xml.attributes().value("which").toString();
                                while(!xml.readNext()==6);
                                //qDebug() << code;
                                if(code == "strength"){
                                    Abilities[STR]= (xml.text().toInt());
                                }else if(code == "dexterity"){
                                    Abilities[DEX]= (xml.text().toInt());
                                }else if(code == "constitution"){
                                    Abilities[CON]= (xml.text().toInt());
                                }else if(code == "intelligence"){
                                    Abilities[INT]= (xml.text().toInt());
                                }else if(code == "wisdom"){
                                    Abilities[WIS]= (xml.text().toInt());
                                }else if(code == "charisma"){
                                    Abilities[CHA]= (xml.text().toInt());
                                }
                            }
                            xml.readNext();
                        }
                    }
                }
            }
            if(xml.name()=="skills"&&xml.isStartElement()){//get the ranks in skills
                while(!(xml.name()=="skills"&&xml.isEndElement())){//get the bio info
                    if(xml.name()=="skill"&&xml.isStartElement()){//get the name
                        QString code = xml.attributes().value("code").toString();
                        while(!xml.readNext()==6);
                        //qDebug() << ;
                        int ranks = (xml.text().toInt());
                        skillRanks.insert(code,ranks);
                    }
                    xml.readNext();
                }
            }
            //if(xml.name()=="feats"&&xml.isStartElement()){}
            if (xml.hasError()) {
                // do error handling
            }
            xml.readNext();
        }
        file.close();
    }
}

void CQTs_Character::saveToFile(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to save your character")), QMessageBox::Ok);
    }else{
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.setAutoFormattingIndent(2);
        xml.writeStartDocument();
        xml.writeStartElement("character");
        xml.writeAttribute("version","0.03");
        xml.writeStartElement("bio");
        xml.writeTextElement("name",bio.Name);
        xml.writeTextElement("surname",bio.Surname);
        xml.writeTextElement("age",QString::number(bio.age));
        xml.writeEndElement();//bio
        xml.writeStartElement("data");
        xml.writeTextElement("hp",QString::number(HP));
        xml.writeTextElement("bab",QString::number(BAB));
        xml.writeStartElement("saves");
        xml.writeTextElement("fort",QString::number(STf));
        xml.writeTextElement("ref",QString::number(STr));
        xml.writeTextElement("will",QString::number(STw));
        xml.writeEndElement();//saves
        xml.writeStartElement("abilities");
        QString names[6]={"strength","dexterity","constitution","intelligence","wisdom","charisma"};
        for (int i = 0; i < 6; ++i) {
            xml.writeStartElement("ability");
            xml.writeAttribute("which",names[i]);
            xml.writeCharacters(QString::number(Abilities[i]));
            xml.writeEndElement();//ability
        }
        xml.writeEndElement();//abilities
        if(!skillRanks.empty()){
            xml.writeStartElement("skills");
            for (int i = 0; i < skillRanks.size(); ++i) {
                xml.writeStartElement("skill");
                QString code = skillRanks.keys().at(i);
                xml.writeAttribute("code",code);
                xml.writeCharacters(QString::number(skillRanks[code]));
                xml.writeEndElement();//skill
            }
            xml.writeEndElement();//skills
        }
        xml.writeEndElement();//data
        xml.writeEndElement();//character
        xml.writeEndDocument();
    }
}

QString CQTs_Character::getName(){return bio.Name;}
QString CQTs_Character::getSurname(){return bio.Surname;}
int CQTs_Character::getAge(){return bio.age;}
charBio CQTs_Character::getBio(){return bio;}
int CQTs_Character::getLV(){return LV;}
int CQTs_Character::getHP(){return HP;}
int CQTs_Character::getBAB(){return BAB;}
int CQTs_Character::getFortitude(){return STf;}
int CQTs_Character::getReflex(){return STr;}
int CQTs_Character::getWill(){return STw;}
int CQTs_Character::getST(int i){
    switch (i) {
    case 0:
        return STf;
        break;
    case 1:
        return STr;
        break;
    case 2:
        return STw;
        break;
    default:
        return 0;
        break;
    }
}

int CQTs_Character::getAbility(CQT_Abilities sel){return Abilities[sel];}
int CQTs_Character::getAbility(int sel){return Abilities[sel];}
int CQTs_Character::getAbilityMod(CQT_Abilities sel){return (Abilities[sel]-10)/2.;}
int CQTs_Character::getAbilityMod(int sel){return (Abilities[sel]-10)/2.;}
int* CQTs_Character::getAbilities(){return Abilities;}
int CQTs_Character::getRanks(QString code){
    if(skillRanks.contains(code)){
        return skillRanks[code];
    }else return 0;
}

void CQTs_Character::setName(QString newName){bio.Name = newName;}
void CQTs_Character::setSurname(QString newSurname){bio.Name = newSurname;}
void CQTs_Character::setAge(int newAge){bio.Name = newAge;}
void CQTs_Character::setBio(charBio newBio){bio =newBio;}
void CQTs_Character::setLV(int newLV){LV = newLV;}
void CQTs_Character::setHP(int newHP){HP = newHP;}
void CQTs_Character::setBAB(int newBAB){BAB = newBAB;}
void CQTs_Character::setFortitude(int newSTf){STf = newSTf;}
void CQTs_Character::setReflex(int newSTr){STr = newSTr;}
void CQTs_Character::setWill(int newSTw){STw = newSTw;}
void CQTs_Character::setST(int newSTf,int newSTr,int newSTw){
    STf = newSTf;
    STr = newSTr;
    STw = newSTw;
}
void CQTs_Character::setAbility(CQT_Abilities sel, int newAbility){Abilities[sel] = newAbility;}
void CQTs_Character::setAbility(int sel, int newAbility){Abilities[sel] = newAbility;}
void CQTs_Character::setAbilities(int newAbilities[6]){
    for (int i = 0; i < 6;i++)
        Abilities[i] = newAbilities[i];
}
void CQTs_Character::setRanks(QString code, int newRanks){skillRanks[code] = newRanks;}
void CQTs_Character::setRanks(QMap<QString,int> newSkillRanks){
    skillRanks.clear();
    skillRanks = newSkillRanks;
}

/*****utilities*****/

QStringList extensionFind(QString ext,QString dir){
    QDir workDir(dir);

    QStringList filelist;
    filelist = workDir.entryList(QStringList(ext),QDir::Files | QDir::NoSymLinks);
    return filelist;
}

QStringList extensionFind(QString ext){
    return extensionFind(ext,"./");
}
