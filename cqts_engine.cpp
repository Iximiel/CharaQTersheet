#include "cqts_engine.h"
#include <QFile>
#include <QDir>

#include <QStringList>
#include <QTextStream>

#include <QDebug>

CQTs_engine::CQTs_engine()
{
}

/*****class handler*****/
/*ClassFile structure:
 *Class Name
 *lv max
 *datanumber
 *endofile
 */

CQTs_Class::CQTs_Class(QString classLink){
    QFile file(classLink+".ClC");
    int data;//data-sink for bab and ST
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        Name="error";
        data=0;
        lmax=-1;
    //add an alert!
       }
       else{
        int data;
        QTextStream in(&file);
        Name= in.readLine();
        in >> lmax;
        in >> data;
    }

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
