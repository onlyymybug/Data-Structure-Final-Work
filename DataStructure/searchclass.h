#ifndef SEARCHCLASS_H
#define SEARCHCLASS_H

#include <QWidget>
#include "activity.h"
#include <QCloseEvent>

class SearchClass : public QWidget
{
    Q_OBJECT
public:

    explicit SearchClass(QWidget *parent = nullptr);
    explicit SearchClass(Activity*courses,int totalCourses);
    ~SearchClass();
signals:

public slots:
    void closeEvent(QCloseEvent*);
};

#endif // SEARCHCLASS_H
