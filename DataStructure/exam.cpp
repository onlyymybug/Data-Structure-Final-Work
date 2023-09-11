#include "exam.h"
#include <QPushButton>
#include "record.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "addexam.h"

QTableWidget * examTable;
int examNum=0;
examInformation*exams;
QPushButton * addExamButton;
extern QString resourcePath;

Exam::Exam(QWidget *parent) : QWidget(parent)
{
    Record * record = new Record(this);
    this->resize(800,500);
    this->setWindowTitle("考试管理");
    this->setFont(QFont("宋体",12));

    addExamButton = new QPushButton("添加考试",this);
    addExamButton->setGeometry(350,400,100,50);
    examTable = new QTableWidget(this);

    examTable->setRowCount(5);
    examTable->setColumnCount(3);
    examTable->setWindowTitle("考试");
    examTable->resize(600,300);
    examTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    examTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);//行列表头居中
    examTable->setSelectionMode(QAbstractItemView::NoSelection);//不可选中
    examTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑

    for(int i=0;i<2;i++)
        examTable->setRowHeight(i,40);
    examTable->setColumnWidth(0,190);
    examTable->setColumnWidth(1,190);
    examTable->setColumnWidth(2,190);
    examTable->move(100,50);
    examTable->setHorizontalHeaderLabels(QStringList()<<"课程名称"<<"考试地点"<<"考试时间");
    FILE * examResource = fopen((resourcePath+"/exam/exam.txt").toLatin1().data(),"r");
    for(int i=0;feof(examResource)==0;i++){
        char tempname[20];
        char tempbuilding[20];
        fscanf(examResource,"%s %s %d %d",tempname,tempbuilding,
               &exams[i].month,&exams[i].day);
        examNum++;
        exams[i].name=QString::fromUtf8(tempname);
        exams[i].building=QString::fromUtf8(tempbuilding);
    }
    examNum--;
    for(int i=0;i<examNum;i++){
        exams[i]=exams[i];
    }
    examTable->setRowCount(examNum);
    for(int i=0;i<examNum;i++){
        examTable->setItem(i,0,new QTableWidgetItem(exams[i].name));
        examTable->setItem(i,1,new QTableWidgetItem(exams[i].building));
        examTable->setItem(i,2,new QTableWidgetItem(QString::number(exams[i].month)+"月"
                                                    +QString::number(exams[i].day)+"日"));
        for(int j=0;j<3;j++)
            examTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
    }

    connect(addExamButton,&QPushButton::clicked,[=](){
        AddExam * addexam = new AddExam(exams,examNum);
        addexam->show();
    });
}

void AddExam::closeEvent(QCloseEvent *){
    int tempExamNum=0;
    examTable->clear();
    examTable->setHorizontalHeaderLabels(QStringList()<<"课程名称"<<"考试地点"<<"考试时间");
    FILE * examResource = fopen((resourcePath+"/exam/exam.txt").toLatin1().data(),"r");
    for(int i=0;feof(examResource)==0;i++){
        char tempname[20];
        char tempbuilding[20];
        fscanf(examResource,"%s %s %d %d",tempname,tempbuilding,
               &this->exams[i].month,&this->exams[i].day);
        exams[i].name=QString::fromUtf8(tempname);
        exams[i].building=QString::fromUtf8(tempbuilding);
        tempExamNum++;
    }
    tempExamNum--;
    examTable->setRowCount(tempExamNum);
    for(int i=0;i<tempExamNum;i++){
        examTable->setItem(i,0,new QTableWidgetItem(exams[i].name));
        examTable->setItem(i,1,new QTableWidgetItem(exams[i].building));
        examTable->setItem(i,2,new QTableWidgetItem(QString::number(exams[i].month)+"月"
                                                    +QString::number(exams[i].day)+"日"));
        for(int j=0;j<3;j++)
            examTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
    }
}

void Exam::hideButton(){
    addExamButton->hide();
}
