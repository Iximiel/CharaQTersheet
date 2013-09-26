#ifndef CQTS_CLASSVIEWER_H
#define CQTS_CLASSVIEWER_H

#include <QWidget>
#include <QGroupBox>
#include "cqts_engine.h"


class CQTs_ClassViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ClassViewer(QWidget *parent = 0);
    explicit CQTs_ClassViewer(CQTs_Class selected,QWidget *parent = 0);
private:

signals:

};

#endif // CQTS_CLASSVIEWER_H
