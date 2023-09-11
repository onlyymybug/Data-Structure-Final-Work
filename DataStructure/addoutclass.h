#ifndef ADDOUTCLASS_H
#define ADDOUTCLASS_H

#include <QWidget>
#include <QCloseEvent>
#include <activity.h>

class AddOutclass : public QWidget
{
    Q_OBJECT
public:
    QString thisUsername;
    Activity*courses;
    Activity*outclasses;
    int coursesNum;
    int outclassNum;
    explicit AddOutclass(QWidget *parent = nullptr);
    //void closeEvent(QCloseEvent *event);
    explicit AddOutclass(Activity*courses,Activity*outclasses,int coursesNum,int outClassNum,QString username);
signals:

public slots:
};

#endif // ADDOUTCLASS_H
