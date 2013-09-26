#ifndef CQTS_CLASSVIEWER_H
#define CQTS_CLASSVIEWER_H

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>

class CQTs_ClassViewer : public QGroupBox
{
    Q_OBJECT
public:
    explicit CQTs_ClassViewer(QWidget *parent = 0);
private:
    QComboBox *ComboSel;

signals:

public slots:
    void selected(QString id);

};

#endif // CQTS_CLASSVIEWER_H
