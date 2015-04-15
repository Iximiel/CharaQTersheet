#include "cqts_engine.h"
#include <QFile>
#include <QDir>

#include <QMessageBox>
#include <QStringList>
#include <algorithm>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QDebug>

CQTs_skill::CQTs_skill(){
    Name  = "";
}

CQTs_skill::CQTs_skill(QString code, bool train):
    QString(code)
{
    Name  = "";
    trainedOnly = train;
}

QString CQTs_skill::myName(){
    return Name;
}

CQTs_skill CQTs_skill::finder (QString code){
    CQTs_skill toreturn(code,0);
    return toreturn;
}

void CQTs_skill::setmyName(QString name){
    Name  = name;
}

void CQTs_skill::setAbility(int abl){
    ability = abl;
}

bool CQTs_skill::needsTrain(){ return trainedOnly;}
int CQTs_skill::myAbility(){return ability;}
bool operator <(CQTs_skill a ,CQTs_skill b){return a.myName()<b.myName();}

//engine!
CQTs_engine::CQTs_engine(){
    loadSkills("Skills_data.xml");//I'm using english names as codes for the skills
    //loadSkillNames("Skills_Ita.xml");//I will add a menu!
    std::sort(Skills.begin(),Skills.end());
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
                /*
                while(!(xml.name()=="skill"&&xml.isEndElement())){
                    xml.readNext();
                    if(xml.name()=="synergy"&&xml.isStartElement()){//get synergies
                        QString desc = xml.attributes().value("circumstantial").toString();
                        while(!xml.readNext()==6);

                        skillAddress[id]->set_Synergies(codes.indexOf(xml.text().toString()),desc);
                    }
                }
                */
                CQTs_skill tSkill(code,train);
                tSkill.setAbility(abl);
                tSkill.setmyName(code);//in case skillnames are not loaded
                //tSkill.setArmor(arm);
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
                int id = Skills.indexOf((CQTs_skill::finder(code)));
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

/*****class handler*****/
/*ClassFile structure:
 *Class Name
 *lv max
 *datanumber 16*fort+8*ref+4*will+bab
 *bab= 1(01) poor, 2(10) good ,3(11) average
 *endoffile
 */

CQTs_Class::CQTs_Class(QString classLink){
    classLink.remove(".ClC");
    QFile file(classLink+".ClC");//temporary
    int data;//data-sink for bab and ST
    int F=16, R=8, W=4, bab=3;//mask for ST&BAB
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        Name="error";
        data=0;
        lmax=-1;
        //add an alert!
    }
    else{
        QTextStream in(&file);
        Name= in.readLine();
        in >> lmax;
        in >> data;
    }
    fort = (data & F)/F;//good? 0/1
    ref = (data & R)/R;//good? 0/1
    will = (data & W)/W;//good ?0/1
    BAB = (data & bab);// good 10, poor 01, average 11, i know it's not intuitive
    /*qDebug()<<Name;
    qDebug()<<lmax;
    qDebug()<<data;
    qDebug()<<BAB;
    qDebug()<<fort;
    qDebug()<<ref;
    qDebug()<<will;
*/
}

QString CQTs_Class::className(){return Name;}

int CQTs_Class::classBAB(){return BAB;}

bool CQTs_Class::STFort(){return fort;}

bool CQTs_Class::STRef(){return ref;}

bool CQTs_Class::STWill(){return will;}

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
