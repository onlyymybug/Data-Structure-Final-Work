#include "temporarymanage.h"
#include "activity.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include "record.h"
#include <QPushButton>
#include "addtemp.h"
#include "deletetemp.h"

QTableWidget * temporaryTable;
Activity*courses3;
Activity*outclasses3;
Activity*temporary3;
int coursesNum3;
int outclassesNum3;
int temporaryNum3;

TemporaryManage::TemporaryManage(QWidget *parent) : QWidget(parent)
{

}

TemporaryManage::TemporaryManage(Activity*courses,Activity*outclasses,Activity*temporary,
                                 int coursesNum,int outclassesNum,int temporaryNum,QString username){
    courses3=courses;
    outclasses3=outclasses;
    temporary3=temporary;
    coursesNum3=coursesNum;
    outclassesNum3=outclassesNum;
    temporaryNum3=temporaryNum;

    this->resize(1200,800);
    this->setWindowTitle("临时事务管理");
    this->setFont(QFont("宋体",12));

    temporaryTable = new QTableWidget(this);

    temporaryTable->setRowCount(temporaryNum3);
    temporaryTable->setColumnCount(4);
    temporaryTable->setWindowTitle("本周临时事务");
    temporaryTable->resize(930,700);
    temporaryTable->move(250,50);
    temporaryTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    temporaryTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter);//行列表头居中
    temporaryTable->setSelectionMode(QAbstractItemView::NoSelection);//不可选中
    temporaryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑

    for(int i=0;i<temporaryNum3;i++)
        temporaryTable->setRowHeight(i,40);
    temporaryTable->setColumnWidth(0,200);
    temporaryTable->setColumnWidth(1,200);
    temporaryTable->setColumnWidth(2,200);
    temporaryTable->setColumnWidth(3,300);
    temporaryTable->setHorizontalHeaderLabels(QStringList()<<"星期"<<"时间"<<"名称"<<"地点");

    for(int i=0;i<temporaryNum3;i++){
        temporaryTable->setItem(i,0,new QTableWidgetItem(QString::number(temporary3[i].date.weekday)));
        temporaryTable->setItem(i,1,new QTableWidgetItem(QString::number(temporary3[i].beginTime)+":00"));
        temporaryTable->setItem(i,2,new QTableWidgetItem(temporary3[i].name));
        temporaryTable->setItem(i,3,new QTableWidgetItem(temporary3[i].building));
        for(int j=0;j<4;j++)
            temporaryTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
    }

    QPushButton * addTempButton = new QPushButton("添加事务",this);
    QPushButton * deleteTempButton = new QPushButton("删除事务",this);

    addTempButton->setGeometry(50,50,180,80);
    deleteTempButton->setGeometry(50,150,180,80);

    connect(addTempButton,&QPushButton::clicked,[=](){
        AddTemp * addTemp = new AddTemp(courses3,outclasses3,temporary3,coursesNum3,
                                        outclassesNum3,temporaryNum3,username);
        addTemp->show();
    });

    connect(deleteTempButton,&QPushButton::clicked,[=](){
        DeleteTemp * deleteTemp = new DeleteTemp(temporary3,temporaryNum3,username);
        deleteTemp->show();
    });
}
