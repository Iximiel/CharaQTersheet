#include "cqts_character.h"
#include "cqts_dataholder.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamAttribute>


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
        version = xml.attributes().value("version").toString();
        if(version == "0.03")
            load003(xml);
        else
            load005(xml);
        file.close();
    }
}

void CQTs_Character::load003(QXmlStreamReader &xml){
    level myOnlyThing;
    myOnlyThing.thisLVclass = "003";
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
                    myOnlyThing.skillRanks.insert(code,ranks);
                }
                xml.readNext();
            }
        }
        //if(xml.name()=="feats"&&xml.isStartElement()){}
        if (xml.hasError()) {
            xmlHasError(xml,"characterfile");
        }
        xml.readNext();
    }
    levelHistory.push_back(myOnlyThing);
}

void CQTs_Character::load005(QXmlStreamReader &xml){
    myOnlyThing.thisLVclass = "003";
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
        if(xml.name()=="data"&&xml.isStartElement()){//togli data aggiungi possibilit' di salvare/caricare gli aumenti di caratteristica

            while(!(xml.name()=="data"&&xml.isEndElement())){

                if(xml.name()=="abilities"&&xml.isStartElement()){
                    int abl[6];
                    while(!(xml.name()=="abilities"&&xml.isEndElement())){
                        if(xml.name()=="ability"&&xml.isStartElement()){
                            QString code = xml.attributes().value("which").toString();
                            while(!xml.readNext()==6);
                            //qDebug() << code;
                            if(code == "strength"){
                                abl[STR]= (xml.text().toInt());
                            }else if(code == "dexterity"){
                                abl[DEX]= (xml.text().toInt());
                            }else if(code == "constitution"){
                                abl[CON]= (xml.text().toInt());
                            }else if(code == "intelligence"){
                                abl[INT]= (xml.text().toInt());
                            }else if(code == "wisdom"){
                                abl[WIS]= (xml.text().toInt());
                            }else if(code == "charisma"){
                                abl[CHA]= (xml.text().toInt());
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
                    myOnlyThing.skillRanks.insert(code,ranks);
                }
                xml.readNext();
            }
        }
        //if(xml.name()=="feats"&&xml.isStartElement()){}
        if (xml.hasError()) {
            xmlHasError(xml,"characterfile");
        }
        xml.readNext();
    }
    levelHistory.push_back(myOnlyThing);
}

void CQTs_Character::saveToFile(QString filename){
    if(filename != ""){
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to save your character")), QMessageBox::Ok);
        }else{
            QXmlStreamWriter xml(&file);
            xml.setAutoFormatting(true);
            xml.setAutoFormattingIndent(2);
            xml.writeStartDocument();
            xml.writeStartElement("character");
            xml.writeAttribute("version","0.05");
            xml.writeStartElement("bio");//open bio
            xml.writeTextElement("name",bio.Name);
            xml.writeTextElement("surname",bio.Surname);
            xml.writeTextElement("age",QString::number(bio.age));
            xml.writeEndElement();//bio
            xml.writeStartElement("abilities");//writing abilities at lv 1
            QString names[6]={"strength","dexterity","constitution","intelligence","wisdom","charisma"};
            for (int i = 0; i < 6; ++i) {
                xml.writeStartElement("ability");//opening ability
                xml.writeAttribute("which",names[i]);
                xml.writeCharacters(QString::number(Abilities[i]));
                xml.writeEndElement();//ability
            }
            xml.writeEndElement();//abilities
            xml.writeStartElement("progression");//opening progression
            if(!levelHistory.empty()){
                for(int i=0;i<levelHistory.size();i++){
                    xml.writeStartElement("lv");
                    QString tLV = QString::number(i+1);
                    xml.writeAttribute("n",tLV);
                    xml.writeAttribute("class",levelHistory[i].thisLVclass);
                    xml.writeStartElement("skills");
                    for (int i = 0; i < levelHistory[i].skillRanks.size(); ++i) {
                        xml.writeStartElement("skill");
                        QString code = levelHistory[i].skillRanks.keys().at(i);
                        xml.writeAttribute("code",code);
                        xml.writeCharacters(QString::number(levelHistory[i].skillRanks[code]));
                        xml.writeEndElement();//skill
                    }
                    xml.writeEndElement();//skills
                }
            }
            xml.writeEndElement();//progression
            xml.writeEndElement();//character
            xml.writeEndDocument();
        }
    }
}

void CQTs_Character::update(){
    //resetting things
    LV=HP=BAB=STf=STr=STw=0;
    for(int i=0;i<6;i++)
        Abilities[i] = 0;
    QMap<QString,int> TakenClasses;
    for(int i=0;i<levelHistory.size();i++){//counting levels and updating abilities
        QString code = levelHistory[i].thisLVclass;
        if(TakenClasses.contains(code))
            TakenClasses[code]++;
        else
            TakenClasses.insert(code,1);
        for(int j=0;j<6;j++)
            Abilities[j] += levelHistory[i].AbilitiyCNGs[j];
        //HP+=levelHistory[i].HP;
    }
    if(levelHistory[i].thisLVclass!="003"){
        //following the book (not using fractional bonuses)
        QMap<QString,int>::iterator classes = TakenClasses.begin();
        for(int i=0;i<TakenClasses.size();i++){//counting BAB and STs
            QString code = (classes+i).key();
            int howManyLV = (classes+i).value();
            LV+=howManyLV;
            CQTs_Class myclass = engine->classData(code);
            if(myclass.STFort())
                STf+=2+howManyLV/2.;
            else
                STf+=howManyLV/3.;
            if(myclass.STRef())
                STr+=2+howManyLV/2.;
            else
                STr+=howManyLV/3.;
            if(myclass.STWill())
                STw+=2+howManyLV/2.;
            else
                STw+=howManyLV/3.;
            int bab = myclass.BAB();
            switch (bab) {
            case 0:
                dbab = (howManyLV)/2.;
                break;
            case 1:
                dbab = (howManyLV)*3/4.;
                break;
            case 2:
                dbab = howManyLV;
                break;
            }
            HP+=howManyLV*myclass.HP();//maximized HPs
        }
        HP+=LV*getAbilityMod(CON);
    }
}

void CQTs_Character::addLevel(QString classCode, QMap<QString,int> ranks, int AbilitiyCNGs[6]){
    newlevel.thisLVclass = classCode;
    level newlevel;
    for (int i = 0; i < 6; ++i)
        newlevel.AbilitiyCNGs[i] =  AbilitiyCNGs[i];
    newlevel.skillRanks = ranks;
    levelHistory.push_back(newlevel);
    update();
}

void CQTs_Character::addLevel(QString classCode, QMap<QString,int> ranks){
    int zero[6]={0,0,0,0,0,0};
    addLevel(classCode,ranks,zero);
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
        return getFortitude();
        break;
    case 1:
        return getReflex();
        break;
    case 2:
        return getWill();
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
    int toreturn = 0;
    for (int i = 0; i < levelHistory.size(); ++i) {
        if(levelHistory[i].skillRanks.contains(code))
            toreturn += levelHistory[i].skillRanks[code];
    }
    return toreturn;
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
void CQTs_Character::setAbilityMod(int lv, CQT_Abilities sel, int newAbilityM){//taking real level!
    levelHistory[lv-1].AbilitiyCNGs[sel] = newAbilityM;
}
void CQTs_Character::setAbilityMod(int lv, int sel, int newAbilityM){
    levelHistory[lv-1].AbilitiyCNGs[sel] = newAbilityM;
}
void CQTs_Character::setAbilitiesMod(int lv, int newAbilitiesM[6]){
    for (int i = 0; i < 6;i++)
        levelHistory[lv-1].AbilitiyCNGs[i] = newAbilitiesM[i];
}
void CQTs_Character::setRanks(int lv, QString code, int newRanks){
    levelHistory[lv-1].skillRanks[code] = newRanks;
}
void CQTs_Character::setRanks(int lv, QMap<QString,int> newSkillRanks){
    levelHistory[lv-1].skillRanks.clear();
    levelHistory[lv-1].skillRanks = newSkillRanks;
}