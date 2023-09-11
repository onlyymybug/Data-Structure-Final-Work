#ifndef ADDEXAM_H
#define ADDEXAM_H

#include <QWidget>
#include "exam.h"

class AddExam : public QWidget
{
    Q_OBJECT
public:
    int examNum;
    examInformation*exams;
    explicit AddExam(QWidget *parent = nullptr);
    explicit AddExam(examInformation*exams,int examNum);
    void closeEvent(QCloseEvent *);
signals:

public slots:
};

#endif // ADDEXAM_H
