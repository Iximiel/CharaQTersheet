#include "cqts_engine.h"
#include <QFile>
#include <QDir>

#include <algorithm>
#include <QMessageBox>
#include <QTextStream>
#include <QXmlStreamAttribute>

/*****engine******/

CQTs_engine::CQTs_engine(){
    /*todo
     * add setting.xml which contains the files where skills and classes are contained
     * and translations
     */
    loadFiles("Settings.xml");
    for (int i = 0; i < files.size(); ++i) {
        loadFromFile(files[i]);
    }
    //loadSkills("Skills_data.xml");//I'm using english names as codes for the skills
    //loadClasses("BaseClasses.xml");//I'm using english names as codes for the skills
    //loadSkillNames("Skills_Ita.xml");//I will add a menu!
    std::sort(Skills.begin(),Skills.end());
    std::sort(Classes.begin(),Classes.end());
}

void CQTs_engine::loadFiles(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to load files data")), QMessageBox::Ok);
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){
            //temp
            if(xml.isStartElement()){
                if(xml.attributes().hasAttribute("filename"))
                    files.push_back(xml.attributes().value("filename").toString());
            }
            if (xml.hasError()){
                xmlHasError(xml,filename);
                break;
            }
            xml.readNext();
        }
    }
}


void CQTs_engine::loadFromFile(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to load skills data")), QMessageBox::Ok);
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){
            if(xml.name()=="skills"&&xml.isStartElement()){
                do{
                    xml.readNext();
                    if(xml.name()=="skill"&&xml.isStartElement()){
                        CQTs_skill tSkill(xml);
                        while(Skills.contains(tSkill)){
                            tSkill.append("*");
                        }
                        Skills.append(tSkill);
                    }
                    if (xml.hasError()){
                        xmlHasError(xml,filename);
                        break;
                    }
                }while(!(xml.name()=="skills"&&xml.isEndElement()));
            }else if(xml.name()=="classes"&&xml.isStartElement()){
                do{
                    xml.readNext();
                    if(xml.name()=="class"&&xml.isStartElement())
                    {
                        CQTs_Class tClass(xml);
                        while(Classes.contains(tClass)){
                            tClass.append("*");
                        }
                        Classes.append(tClass);
                    }
                    if (xml.hasError()) {
                        xmlHasError(xml,filename);
                        break;
                    }
                }while(!(xml.name()=="classes"&&xml.isEndElement()));
            }
            if (xml.hasError()){
                xmlHasError(xml,filename);
                break;
            }
            xml.readNext();
        }
    }
}

void CQTs_engine::loadSkills(QString filename){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(0, QString(QObject::tr("Error")), QString(QObject::tr("Failed to load skills data")), QMessageBox::Ok);
    }
    else{
        QXmlStreamReader xml(&file);
        while(!xml.atEnd()){
            if(xml.name()=="skill"&&xml.isStartElement()){
                CQTs_skill tSkill(xml);
                while(Skills.contains(tSkill)){
                    tSkill.append("*");
                }
                Skills.append(tSkill);
            }
            if (xml.hasError()){
                xmlHasError(xml,filename);
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
                xmlHasError(xml,filename);
                break;
            }
            xml.readNext();
        }
        file.close();
    }
}

int CQTs_engine::skillNum(){return Skills.size();}

int CQTs_engine::getSkillNum(QString code){
    int toreturn = -1;
    if(Skills.contains(code)){
        for(int i =0;toreturn<0;i++){
            if(Skills.at(i) == code)//at() is faster than []
                toreturn = i;
        }
    }
    return toreturn;
}

CQTs_skill CQTs_engine::skillData(int i){return Skills[i];}

int CQTs_engine::classNum(){return Classes.size();}
CQTs_Class CQTs_engine::classData(int i){return Classes[i];}
CQTs_Class CQTs_engine::classData(QString code){
    CQTs_Class myclass;
    for (int i = 0; i < classNum(); ++i) {
        if(Classes.at(i) == code)//at() is faster than []
            myclass = Classes[i];
    }
    return myclass;
}

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
                CQTs_Class tClass(xml);
                while(Classes.contains(tClass)){
                    tClass.append("*");
                }
                Classes.append(tClass);
            }
            if (xml.hasError()) {
                xmlHasError(xml,filename);
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

void CQTs_engine::appendClass(CQTs_Class newclass){
    while(Classes.contains(newclass)){
        newclass.append("*");
    }
    Classes.append(newclass);
    std::sort(Classes.begin(),Classes.end());
}

void CQTs_engine::loadClassNames(QString filename){}

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
