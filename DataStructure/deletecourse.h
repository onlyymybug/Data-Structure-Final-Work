#ifndef DELETECOURSE_H
#define DELETECOURSE_H

#include <QWidget>
#include "activity.h"
#include <QCloseEvent>

class DeleteCourse : public QWidget
{
    Q_OBJECT
public:
    Activity*courses;
    int coursesNum;

    explicit DeleteCourse(Activity*courses,int coursesNum);
    void closeEvent(QCloseEvent*);

signals:

public slots:
    //void closeEvent(QCloseEvent*);
    void confirmCourses();
    void deleteOneCourse();
};

#endif // DELETECOURSE_H
