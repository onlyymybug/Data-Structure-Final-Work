#include "activity.h"

Activity::Activity(QObject *parent) : QObject(parent)
{

}

Activity::Activity(int classfication,int frequency,Date date,int beginTime,int endTime,QString building,QString name)
{
    this->classfication=classfication;
    this->frequency=frequency;
    this->date=date;
    this->beginTime=beginTime;
    this->endTime=endTime;
    this->building=building;
    this->name=name;
}

void Activity::setCourse(int classfication,int onOffLine ,int frequency,
                         Date date, int beginTime, int endTime, QString building, QString name)
{
    this->classfication=classfication;
    this->onOffLine=onOffLine;
    this->frequency=frequency;
    this->date=date;
    this->beginTime=beginTime;
    this->endTime=endTime;
    this->building=building;
    this->name=name;
}


void Activity::setOutClassActivity(int classfication, int outClassType, int onOffLine, int frequency,
                                   Date date, int beginTime, int endTime, QString building, QString name)
{
    this->classfication=classfication;
    this->outClassType=outClassType;
    this->onOffLine=onOffLine;
    this->frequency=frequency;
    this->date=date;
    this->beginTime=beginTime;
    this->endTime=endTime;
    this->building=building;
    this->name=name;
}

void Activity::copyActivity(Activity activity){
    this->classfication=activity.classfication;
    this->outClassType=activity.outClassType;
    this->onOffLine=activity.onOffLine;
    this->frequency=activity.frequency;
    this->date=activity.date;
    this->beginTime=activity.beginTime;
    this->endTime=activity.endTime;
    this->building=activity.building;
    this->name=activity.name;
}


Activity::~Activity(){

}
