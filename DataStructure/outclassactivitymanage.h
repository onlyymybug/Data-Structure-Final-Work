#ifndef OUTCLASSACTIVITYMANAGE_H
#define OUTCLASSACTIVITYMANAGE_H

#include <QWidget>
#include "activity.h"
#include <QCloseEvent>

class OutClassActivityManage : public QWidget
{
    Q_OBJECT
public:
    explicit OutClassActivityManage(Activity*courses,Activity*outclasses,int coursesNum,int outClassNum,QString username);

signals:

public slots:
    void closeEvent(QCloseEvent*);
};

#endif // OUTCLASSACTIVITYMANAGE_H
