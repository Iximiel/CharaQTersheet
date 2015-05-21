#ifndef CQTS_CHARACTERCREATOR_H
#define CQTS_CHARACTERCREATOR_H
#include "cqts_engine.h"
#include "cqts_character.h"
#include <QWidget>

class CQTs_CharacterCreator : public QWidget
{
    Q_OBJECT
public:
    explicit CQTs_CharacterCreator(CQTs_engine* eng, QWidget *parent = 0);
private:
    CQTs_engine *engine;
signals:

public slots:
};

#endif // CQTS_CHARACTERCREATOR_H
