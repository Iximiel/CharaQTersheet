#include "cqts_engine.h"
#include <QFile>
#include <QDir>

#include <QStringList>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QDebug>

CQTs_skill::CQTs_skill(){
    Name  = "";
}

CQTs_skill::CQTs_skill(QString name){
    Name  = name;
}

QString CQTs_skill::myName(){
    return Name;
}


CQTs_engine::CQTs_engine(){
    QFile file("Skills_Eng.txt");//first load the language file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //add an alert!
    }
    else{
        QXmlStreamReader xml(&file);
        xml.readNext();
        while(xml.name()!="skills")
             xml.readNext();
        while(!xml.atEnd()){
            if(xml.readNext() == 4){
                QString code=xml.name().toString();
                xml.readNext();
                QString name = xml.text().toString();
                skilladdress.push_back(code);
                Skills.insert(code,name);
            }
            if (xml.hasError()) {
                // do error handling
            }
        }
        file.close();
    }
}
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
    }
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
    if(i==0)
        return STf;
    if(i==1)
        return STr;
    if(i==2)
        return STw;
    return 0;//to make compiler calm
}
int CQTs_Character::getAbility(CQT_Abilities sel){return Abilities[sel];}
int CQTs_Character::getAbility(int sel){return Abilities[sel];}
int CQTs_Character::getAbilityMod(int sel){return (Abilities[sel]-10)/2.;}

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
