#ifndef ADDTEMP_H
#define ADDTEMP_H

#include <QWidget>
#include "activity.h"
#include <QCloseEvent>

class AddTemp : public QWidget
{
    Q_OBJECT
public:
    Activity*courses;
    Activity*outclasses;
    Activity*temporarys;
    int coursesNum;
    int outclassesNum;
    int temporarysNum;
    explicit AddTemp(QWidget *parent = nullptr);
    explicit AddTemp(Activity*courses,Activity*outclasses,Activity*temporary,
                     int coursesNum,int outclassesNum,int temporarysNum,QString username);
    //void closeEvent(QCloseEvent *event);
signals:

public slots:
};

#endif // ADDTEMP_H
