#ifndef EXAM_H
#define EXAM_H

#include <QWidget>
#include <QCloseEvent>

typedef struct examInformation
{
    QString name;
    QString building;
    int month;
    int day;
}examInformation;

class Exam : public QWidget
{
    Q_OBJECT
public:
    int examNum=0;
    examInformation exams[20];
    explicit Exam(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *);
    void hideButton();

signals:

public slots:
};

#endif // EXAM_H
