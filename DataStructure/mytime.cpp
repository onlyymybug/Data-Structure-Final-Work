#include "mytime.h"

int EachMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

MyTime::MyTime(int year,int month,int day,int hour,int minute,int weekday,int weekNum)
{
    this->year=year;
    this->month=month;
    this->day=day;
    this->hour=hour;
    this->minute=minute;
    this->weekday=weekday;
    this->weekNum=weekNum;
}

bool MyTime::isLeep(){
    if(this->year%100==0){
        if(this->year%400==0)
            return true;
        else
            return false;
    }
    else{
        if(this->year%4==0)
            return true;
        else
            return false;
    }
}

void MyTime::after1s(){
    //默认1s=6min
    this->minute+=6;
    if(this->minute>=60){
        this->minute%=60;
        this->hour++;
    }
    if(this->hour>=24){
        this->hour%=24;
        this->day++;
        this->weekday++;
    }
    if(this->weekday>7){
        this->weekday%=7;
        this->weekNum++;
    }
    int temp=EachMonth[this->month];
    if(this->isLeep()&&this->month==2)
        temp++;
    if(this->day>temp){
        this->day%=temp;
        this->month++;
    }
    if(this->month>12){
        this->month%=12;
        year++;
    }
}

QString MyTime::toString(){
    QString tempmonth = QString::number(this->month);
    QString tempday = QString::number(this->day);
    QString temphour = QString::number(this->hour);
    QString tempminute = QString::number(this->minute);
    if(tempmonth.length()==1)
        tempmonth="0"+tempmonth;
    if(tempday.length()==1)
        tempday="0"+tempday;
    if(temphour.length()==1)
        temphour="0"+temphour;
    if(tempminute.length()==1)
        tempminute="0"+tempminute;
    return QString::number(this->year)+"/"+tempmonth+"/"+tempday+"_"+temphour
            +":"+tempminute+"_"+QString::number(this->weekday)+"_"+QString::number(this->weekNum);
}

QString MyTime::toOutputString(){
    QString tempmonth = QString::number(this->month);
    QString tempday = QString::number(this->day);
    QString temphour = QString::number(this->hour);
    QString tempminute = QString::number(this->minute);
    QString tempweek[8]={"","星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
    if(tempmonth.length()==1)
        tempmonth="0"+tempmonth;
    if(tempday.length()==1)
        tempday="0"+tempday;
    if(temphour.length()==1)
        temphour="0"+temphour;
    if(tempminute.length()==1)
        tempminute="0"+tempminute;
    return QString::number(this->year)+"年"+tempmonth+"月"+tempday+"日"+temphour
            +":"+tempminute+" "+tempweek[this->weekday] + " " + "第"+QString::number(this->weekNum)+"周";
}
