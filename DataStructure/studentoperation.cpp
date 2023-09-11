#include "studentoperation.h"
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <stdio.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "mytime.h"
#include "activity.h"
#include <QTextCodec>
#include "searchclass.h"
#include <QDialog>
#include "mymessagebox.h"
#include <QComboBox>
#include "outclassactivitymanage.h"
#include "map.h"
#include "exam.h"
#include "temporarymanage.h"
#include "record.h"

#define MAX_LEN_TIME 20

extern QString resourcePath;
Activity * courses = new Activity[MAX_COURSE];
Activity * outclasses = new Activity[MAX_OUTCLASS];
Activity * temporarys = new Activity[20];
int coursesNum=0;
int outclassesNum=0;
int temporarysNum=0;
QTimer*timer;
int speed=1;
int speeds[4]={1,2,5,10};
int studentFlag=1;
QString username1;

StudentOperation::StudentOperation(QString username)
{
    studentFlag=1;
    Record * record = new Record(this);
    record->writeRecord("学生"+username+"登录了系统");
    username1=username;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    this->setWindowTitle("学生日程管理系统-学生端");
    this->setFont(QFont("宋体",12));

    QPushButton * courseButton = new QPushButton("课程查询",this);
    QPushButton * navigationButton = new QPushButton("地图导航",this);
    QPushButton * outClassButton = new QPushButton("课外活动",this);
    QPushButton * searchExamButton = new QPushButton("查看考试",this);
    QPushButton * temporaryThingButton = new QPushButton("临时事务",this);
    courseButton->setGeometry(50,100,180,80);
    navigationButton->setGeometry(50,200,180,80);
    outClassButton->setGeometry(50,300,180,80);
    searchExamButton->setGeometry(50,500,180,80);
    temporaryThingButton->setGeometry(50,400,180,80);
    courseButton->show();
    navigationButton->show();
    outClassButton->show();
    searchExamButton->show();
    temporaryThingButton->show();

    map * navigation = new map(this);

    connect(navigationButton,&QPushButton::clicked,[=](){
        navigation->showButton1();
        timer->stop();
        navigation->show();
    });

    FILE * timeResource =fopen((resourcePath+"/time/time.txt").toLatin1().data(),"r+");
//    FILE * timeResource =fopen("F:/QtFile/DataStructure/resource/time/time.txt","r+");
    int tempyear,tempmonth,tempday,temphour,tempminute,tempweekday,tempweeknum;
    fscanf(timeResource,"%d/%d/%d_%d:%d_%d_%d",&tempyear,&tempmonth,&tempday,&temphour,&tempminute,&tempweekday,&tempweeknum);

    MyTime * myTime = new MyTime(tempyear,tempmonth,tempday,temphour,tempminute,tempweekday,tempweeknum);
    QLabel * showTime = new QLabel(myTime->toOutputString(),this);
    showTime->move(300,50);

    //qDebug()<<myTime->year<<myTime->month<<myTime->day<<myTime->hour<<myTime->minute;

    QLabel * timeSpeedLabel = new QLabel("倍速： "+this->studentUsername,this);
    timeSpeedLabel->move(710,50);
    QComboBox * speedChoose = new QComboBox(this);
    speedChoose->addItems({"1","2","5","10"});
    speedChoose->move(780,50);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,[=]()mutable{
        myTime->after1s();
        fseek(timeResource,0,SEEK_SET);
        fputs(myTime->toString().toLatin1().data(),timeResource);
        showTime->setText(myTime->toOutputString());
    });
    //qDebug()<<speed<<"cnm";
    timer->start(1000/speed);

    connect(speedChoose,SIGNAL(currentIndexChanged(int)),this,SLOT(changeSpeed(int)));

    this->studentUsername=username;
    QLabel * loginUserName = new QLabel("欢迎： "+this->studentUsername,this);
    loginUserName->move(50,50);

    QTableWidget * timeTable = new QTableWidget(this);
    timeTable->setRowCount(11);
    timeTable->setColumnCount(5);
    timeTable->setWindowTitle("课程表");
    timeTable->resize(1200,810);
    timeTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    timeTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);//行列表头居中
    timeTable->setSelectionMode(QAbstractItemView::NoSelection);//不可选中
    timeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑


    for(int i=0;i<11;i++)
        timeTable->setRowHeight(i,70);
    for(int i=0;i<5;i++)
        timeTable->setColumnWidth(i,215);

    timeTable->move(300,100);


    timeTable->setHorizontalHeaderLabels(QStringList()<<"星期一"<<"星期二"<<"星期三"<<"星期四"<<"星期五");
    timeTable->setVerticalHeaderLabels(QStringList()<<"第一节\n8:00-9:00"<<"第二节\n9:00-10:00"<<"第三节\n10:00-11:00"
                                       <<"第四节\n11:00-12:00"<<"第五节\n13:00-14:00"<<"第六节\n14:00-15:00"
                                       <<"第七节\n15:00-16:00"<<"第八节\n16:00-17:00"<<"第九节\n17:00-18:00"
                                       <<"第十节\n18:00-19:00"<<"第十一节\n19:00-20:00");

    //QString courseFileName = "F:/QtFile/DataStructure/resource/classSchedule/" + username + ".txt";
    FILE * courseResource = fopen((resourcePath+"/classSchedule/basic.txt").toLatin1().data(),"r");

    //int coursesNum=0;
    for(int i=0;feof(courseResource)==0;i++){
        int classfication;
        int onOffLine;
        int frequency;
        Date date;
        int beginTime;
        int endTime;
        //QString building;
        //QString name;
        char tempBuilding[MAX_NAME_LEN];
        char tempName[MAX_NAME_LEN];
        fscanf(courseResource,"%d %d %d %d %d %d %s %s",&classfication,&onOffLine,&frequency,&date.weekday,
               &beginTime,&endTime,tempBuilding,tempName);
        qDebug()<<tempBuilding<<QString::fromUtf8(tempBuilding)<<tempName<<QString::fromUtf8(tempName);
        courses[i].setCourse(classfication,onOffLine,frequency,date,beginTime,endTime,
                                  QString::fromUtf8(tempBuilding),QString::fromUtf8(tempName));
        coursesNum++;
    }
    coursesNum--;
    int beginTimeForTable[11]={8,9,10,11,13,14,15,16,17,18,19};
    for(int i=0;i<coursesNum;i++){
        for(int j=0;j<11;j++){
            if(courses[i].beginTime<=beginTimeForTable[j]&&courses[i].endTime>=beginTimeForTable[j]+1){

                timeTable->setItem(j,courses[i].date.weekday-1,
                                   new QTableWidgetItem(courses[i].name+"\n"
                                                        +(courses[i].onOffLine==ONLINE?"线上":courses[i].building)));
                timeTable->item(j,courses[i].date.weekday-1)->setTextAlignment(Qt::AlignCenter);
            }
            if(courses[i].endTime<=beginTimeForTable[j]+1){
                break;
            }
        }
    }
    timeTable->show();

    //QString outclassFileName = "F:/QtFile/DataStructure/resource/outClass/" + username + ".txt";
    FILE * outClassResource =fopen((resourcePath+ "/outClass/" + username + ".txt").toLatin1().data(),"r+");

//    int outclassesNum=0;
    for(int i=0;feof(outClassResource)==0;i++){
        int classfication;
        int outClassType;
        int onOffLine;
        int frequency;
        Date date;
        int beginTime;
        char tempBuilding[MAX_NAME_LEN];
        char tempName[MAX_NAME_LEN];

        fscanf(outClassResource,"%d %d %d %d",&classfication,&outClassType,&onOffLine,&frequency);

        if(frequency==0){//每天
            fscanf(outClassResource,"%d %s %s",&beginTime,tempBuilding,tempName);
        }
        else if(frequency==1) {//每周
            fscanf(outClassResource,"%d %d %s %s",&date.weekday,&beginTime,tempBuilding,tempName);
        }
        else if(frequency==2){//单周（单次
            fscanf(outClassResource,"%d %d %d %d %s %s",&date.month,&date.day,&date.weekday,&beginTime,tempBuilding,tempName);
        }
        outclasses[i].setOutClassActivity(classfication,outClassType,onOffLine,frequency,date,
                                          beginTime,beginTime+1,tempBuilding,tempName);
        outclassesNum++;
        qDebug()<<outclasses[i].building<<outclasses[i].name;
    }
    outclassesNum--;

    QString temporaryFileName = resourcePath+"/temporary/" + username + ".txt";
    FILE * temporaryResource =fopen(temporaryFileName.toLatin1().data(),"r+");

    for(int i=0;feof(temporaryResource)==0;i++){
        int weekday;
        int begintime;
        char name[20];
        char building[20];
        fscanf(temporaryResource,"%d %d %s %s",&weekday,&begintime,name,building);
        temporarys[i].date.weekday=weekday;
        temporarys[i].beginTime=begintime;
        temporarys[i].name=QString::fromUtf8(name);
        temporarys[i].building=QString::fromUtf8(building);
        temporarysNum++;
    }
    temporarysNum--;

    //map * navigation = new map("TEMP");
    connect(timer,&QTimer::timeout,[=](){
        int temp;

        MyMessageBox courseRemindBox;
        courseRemindBox.setMySize(500,300);
        courseRemindBox.setWindowTitle("课程提醒");
        QPushButton * ViewNavigationButton = courseRemindBox.addButton("更多", QMessageBox::AcceptRole);
        for(int i=0;i<coursesNum;i++){
            if(courses[i].date.weekday==myTime->weekday&&courses[i].beginTime-1==myTime->hour&&myTime->minute==0){
                temp=i;
                timer->stop();
                courseRemindBox.setText("1小时后有课程：" + courses[i].name + "\n时间："+ QString::number(courses[i].beginTime) + ":00"
                                        + " - " + QString::number(courses[i].endTime) + ":00");
                courseRemindBox.show();
                courseRemindBox.exec();
            }
        }
        if(courseRemindBox.clickedButton()==ViewNavigationButton){
            qDebug()<<"wdnmd";
//            timer->start(1000);
            if(courses[temp].onOffLine==ONLINE){
                MyMessageBox onlineInformation;
                onlineInformation.setWindowTitle("线上课程链接");
                QPushButton * agreeButton = onlineInformation.addButton("确定", QMessageBox::AcceptRole);
                onlineInformation.setText("链接："+courses[temp].building);
                onlineInformation.show();
                onlineInformation.exec();
                if(onlineInformation.clickedButton()==agreeButton){
                    timer->start(1000/speed);
                }
            }
            if(courses[temp].onOffLine==OFFLINE){
                qDebug()<<courses[temp].building;
                navigation->showButton3();
                navigation->setFinalName(courses[temp].building);
                navigation->show();
            }
        }

    });

    connect(timer,&QTimer::timeout,[=](){
        int temp=0;
        QString tempText = "明日课程：\n";
        MyMessageBox courseRemindBox;
        courseRemindBox.setMySize(600,400);
        courseRemindBox.setWindowTitle("明日课程提醒");
        if(myTime->hour==22&&myTime->minute==0){
            for(int i=0;i<coursesNum;i++){
                if(courses[i].date.weekday==(myTime->weekday+1)%7){
                    tempText += QString::number(courses[i].beginTime)+ ":" + "00" + "-"
                            + QString::number(courses[i].endTime) + ":" + "00" + " " + courses[i].name
                            + " " + courses[i].building + "\n";
                    temp++;
                }
            }
            if(temp==0){
                tempText+="无课程\n";
            }
            else {
                temp=0;
            }
            tempText += "明日活动：\n";
            for(int i=0;i<outclassesNum;i++){
                if(outclasses[i].frequency==EVERYDAY||outclasses[i].date.weekday==(myTime->weekday+1)%1){
                    tempText += QString::number(outclasses[i].beginTime)+ ":" + "00" + "-"
                            + QString::number(outclasses[i].endTime) + ":" + "00" + " " + outclasses[i].name
                            + " " + outclasses[i].building + "\n";
                    temp++;
                }
            }
            if(temp==0){
                tempText+="无活动";
            }
            courseRemindBox.setText(tempText);
            courseRemindBox.show();
            courseRemindBox.exec();
        }
    });

    //map * navigationWindowForOnce = new map("WIN");
    connect(timer,&QTimer::timeout,[=](){
        int temp;

        MyMessageBox outclassRemindBox;
        outclassRemindBox.setMySize(500,300);
        outclassRemindBox.setWindowTitle("活动提醒");
        QPushButton * ViewNavigationButton = outclassRemindBox.addButton("更多", QMessageBox::AcceptRole);
        for(int i=0;i<outclassesNum;i++){
            if((outclasses[i].frequency==EVERYDAY||outclasses[i].date.weekday==myTime->weekday)&&
                    outclasses[i].beginTime-1==myTime->hour&&myTime->minute==0){
                temp=i;
                timer->stop();
                outclassRemindBox.setText("1小时后有活动：" + outclasses[i].name + "\n时间："
                                        + QString::number(outclasses[i].beginTime) + ":00"
                                        + " - " + QString::number(outclasses[i].endTime) + ":00");
                outclassRemindBox.show();
                outclassRemindBox.exec();
            }
        }
        if(outclassRemindBox.clickedButton()==ViewNavigationButton){
            qDebug()<<"wdnmd";
//            timer->start(1000);
            if(outclasses[temp].onOffLine==ONLINE){
                MyMessageBox onlineInformation;
                onlineInformation.setWindowTitle("线上活动链接");
                QPushButton * agreeButton = onlineInformation.addButton("确定", QMessageBox::AcceptRole);
                onlineInformation.setText("链接："+outclasses[temp].building);
                onlineInformation.show();
                onlineInformation.exec();
                if(onlineInformation.clickedButton()==agreeButton){
                    timer->start(1000/speed);
                }
            }
            if(outclasses[temp].onOffLine==OFFLINE){
                navigation->showButton3();
                navigation->setFinalName(outclasses[temp].building);
                qDebug()<<outclasses[temp].building;
                navigation->show();
            }
        }

    });

    connect(timer,&QTimer::timeout,[=](){
        bool ifhave=false;
        int count=0;
        QString passnames[10];
        MyMessageBox outclassRemindBox;
        QString temps;
        outclassRemindBox.setMySize(500,300);
        outclassRemindBox.setWindowTitle("临时事务提醒");
        QPushButton * ViewNavigationButton = outclassRemindBox.addButton("更多", QMessageBox::AcceptRole);
        for(int i=0;i<temporarysNum;i++){
            if((temporarys[i].date.weekday==myTime->weekday)&&
                    temporarys[i].beginTime-1==myTime->hour&&myTime->minute==0){
                timer->stop();
                temps+=temporarys[i].name+"\n";
                navigation->passnames[count+1]=temporarys[i].building;
                qDebug()<<passnames[count+1];
                count++;
                ifhave = true;
            }
        }
        if(ifhave){
            outclassRemindBox.setText("1小时后有临时事务：\n" + temps);
            outclassRemindBox.show();
            outclassRemindBox.exec();
            if(outclassRemindBox.clickedButton()==ViewNavigationButton){
                    navigation->showButton2();
                    navigation->locationsNum=count+1;
                    navigation->show();
            }
        }
    });

    SearchClass * searchClass = new SearchClass(courses,coursesNum);
    connect(courseButton,&QPushButton::clicked,[=](){
        timer->stop();
        searchClass->show();
    });

//    OutClassActivityManage * outClassActivityManage
//            = new OutClassActivityManage(courses,outclasses,coursesNum,outclassesNum,username);
    connect(outClassButton,&QPushButton::clicked,[=](){
        OutClassActivityManage * outClassActivityManage
                = new OutClassActivityManage(courses,outclasses,coursesNum,outclassesNum,username);
        timer->stop();
        outClassActivityManage->show();
    });

    connect(searchExamButton,&QPushButton::clicked,[=](){
        timer->stop();
        Exam * viewExam = new Exam(NULL);
        viewExam->hideButton();
        viewExam->show();
    });

    connect(temporaryThingButton,&QPushButton::clicked,[=](){
        timer->stop();
        TemporaryManage * temporaryManage = new TemporaryManage(courses,outclasses,temporarys,
                                                                coursesNum,outclassesNum,temporarysNum,username);
        temporaryManage->show();
    });

}


void StudentOperation::setStudentUsername(QString username){
    this->studentUsername=username;
}

void SearchClass::closeEvent(QCloseEvent *)
{
    timer->start(1000/speed);
}

void MyMessageBox::closeEvent(QCloseEvent *)
{
    timer->start(1000/speed);
}

void map::closeEvent(QCloseEvent *)
{
    timer->start(1000/speed);
    this->clearLineEdit();
}

void StudentOperation::changeSpeed(int index)
{
    timer->stop();
    speed=speeds[index];
    qDebug()<<speed;
    timer->start(1000/speed);
}

void OutClassActivityManage::closeEvent(QCloseEvent*)
{
    //QString outclassFileName = "F:/QtFile/DataStructure/resource/outClass/" + username1 + ".txt";
    FILE * outClassResource =fopen((resourcePath+ "/outClass/" + username1 + ".txt").toLatin1().data(),"r+");

    timer->start(1000/speed);
    outclassesNum=0;
    for(int i=0;feof(outClassResource)==0;i++){
        int classfication;
        int outClassType;
        int onOffLine;
        int frequency;
        Date date;
        int beginTime;
        char tempBuilding[MAX_NAME_LEN];
        char tempName[MAX_NAME_LEN];

        fscanf(outClassResource,"%d %d %d %d",&classfication,&outClassType,&onOffLine,&frequency);

        if(frequency==0){//每天
            fscanf(outClassResource,"%d %s %s",&beginTime,tempBuilding,tempName);
        }
        else if(frequency==1) {//每周
            fscanf(outClassResource,"%d %d %s %s",&date.weekday,&beginTime,tempBuilding,tempName);
        }
        else if(frequency==2){//单周（单次
            fscanf(outClassResource,"%d %d %d %d %s %s",&date.month,&date.day,&date.weekday,&beginTime,tempBuilding,tempName);
        }
        outclasses[i].setOutClassActivity(classfication,outClassType,onOffLine,frequency,date,
                                          beginTime,beginTime+1,tempBuilding,tempName);
        outclassesNum++;
        qDebug()<<outclasses[i].building<<outclasses[i].name;
    }
    outclassesNum--;
}

void Exam::closeEvent(QCloseEvent *){
    if(studentFlag==1)
    {
        timer->start(1000/speed);
    }
}

void TemporaryManage::closeEvent(QCloseEvent *event){
    timer->start(1000/speed);
    //QString temporaryFileName = "F:/QtFile/DataStructure/resource/temporary/" + username1 + ".txt";
    FILE * temporaryResource =fopen((resourcePath+"/temporary/" + username1 + ".txt").toLatin1().data(),"r+");
    temporarysNum=0;
    for(int i=0;feof(temporaryResource)==0;i++){
        int weekday;
        int begintime;
        char name[20];
        char building[20];
        fscanf(temporaryResource,"%d %d %s %s",&weekday,&begintime,name,building);
        temporarys[i].date.weekday=weekday;
        temporarys[i].beginTime=begintime;
        temporarys[i].name=QString::fromUtf8(name);
        temporarys[i].building=QString::fromUtf8(building);
        temporarysNum++;
    }
    temporarysNum--;
}
