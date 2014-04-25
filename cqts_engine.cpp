#include "cqts_engine.h"
#include <QFile>
#include <QDir>

#include <QStringList>
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

bool CQTs_skill::operator <(CQTs_skill b){
    return Name<b.Name;
}

//engine!
CQTs_engine::CQTs_engine(){
    loadSkills();
    loadSkillNames();
}

void CQTs_engine::loadSkills(){
    QFile file("Skills_data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // qDebug()<<"errore lettura";
        //add an alert!
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){

            if(xml.name()=="skill"&&xml.isStartElement())
            {
                QString code;
                int abl;//, arm;
                bool train;
                //QStringList Synergies, cyrcSinergies;
                while(!(xml.name()=="skill"&&xml.isEndElement())){
                    xml.readNext();
                    if(xml.name()=="code"&&xml.isStartElement()){//get the code
                        while(!xml.readNext()==6);

                        code = (xml.text().toString());
                    }
                    if(xml.name()=="ability"&&xml.isStartElement()){//get the ability related
                        while(!xml.readNext()==6);

                        abl = xml.text().toInt();
                    }/*
                    if(xml.name()=="armor"&&xml.isStartElement()){//get armor penality
                        while(!xml.readNext()==6);

                        arm = xml.text().toInt();
                    }*/
                    if(xml.name()=="onlytrained"&&xml.isStartElement()){//get trained only
                        while(!xml.readNext()==6);

                        train =xml.text().toInt();
                    }/*
                    if(xml.name()=="synergy"&&xml.isStartElement()){//get synergies
                        while(!xml.readNext()==6);

                        skillAddress[id]->set_Synergies(codes.indexOf(xml.text().toString()));
                    }
                    if(xml.name()=="circumstantial"&&xml.isStartElement()){//get cyrcumstantial synergies
                        while(!xml.readNext()==6);

                        skillAddress[id]->set_CyrcSynergies(codes.indexOf(xml.text().toString()));
                    }*/
                }
                CQTs_skill tSkill(code,train);
                tSkill.setAbility(abl);
                //tSkill.setArmor(arm);
                Skills.append(tSkill);
            }
            if (xml.hasError()) {
                // do error handling
            }
            xml.readNext();
        }
    }
    file.close();
}

void CQTs_engine::loadSkillNames(){

    QFile file("Skills_Eng.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        // qDebug()<<"errore";
        //add an alert!
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){
            if(xml.name()=="skill"&&xml.isStartElement())
            {
                QString code,name;
                while(!(xml.name()=="skill"&&xml.isEndElement())){
                    xml.readNext();
                    if(xml.name()=="code"&&xml.isStartElement()){//taking code
                        while(!xml.readNext()==6);
                        code = xml.text().toString();
                    }
                    if(xml.name()=="name"&&xml.isStartElement()){//taking names
                        while(!xml.readNext()==6);
                        name=xml.text().toString();
                    }
                }
                int id = Skills.indexOf((CQTs_skill::finder(code)));
                if(id!=-1)
                {
                    Skills[id] .setmyName(name);
                }
            }
            if (xml.hasError()) {
                // do error handling
            }
            xml.readNext();
        }
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
CQTs_Character::CQTs_Character(QString filename){
    LV=HP=BAB=STf=STr=STw=0;
    for (int i = 0; i < 6;Abilities[i++]=0 );
    loadFromFile(filename);
    /*//old loader
    filename.remove(".chc");
    QFile file(filename+".chc");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        bio.Name=bio.Surname="error";
        bio.age=HP=LV=BAB=STf=STr=STw=0;
        //add an alert!
    }
    else{
        QTextStream in(&file);
        bio.Name= in.readLine();
        bio.Surname= in.readLine();
        in >> bio.age;
        in >> LV ;
        for(int i=0;i<6;i++)
            in >> Abilities [i];
        in >> HP >> BAB >> STf >> STr >> STw;
    }*/
    /*
    qDebug()<<bio.Name;
    qDebug()<<bio.Surname;
    qDebug()<<bio.age;
    qDebug()<<LV;
    qDebug()<<HP;
    qDebug()<<BAB;
    qDebug()<< STf <<"\t" << STr <<"\t"<< STw;
    */
}

void CQTs_Character::loadFromFile(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        bio.Name=bio.Surname="error";
        bio.age=HP=LV=BAB=STf=STr=STw=0;
        //add an alert!
    }else{
        QXmlStreamReader xml(&file);
        while(!(xml.name()=="character"&&xml.isStartElement()))
            xml.readNext();

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
                    /*
                    if(xml.name()=="strength"&&xml.isStartElement()){
                        while(!xml.readNext()==6);

                        Abilities[STR]= (xml.text().toInt());
                    }
                    if(xml.name()=="dexterity"&&xml.isStartElement()){
                        while(!xml.readNext()==6);

                        Abilities[DEX]= (xml.text().toInt());
                    }
                    if(xml.name()=="constitution"&&xml.isStartElement()){
                        while(!xml.readNext()==6);

                        Abilities[CON]= (xml.text().toInt());
                    }
                    if(xml.name()=="intelligence"&&xml.isStartElement()){
                        while(!xml.readNext()==6);

                        Abilities[INT]= (xml.text().toInt());
                    }
                    if(xml.name()=="wisdom"&&xml.isStartElement()){
                        while(!xml.readNext()==6);

                        Abilities[WIS]= (xml.text().toInt());
                    }
                    if(xml.name()=="charisma"&&xml.isStartElement()){
                        while(!xml.readNext()==6);

                        Abilities[CHA]= (xml.text().toInt());
                    }*/

                }
            }

            if(xml.name()=="skills"&&xml.isStartElement()){//get the ranks in skills
                while(!(xml.name()=="skills"&&xml.isEndElement())){//get the bio info
                    if(xml.name()=="skill"&&xml.isStartElement()){//get the name
                        QString code = xml.attributes().value("code").toString();
                        while(!xml.readNext()==6);
                        //qDebug() << code;
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
    filename.remove(".chc");
    QFile file(filename+".chc");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //add an alert!
    }
    else{
        QTextStream out(&file);
        out << bio.Name << '\n';
        out << bio.Surname << '\n';
        out << bio.age << '\n';
        out << LV << '\n';
        out << Abilities [0];
        for(int i=1;i<6;i++)
            out << Abilities [i] << '\t';
        out <<'\n';
        out << HP <<'\n' << BAB <<'\n' << STf <<'\n' << STr  <<'\n' << STw  <<'\n';
    }
}

QString CQTs_Character::getName(){return bio.Name;}
QString CQTs_Character::getSurname(){return bio.Surname;}
int CQTs_Character::getAge(){return bio.age;}
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
int CQTs_Character::getRanks(QString code){
    if(skillRanks.contains(code)){
        return skillRanks[code];
    }else return 0;
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
