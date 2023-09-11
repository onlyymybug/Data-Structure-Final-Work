#ifndef TEACHEROPERATION_H
#define TEACHEROPERATION_H

#include <QWidget>
#include "activity.h"

class TeacherOperation : public QWidget
{
    Q_OBJECT
public:
    Activity*courses;
    int coursesNum;
    explicit TeacherOperation(QWidget *parent = nullptr);

signals:

public slots:
    void updateTableWidght();
};

#endif // TEACHEROPERATION_H
