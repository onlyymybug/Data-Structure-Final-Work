#include "teacheroperation.h"
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "activity.h"
#include <QLabel>
#include "deletecourse.h"
#include "mymessagebox.h"
#include "addcourse.h"
#include <QDebug>
#include "record.h"
#include "exam.h"
#include <QTimer>

extern int studentFlag;
extern QString resourcePath;
QTableWidget * manageTimeTable;
int teacherCoursesNum=0;
Activity * teacherCourses;

TeacherOperation::TeacherOperation(QWidget *parent) : QWidget(parent)
{
    studentFlag=0;
    Record * record = new Record(this);
    record->writeRecord("管理员登录了系统");
    this->resize(1600,1000);
    this->setWindowTitle("学生日程管理系统-管理端");
    this->setFont(QFont("宋体",12));

    QLabel * timetableTitle = new QLabel("学校课程表",this);
    timetableTitle->move(800,50);

    QPushButton * addCourseButton = new QPushButton("添加课程",this);
    QPushButton * deleteCourseButton = new QPushButton("删除课程",this);
    QPushButton * addExamButton = new QPushButton("添加考试",this);

    addCourseButton->setGeometry(50,100,180,80);
    deleteCourseButton->setGeometry(50,200,180,80);
    addExamButton->setGeometry(50,300,180,80);



    teacherCourses = new Activity[MAX_COURSE];

    manageTimeTable = new QTableWidget(this);
    manageTimeTable->setRowCount(11);
    manageTimeTable->setColumnCount(5);
    manageTimeTable->setWindowTitle("课程表");
    manageTimeTable->resize(1200,810);
    manageTimeTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    manageTimeTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);//行列表头居中
    manageTimeTable->setSelectionMode(QAbstractItemView::NoSelection);//不可选中
    manageTimeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑


    for(int i=0;i<11;i++)
        manageTimeTable->setRowHeight(i,70);
    for(int i=0;i<5;i++)
        manageTimeTable->setColumnWidth(i,215);

    manageTimeTable->move(300,100);


    manageTimeTable->setHorizontalHeaderLabels(QStringList()<<"星期一"<<"星期二"<<"星期三"<<"星期四"<<"星期五");
    manageTimeTable->setVerticalHeaderLabels(QStringList()<<"第一节\n8:00-9:00"<<"第二节\n9:00-10:00"<<"第三节\n10:00-11:00"
                                       <<"第四节\n11:00-12:00"<<"第五节\n13:00-14:00"<<"第六节\n14:00-15:00"
                                       <<"第七节\n15:00-16:00"<<"第八节\n16:00-17:00"<<"第九节\n17:00-18:00"
                                       <<"第十节\n18:00-19:00"<<"第十一节\n19:00-20:00");

    //QString courseFileName = "F:/QtFile/DataStructure/resource/classSchedule/basic.txt";
    FILE * courseResource = fopen((resourcePath+"/classSchedule/basic.txt").toLatin1().data(),"r");
//    int teacherCoursesNum=0;
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
        teacherCourses[i].setCourse(classfication,onOffLine,frequency,date,beginTime,endTime,
                                  QString::fromUtf8(tempBuilding),QString::fromUtf8(tempName));
        teacherCoursesNum++;
    }
    fclose(courseResource);
    teacherCoursesNum--;
    this->coursesNum=teacherCoursesNum;
    qDebug()<<this->coursesNum<<"节课";
    qDebug()<<teacherCourses[teacherCoursesNum-1].name;
    int beginTimeForTable[11]={8,9,10,11,13,14,15,16,17,18,19};
    for(int i=0;i<teacherCoursesNum;i++){
        for(int j=0;j<11;j++){
            if(teacherCourses[i].beginTime<=beginTimeForTable[j]&&teacherCourses[i].endTime>=beginTimeForTable[j]+1){

                manageTimeTable->setItem(j,teacherCourses[i].date.weekday-1,
                                   new QTableWidgetItem(teacherCourses[i].name+"\n"
                                                        +(teacherCourses[i].onOffLine==ONLINE?"线上":teacherCourses[i].building)));
                manageTimeTable->item(j,teacherCourses[i].date.weekday-1)->setTextAlignment(Qt::AlignCenter);
            }
            if(teacherCourses[i].endTime<=beginTimeForTable[j]+1){
                break;
            }
        }
    }
    manageTimeTable->show();


    connect(deleteCourseButton,&QPushButton::clicked,[=](){
        DeleteCourse * deleteCourse = new DeleteCourse(teacherCourses,teacherCoursesNum);
        deleteCourse->show();

    });

//    AddCourse * addCourse = new AddCourse(teacherCourses,teacherCoursesNum);
    connect(addCourseButton,&QPushButton::clicked,[=](){
        AddCourse * addCourse = new AddCourse(teacherCourses,teacherCoursesNum);
        addCourse->show();
    });


    connect(addExamButton,&QPushButton::clicked,[=](){
        Exam * examManage = new Exam();
        examManage->show();
    });
}

void TeacherOperation::updateTableWidght(){}

void DeleteCourse::closeEvent(QCloseEvent *){
    teacherCourses=this->courses;
    teacherCoursesNum=this->coursesNum;
    int beginTimeForTable[11]={8,9,10,11,13,14,15,16,17,18,19};
    manageTimeTable->clear();
    manageTimeTable->setHorizontalHeaderLabels(QStringList()<<"星期一"<<"星期二"<<"星期三"<<"星期四"<<"星期五");
    manageTimeTable->setVerticalHeaderLabels(QStringList()<<"第一节\n8:00-9:00"<<"第二节\n9:00-10:00"<<"第三节\n10:00-11:00"
                                       <<"第四节\n11:00-12:00"<<"第五节\n13:00-14:00"<<"第六节\n14:00-15:00"
                                       <<"第七节\n15:00-16:00"<<"第八节\n16:00-17:00"<<"第九节\n17:00-18:00"
                                       <<"第十节\n18:00-19:00"<<"第十一节\n19:00-20:00");
    for(int i=0;i<coursesNum;i++){
        for(int j=0;j<11;j++){
            if(this->courses[i].beginTime<=beginTimeForTable[j]&&this->courses[i].endTime>=beginTimeForTable[j]+1){

                manageTimeTable->setItem(j,this->courses[i].date.weekday-1,
                                   new QTableWidgetItem(this->courses[i].name+"\n"
                                                        +(this->courses[i].onOffLine==ONLINE?"线上":this->courses[i].building)));
                manageTimeTable->item(j,this->courses[i].date.weekday-1)->setTextAlignment(Qt::AlignCenter);
            }
            if(this->courses[i].endTime<=beginTimeForTable[j]+1){
                break;
            }
        }
    }
}

void AddCourse::closeEvent(QCloseEvent *){
    teacherCourses=this->courses;
    teacherCoursesNum=this->coursesNum;
    int beginTimeForTable[11]={8,9,10,11,13,14,15,16,17,18,19};
    manageTimeTable->clear();
    manageTimeTable->setHorizontalHeaderLabels(QStringList()<<"星期一"<<"星期二"<<"星期三"<<"星期四"<<"星期五");
    manageTimeTable->setVerticalHeaderLabels(QStringList()<<"第一节\n8:00-9:00"<<"第二节\n9:00-10:00"<<"第三节\n10:00-11:00"
                                       <<"第四节\n11:00-12:00"<<"第五节\n13:00-14:00"<<"第六节\n14:00-15:00"
                                       <<"第七节\n15:00-16:00"<<"第八节\n16:00-17:00"<<"第九节\n17:00-18:00"
                                       <<"第十节\n18:00-19:00"<<"第十一节\n19:00-20:00");
    for(int i=0;i<coursesNum;i++){
        for(int j=0;j<11;j++){
            if(this->courses[i].beginTime<=beginTimeForTable[j]&&this->courses[i].endTime>=beginTimeForTable[j]+1){

                manageTimeTable->setItem(j,this->courses[i].date.weekday-1,
                                   new QTableWidgetItem(this->courses[i].name+"\n"
                                                        +(this->courses[i].onOffLine==ONLINE?"线上":this->courses[i].building)));
                manageTimeTable->item(j,this->courses[i].date.weekday-1)->setTextAlignment(Qt::AlignCenter);
            }
            if(this->courses[i].endTime<=beginTimeForTable[j]+1){
                break;
            }
        }
    }
}

