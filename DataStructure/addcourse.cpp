#include "addcourse.h"
#include <QComboBox>
#include "activity.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "mymessagebox.h"
#include <QDebug>
#include "record.h"

extern QString resourcePath;

AddCourse::AddCourse(Activity*courses,int coursesNum)
{
    Record * record = new Record(this);
    this->courses=courses;
    this->coursesNum=coursesNum;
    this->setWindowTitle("添加课程");
    this->setFont(QFont("宋体",12));
    this->resize(600,800);

    QLabel * weekdayChooseLabel = new QLabel("添加星期      的课程",this);
    weekdayChooseLabel->move(100,100);
    QComboBox * weekdayChooseBox2;
    weekdayChooseBox2 = new QComboBox(this);
    weekdayChooseBox2->move(200,100);
    weekdayChooseBox2->addItems({"一","二","三","四","五"});

    QLabel * courseNameChooseLabel = new QLabel("课程名称",this);
    courseNameChooseLabel->move(100,180);
    QLineEdit * courseName = new QLineEdit(this);
    courseName->move(200,180);

    QLabel * chooseOnofflineLabel = new QLabel("课程形式",this);
    chooseOnofflineLabel->move(100,260);
    QComboBox * onofflineBox = new QComboBox(this);
    onofflineBox->move(200,260);
    onofflineBox->addItems({"线上","线下"});

    QLabel * buildingChooseLabel = new QLabel("上课地点",this);
    buildingChooseLabel->move(100,340);
    QLineEdit * buildingName = new QLineEdit(this);
    buildingName->move(200,340);

    QLabel * beginTimeLabel = new QLabel("开始时间",this);
    beginTimeLabel->move(100,420);
    QComboBox * beginTimeBox = new QComboBox(this);
    beginTimeBox->move(200,420);
    beginTimeBox->addItems({"8","9","10","11","13","14","15","16","17","18","19"});

    QLabel * endTimeLabel = new QLabel("结束时间",this);
    endTimeLabel->move(100,500);
    QComboBox * endTimeBox = new QComboBox(this);
    endTimeBox->move(200,500);
    endTimeBox->addItems({"9","10","11","12","14","15","16","17","18","19","20"});

    QPushButton * confirmAdd = new QPushButton("添加课程",this);
    confirmAdd->move(240,600);

    connect(confirmAdd,&QPushButton::clicked,[=](){
        bool canAdd = true;
        Date tempDate;
        tempDate.weekday=weekdayChooseBox2->currentIndex()+1;
        for(int i=0;i<this->coursesNum;i++){
            if(this->courses[i].date.weekday==tempDate.weekday&&
                    ((this->courses[i].beginTime<endTimeBox->currentText().toInt()&&
                    endTimeBox->currentText().toInt()<=this->courses[i].endTime)
                    ||(this->courses[i].beginTime<=beginTimeBox->currentText().toInt()&&
                       beginTimeBox->currentText().toInt()<this->courses[i].endTime))){
                canAdd=false;
                break;
            }
        }
        if(canAdd){
            record->writeRecord("管理员添加了星期"+weekdayChooseBox2->currentText()+"的课程"+courseName->text());
            qDebug()<<"添加了课程";
            this->courses[coursesNum].setCourse(0,1,1,tempDate,beginTimeBox->currentText().toInt(),
                                                   endTimeBox->currentText().toInt(),buildingName->text(),courseName->text());
            this->coursesNum++;
            FILE * fp = fopen((resourcePath+"/classSchedule/basic.txt").toLatin1().data(),"w");
            for(int i=0;i<this->coursesNum;i++){
                fprintf(fp,"%d %d %d %d %d %d %s %s\n",this->courses[i].classfication,this->courses[i].onOffLine,
                        this->courses[i].frequency,
                        this->courses[i].date.weekday,this->courses[i].beginTime,this->courses[i].endTime,
                        this->courses[i].building.toStdString().data(),this->courses[i].name.toStdString().data());
            }
            fclose(fp);
            MyMessageBox deleteSuccess;
            deleteSuccess.setWindowTitle("提示");
            deleteSuccess.setText("添加成功！");
            deleteSuccess.show();
            deleteSuccess.exec();
            this->close();
        }
        else {
            record->writeRecord("管理员添加课程"+courseName->text()+"失败");
            qDebug()<<"添加你摩洛哥炒饼";
            MyMessageBox deleteFailed;
            deleteFailed.setWindowTitle("提示");
            deleteFailed.setText("添加失败！\n时间与现有课程冲突！");
            deleteFailed.show();
            deleteFailed.exec();
        }
    });
}
