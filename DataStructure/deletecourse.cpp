#include "deletecourse.h"
#include "activity.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "mymessagebox.h"
#include "record.h"

QStringList coursesNames;
QComboBox * coursesBox;
QComboBox * weekdayChooseBox;
extern QString resourcePath;

DeleteCourse::DeleteCourse(Activity*courses,int coursesNum)
{
    Record * record = new Record(this);
    this->courses=courses;
    this->coursesNum=coursesNum;
    this->setWindowTitle("删除课程");
    this->setFont(QFont("宋体",12));
    this->resize(600,400);

    QLabel * weekdayChooseLabel = new QLabel("删除星期      的课程",this);
    weekdayChooseLabel->move(100,100);
    QString tempWeekdays[6] = {"","一","二","三","四","五"};
    weekdayChooseBox = new QComboBox(this);
    weekdayChooseBox->move(200,100);
    weekdayChooseBox->addItems({"一","二","三","四","五"});

    QLabel * courseNameChooseLabel = new QLabel("课程名称",this);
    courseNameChooseLabel->move(100,200);
    coursesBox = new QComboBox(this);
    coursesBox->resize(300,30);
    confirmCourses();
    coursesBox->move(200,200);
    connect(weekdayChooseBox,SIGNAL(currentIndexChanged(int)),this,SLOT(confirmCourses()));

    QPushButton * deleteButton = new QPushButton("删除",this);
    deleteButton->move(250,300);

    connect(deleteButton,&QPushButton::clicked,this,&DeleteCourse::deleteOneCourse);
    connect(deleteButton,&QPushButton::clicked,[=](){
        record->writeRecord("管理员删除了星期"+weekdayChooseBox->currentText()+"的课程"+coursesBox->currentText());
        MyMessageBox deleteSuccess;
        deleteSuccess.setWindowTitle("提示");
        deleteSuccess.setText("删除成功！");
        deleteSuccess.show();
        deleteSuccess.exec();
        this->close();
    });
}

void DeleteCourse::confirmCourses(){
    coursesBox->clear();
    coursesNames.clear();
    for(int i=0;i<this->coursesNum;i++){
        if(weekdayChooseBox->currentIndex()+1==courses[i].date.weekday)
            coursesNames<<this->courses[i].name;
    }
    coursesBox->addItems(coursesNames);
}

void DeleteCourse::deleteOneCourse(){
    for(int i=0;i<coursesNum;i++){
        if(this->courses[i].date.weekday==weekdayChooseBox->currentIndex()+1
                &&this->courses[i].name==coursesBox->currentText()){
            for(int j=i;j<coursesNum;j++){
                this->courses[j].classfication=this->courses[j+1].classfication;
                this->courses[i].outClassType=this->courses[j+1].outClassType;
                this->courses[j].onOffLine=this->courses[j+1].onOffLine;
                this->courses[j].frequency=this->courses[j+1].frequency;
                this->courses[j].date=this->courses[j+1].date;
                this->courses[j].beginTime=this->courses[j+1].beginTime;
                this->courses[j].endTime=this->courses[j+1].endTime;
                this->courses[j].building=this->courses[j+1].building;
                this->courses[j].name=this->courses[j+1].name;
            }
            this->coursesNum--;
            break;
        }
    }
    FILE * fp = fopen((resourcePath+"/classSchedule/basic.txt").toLatin1().data(),"w");
    for(int i=0;i<this->coursesNum;i++){
        fprintf(fp,"%d %d %d %d %d %d %s %s\n",this->courses[i].classfication,this->courses[i].onOffLine,this->courses[i].frequency,
                this->courses[i].date.weekday,this->courses[i].beginTime,this->courses[i].endTime,
                this->courses[i].building.toStdString().data(),this->courses[i].name.toStdString().data());
    }
    fclose(fp);
}
