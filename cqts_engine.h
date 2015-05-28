//the engine is the "globalresourcepack" of my prog
#ifndef CQTS_ENGINE_H
#define CQTS_ENGINE_H
#include "cqts_dataholder.h"
#include <QMap>

//container for everithing that will need a tranlsation

class CQTs_engine//it holds all data related to the game, like skills, max level and conf files
{
public:
    CQTs_engine();
    //skills manipulation
    int skillNum();
    int getSkillNum(QString code);
    CQTs_skill skillData(int i);
    //classes manipulation
    int classNum();
    CQTs_Class classData(int i);
    CQTs_Class classData(QString code);
    QStringList classNames();
    void appendClass(CQTs_Class newclass);
private:
    //QStringList confFiles;// 0 skills 1 skillnames 2 classes 3 classnames
    void loadFiles(QString filename);
    void loadFromFile(QString filename);
    void loadSkills(QString filename);
    void loadSkillNames(QString filename);
    void loadClasses(QString filename);
    void loadClassNames(QString filename);
    QStringList files;
    QList<CQTs_skill> Skills;
    QList<CQTs_Class> Classes;
    QList<CQTs_Race> Races;
};

#endif // CQTS_ENGINE_H

#ifndef UTILITIES
#define UTILITIES
#include <QStringList>

QStringList extensionFind(QString ext, QString dir);
QStringList extensionFind(QString ext);
#endif //UTILITIES
