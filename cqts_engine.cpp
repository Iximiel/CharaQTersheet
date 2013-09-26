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
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);

            Name= in.readLine();
            in >> lmax;
            in >> data;

}

/*****utilities*****/

QStringList extensionFind(QString ext,QString dir){
    //protocol to get list of files, may export it
    QDir currentDir(dir);

    QStringList filelist;
    filelist = currentDir.entryList(QStringList(ext),QDir::Files | QDir::NoSymLinks);
    return filelist;
}

QStringList extensionFind(QString ext){
    return extensionFind(ext,"./");
}
