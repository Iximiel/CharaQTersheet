//the engine is the "globalresorcepack" of my prog
#ifndef CQTS_ENGINE_H
#define CQTS_ENGINE_H

class CQTs_engine
{
public:
    CQTs_engine();
};

#endif // CQTS_ENGINE_H

#ifndef CQTS_CLASS
#define CQTS_CLASS
#include <QString>

class CQTs_Class
{
public:
    CQTs_Class(QString classLink);

private:
    QString Name;
    int lmax;//20,10,5,3 so he can understand if is baseclass or not//may be made compatible with d20System in general
    int data;//tell me core stats: binary: xxxxx FRWAB FRW 0/1 each (good or bad) BAB:00 01 10
    //next: adding class skills and privileges
};

#endif //CQTS_CLASS
