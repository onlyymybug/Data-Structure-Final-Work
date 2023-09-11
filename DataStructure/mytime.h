#ifndef MYTIME_H
#define MYTIME_H

#include <QObject>



class MyTime : public QObject
{
    Q_OBJECT
public:
    explicit MyTime(QObject *parent = nullptr);
    explicit MyTime(int year,int month,int day,int hour,int minute,int weekday,int weekNum);

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int weekday;
    int weekNum;

    bool isLeep();
    void after1s();
    QString toString();
    QString toOutputString();

signals:

public slots:
};

#endif // MYTIME_H
