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

QStringList extensionFind(QString ext){
    //protocol to get list of files, may export it
    QDir currentDir;
    qDebug() << currentDir.dirName();

    QStringList files;// = new QStringList();
    files = currentDir.entryList(QStringList(ext),QDir::Files | QDir::NoSymLinks);
    int total =files.length();
    for (int i = 0; i < total; ++i) {
        qDebug() << files [i];
    }
    return files;
}
