#include "cqts_engine.h"
#include <QFile>
#include <QDir>

#include <QStringList>
#include <QTextStream>

#include <QDebug>

CQTs_engine::CQTs_engine()
{
}
/*****character handler*****/
/*CharacterFile structure:
 *Name
 *Surname
 *age
 *lv
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
        in >> LV >> HP >> BAB >> STf >> STr >> STw;
    }
    qDebug()<<bio.Name;
    qDebug()<<bio.Surname;
    qDebug()<<bio.age;
    qDebug()<<LV;
    qDebug()<<HP;
    qDebug()<<BAB;
    qDebug()<< STf <<"\t" << STr <<"\t"<< STw;
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
