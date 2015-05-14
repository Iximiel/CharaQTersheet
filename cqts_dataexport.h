#ifndef CQTS_DATAEXPORT_H
#define CQTS_DATAEXPORT_H

#include <QWidget>
#include <QCheckBox>
#include "cqts_engine.h"

class CQTs_dataExport : public QWidget
{
    Q_OBJECT
public:
    enum CQTsdata{CQTs_CLASSES};
    explicit CQTs_dataExport(QString file, CQTs_engine *eng, CQTsdata setup, QWidget *parent = 0);
public slots:
    void doExport();
private:
    QString filename;
    CQTs_engine *engine;
    CQTsdata todo;
    QCheckBox **datacontainer;

    QWidget* loadClasses();
};

#endif // CQTS_DATAEXPORT_H
