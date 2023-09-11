#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QWidget>
#include "activity.h"

class AddCourse : public QWidget
{
    Q_OBJECT
public:
    Activity*courses;
    int coursesNum;
    explicit AddCourse(Activity*courses,int coursesNum);
    void closeEvent(QCloseEvent *);
signals:

public slots:
};

#endif // ADDCOURSE_H
