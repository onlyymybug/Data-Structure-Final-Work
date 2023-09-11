#ifndef STUDENTOPERATION_H
#define STUDENTOPERATION_H

#include <QWidget>

class StudentOperation : public QWidget
{
    Q_OBJECT
public:
    QString studentUsername;
    explicit StudentOperation(QWidget *parent = nullptr);
    explicit StudentOperation(QString username);
    void setStudentUsername(QString username);

signals:

public slots:
    void changeSpeed(int index);
};

#endif // STUDENTOPERATION_H
