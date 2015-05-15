#include "cqts_dataholder.h"
#include <QFile>
#include <QMessageBox>

void xmlHasError(QXmlStreamReader &xml,QString filename){
    QString ERROR=QObject::tr("Error in file:%4\n%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber())
            .arg(filename);
    QMessageBox::information(0, QString(QObject::tr("Error")), ERROR, QMessageBox::Ok);
}

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

void CQTS_infoHolder::setCode(QString code){
    int n = size();
    remove(0,n);
    append(code);
}

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

CQTs_skill::CQTs_skill(QXmlStreamReader &xml){
    synergies=NULL;
    descSyn=NULL;
    QString code = xml.attributes().value("code").toString();
    append(code);
    ability = xml.attributes().value("ability").toInt();
    //armor = xml.attributes().value("armor").toInt();
    trainedOnly = xml.attributes().value("onlytrained").toInt();
    Name=code;//in case skillnames are not loaded
    do{
        xml.readNext();
        if(xml.name()=="synergy"&&xml.isStartElement()){//get synergies
            QString SynCode = xml.attributes().value("syncode").toString();
            QString desc = xml.attributes().value("circumstantial").toString();
            add_Synergy(SynCode,desc);
        }
    }while(!(xml.name()=="skill"&&xml.isEndElement()));
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
    spellcaster = false;
    lmax = 0;
}

CQTs_Class::CQTs_Class(QString code):
    CQTS_infoHolder(code)
{
    for (int i = 0; i < 5; ++i) {
        info[i] = false;
    }
    spellcaster = false;
    lmax = 0;
}

CQTs_Class::CQTs_Class(QString code, bool data[5], int setDV, int setRanks, int MaxLV):
    CQTS_infoHolder(code)
{
    spellcaster = false;
    setParam(data, setDV, setRanks, MaxLV);
}

CQTs_Class::CQTs_Class(QXmlStreamReader &xml){
    spellcaster = false;
    //trusting this:if(xml.name()=="class"&&xml.isStartElement())
    QString code = xml.attributes().value("code").toString();
    append(code);
    Name = code;//in case classnames are not loaded
    bool bab1=false,bab2=false;
    int bab = xml.attributes().value("bab").toInt();
    if(bab==1)
        bab1=true;
    else if(bab==2)
        bab2=true;
    bool f = xml.attributes().value("fort").toInt();
    bool r = xml.attributes().value("ref").toInt();
    bool w = xml.attributes().value("will").toInt();
    bool data[5] = {bab1,bab2,f,r,w};
    std::copy(data,data+5,info);
    lmax = xml.attributes().value("lmax").toInt();
    QStringList skillList;
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
            DV = xml.attributes().value("dv").toInt();
            Ranks = xml.attributes().value("skillpoints").toInt();
            do{
                xml.readNext();
                if(xml.name()=="level"&&xml.isStartElement()){
                    //spell progression
                    int lv = xml.attributes().value("n").toInt();
                    if(xml.attributes().hasAttribute("spells")){
                        spellcaster = true;
                        for (int i = spellNumberList.size(); i < lv-1; ++i)
                            spellNumberList.append("-");
                        spellNumberList.append(xml.attributes().value("spells").toString());
                    }
                }
            }while(!(xml.name()=="progression"&&xml.isEndElement()));
        }

    }while(!(xml.isEndElement()&&xml.name()=="class"));
    if(skillList.size()>0)
        setSkills(skillList);
}

void CQTs_Class::setParam(bool data[5], int setDV, int setRanks, int MaxLV){
    Ranks =setRanks;
    DV = setDV;
    std::copy(data,data+5,info);
    lmax = MaxLV;
}

void CQTs_Class::writeData(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to save your class")), QMessageBox::Ok);
    }else{
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        writeDatatoXml(xml);
        xml.writeEndDocument();
    }
}

void CQTs_Class::writeDatatoXml(QXmlStreamWriter &xml){
    xml.writeStartElement("class");//opening class
    QString dummy(*this);//getting the code
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
        xml.writeStartElement("classskills");//opening classskills
        for (int i = 0; i < skillList.size(); ++i) {
            xml.writeStartElement("skill");//opening skill
            xml.writeAttribute("code",skillList[i]);
            xml.writeEndElement();//skill
        }
        xml.writeEndElement();//classskills
    }
    xml.writeStartElement("progression");//opening progression
    dummy.setNum(Ranks);
    xml.writeAttribute("skillpoints",dummy);
    dummy.setNum(DV);
    xml.writeAttribute("dv",dummy);
    //levelprogression reserved for spellcaster as now
    for(int i=0;i<lmax;i++){
        if(spellcaster&&(spellNumberList[i][spellNumberList[i].size()-1])!="-"){//"-" is no spell for that level
            xml.writeStartElement("level");//opening a level
            dummy.setNum(i);
            xml.writeAttribute("n",dummy);
            xml.writeAttribute("spells",spellNumberList[i]);
        }
    }
    xml.writeEndElement();//progression
    xml.writeEndElement();//class
    xml.writeEndDocument();
}

void CQTs_Class::setSkills(QStringList newSkills){
    skillList.clear();
    skillList.append(newSkills);
}
QStringList CQTs_Class::getSkills(){
    return skillList;
}

CQTs_Class& CQTs_Class::operator=(CQTs_Class x){
    clear();
    append(x);
    skillList.clear();
    skillList.append(x.skillList);
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

QString CQTs_Class::SpellList(int lv){
    int i = lv-1;//list starts from 0, levels from 1 hoping i'll remember it in future!
    QString toreturn = "-";
    if(i<lmax && spellcaster)
        toreturn = spellNumberList[i];
    return toreturn;
}
