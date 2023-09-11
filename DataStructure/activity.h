#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>

#define COURSE 0//课程
#define OUT_CLASS_ACTIVITY 1//课外活动
#define TEMP_ACTIVITY 2//临时事务

#define PERSONAL 0
#define GROUP 1

#define ONLINE 0//线上
#define OFFLINE 1//线下

#define EVERYDAY 0//每天
#define EVERYWEEK 1//每周
#define ONE_WEEK 2//单周
#define SEVERAL_WEEK 3//几周

#define MAX_WEEK 20//活动最多进行的周数

#define MAX_COURSE 30//一周最多课程数
#define MAX_ONEDAY_COURSE 10//一天最多课程数
#define MAX_OUTCLASS 30//一周最多课外活动

#define MAX_NAME_LEN 50

typedef struct Date
{
    int month;//在多周时存总周数
    int day;
    int weeks[MAX_WEEK];
    int weekday;
}Date;


class Activity : public QObject
{
    Q_OBJECT
public:

    int classfication;//类型
    int outClassType;//课外活动的类型
    int onOffLine;//线上or线下
    int frequency=-1;//频率
    Date date;
    int beginTime;
    int endTime;
    QString building;
    QString name;

    explicit Activity(QObject *parent = nullptr);
    explicit Activity(int classfication,int frequency,Date date,
                      int beginTime,int endTime,QString building,QString name);
    void setCourse(int classfication,int onOffLine,int frequency,Date date,
                   int beginTime,int endTime,QString building,QString name);
    void setOutClassActivity(int classfication,int outClassType,int onOffLine,int frequency,Date date,
                             int beginTime,int endTime,QString building,QString name);
    void copyActivity(Activity activity);
    ~Activity();
signals:

public slots:
};

#endif // ACTIVITY_H
