#ifndef TEMPORARYMANAGE_H
#define TEMPORARYMANAGE_H

#include <QWidget>
#include "activity.h"
#include <QCloseEvent>

class TemporaryManage : public QWidget
{
    Q_OBJECT
public:
    explicit TemporaryManage(QWidget *parent = nullptr);
    explicit TemporaryManage(Activity*courses,Activity*outclasses,Activity*temporary,
                             int coursesNum,int outclassesNum,int temporaryNum,QString username);
    void closeEvent(QCloseEvent *event);
signals:

public slots:
};

#endif // TEMPORARYMANAGE_H
