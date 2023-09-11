#include "outclassactivitymanage.h"
#include "activity.h"
#include <QPushButton>
#include <stdio.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>
#include "addoutclass.h"
#include "deleteoutclass.h"

QTableWidget * outclassTable;
QString thisUsername;
Activity*courses2;
Activity*outclasses2;
int coursesNum2;
int outclassNum2;
extern QString resourcePath;

OutClassActivityManage::OutClassActivityManage(Activity*courses,Activity*outclasses,int coursesNum,int outClassNum,QString username)
{
    thisUsername=username;
    courses2=courses;
    outclasses2=outclasses;
    coursesNum2=coursesNum;
    outclassNum2=outClassNum;
    this->resize(1400,800);
    this->setWindowTitle("课外活动管理");
    this->setFont(QFont("宋体",12));

    outclassTable = new QTableWidget(this);

    outclassTable->setRowCount(outclassNum2);
    outclassTable->setColumnCount(6);
    outclassTable->setWindowTitle("本周活动");
    outclassTable->resize(1130,700);
    outclassTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    outclassTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);//行列表头居中
    outclassTable->setSelectionMode(QAbstractItemView::NoSelection);//不可选中
    outclassTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑

    for(int i=0;i<outclassNum2;i++)
        outclassTable->setRowHeight(i,40);
    outclassTable->setColumnWidth(0,150);
    outclassTable->setColumnWidth(1,200);
    outclassTable->setColumnWidth(2,100);
    outclassTable->setColumnWidth(3,150);
    outclassTable->setColumnWidth(4,200);
    outclassTable->setColumnWidth(5,300);

    outclassTable->move(190,50);
    outclassTable->setHorizontalHeaderLabels(QStringList()<<"周期"<<"日期"<<"活动类型"<<"开始时间"<<"活动名称"<<"活动地点/链接");

    QString tempName[4]={"每天","每周","单次","数周"};
    QString tempW;
    for(int i=0;i<outClassNum;i++){
        qDebug()<<outclasses[i].building<<outclasses[i].name<<outclasses[i].beginTime;
            outclassTable->setItem(i,0,new QTableWidgetItem(tempName[outclasses[i].frequency]));
            if(outclasses[i].frequency==EVERYDAY)
                tempW = "每天";
            if(outclasses[i].frequency==EVERYWEEK)
                tempW = "每周";
            if(outclasses[i].frequency==ONE_WEEK)
                tempW = QString::number(outclasses[i].date.month)+"月"+QString::number(outclasses[i].date.day)+"日";
            outclassTable->setItem(i,1,new QTableWidgetItem(tempW));
            outclassTable->setItem(i,2,new QTableWidgetItem((outclasses[i].outClassType==PERSONAL?
                                                               "个人":"集体")));
            outclassTable->setItem(i,3,new QTableWidgetItem(QString::number(outclasses[i].beginTime)+":00"));
            outclassTable->setItem(i,4,new QTableWidgetItem(outclasses[i].name));
            outclassTable->setItem(i,5,new QTableWidgetItem(outclasses[i].building));
            for(int j=0;j<6;j++)
                outclassTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
    }

    QPushButton * addOutclassButton = new QPushButton("活动添加",this);
    QPushButton * deleteOutclassButton = new QPushButton("活动删除",this);
    addOutclassButton->setGeometry(30,50,120,50);
    deleteOutclassButton->setGeometry(30,130,120,50);
    addOutclassButton->show();
    deleteOutclassButton->show();

    connect(addOutclassButton,&QPushButton::clicked,[=](){
        AddOutclass * addoutclass = new AddOutclass(courses2,outclasses2,coursesNum2,outclassNum2,thisUsername);
        addoutclass->show();
    });

    connect(deleteOutclassButton,&QPushButton::clicked,[=](){
        DeleteOutclass * deleteOutclass = new DeleteOutclass(outclasses2,outclassNum2,thisUsername);
        deleteOutclass->show();
    });
}

