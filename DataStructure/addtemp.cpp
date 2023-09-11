#include "addtemp.h"
#include <QComboBox>
#include "activity.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "mymessagebox.h"
#include <QDebug>
#include "record.h"

extern QString resourcePath;

AddTemp::AddTemp(QWidget *parent) : QWidget(parent)
{

}

AddTemp::AddTemp(Activity*courses,Activity*outclasses,Activity*temporarys,
                 int coursesNum,int outclassesNum,int temporarysNum,QString username){
    Record * record = new Record(this);
    this->courses=courses;
    this->coursesNum=coursesNum;
    this->outclasses=outclasses;
    this->outclassesNum=outclassesNum;
    this->temporarys=temporarys;
    this->temporarysNum=temporarysNum;
    this->setWindowTitle("添加临时事务");
    this->setFont(QFont("宋体",12));
    this->resize(600,800);

    QLabel * weekdayChooseLabel = new QLabel("添加星期      的临时事务",this);
    weekdayChooseLabel->move(100,100);
    QComboBox * weekdayChooseBox2;
    weekdayChooseBox2 = new QComboBox(this);
    weekdayChooseBox2->move(200,100);
    weekdayChooseBox2->addItems({"一","二","三","四","五","六","日"});

    QLabel * nameLabel = new QLabel("事务名称",this);
    nameLabel->move(100,180);
    QLineEdit * NameEdit = new QLineEdit(this);
    NameEdit->move(200,180);

    QLabel * beginTimeLabel = new QLabel("开始时间      时",this);
    beginTimeLabel->move(100,260);
    QComboBox * beginTimeBox = new QComboBox(this);
    beginTimeBox->move(200,260);
    beginTimeBox->addItems({"6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21"});

    QLabel * buildingLabel = new QLabel("事务地点",this);
    buildingLabel->move(100,340);
    QLineEdit * buildingEdit = new QLineEdit(this);
    buildingEdit->move(200,340);

    QPushButton * confirmAdd = new QPushButton("添加事务",this);
    confirmAdd->move(240,700);

    connect(confirmAdd,&QPushButton::clicked,[=](){
        bool canAdd = true;
        Date tempdate;
        int tempWeekday = weekdayChooseBox2->currentIndex()+1;
        tempdate.weekday=tempWeekday;
        qDebug()<<tempWeekday;
        int tempBegin=beginTimeBox->currentText().toInt();
        for(int i=0;i<this->coursesNum;i++){
            if(tempWeekday==this->courses[i].date.weekday&&
                    tempBegin>=this->courses[i].beginTime&&tempBegin<courses[i].endTime){
                canAdd = false;
                break;
            }
        }
        for(int i=0;i<this->outclassesNum;i++){
            if(tempWeekday==this->courses[i].date.weekday&&
                    tempBegin==this->outclasses[i].beginTime){
                canAdd = false;
                break;
            }
        }
        if(canAdd){
            this->temporarys[temporarysNum].date=tempdate;
            this->temporarys[temporarysNum].name=NameEdit->text();
            this->temporarys[temporarysNum].building=buildingEdit->text();
            this->temporarys[temporarysNum].beginTime=beginTimeBox->currentText().toInt();
            record->writeRecord("学生"+username+"添加了临时活动："+this->temporarys[temporarysNum].name);
            QString address = resourcePath+"/temporary/"+username+".txt";
            FILE * fp = fopen(address.toLatin1().data(),"a+");
            fprintf(fp,"%d %d %s %s\n",this->temporarys[temporarysNum].date.weekday,
                    this->temporarys[temporarysNum].beginTime,this->temporarys[temporarysNum].name.toUtf8().data(),
                    this->temporarys[temporarysNum].building.toUtf8().data());
            fclose(fp);
            MyMessageBox deleteSuccess;
            deleteSuccess.setWindowTitle("提示");
            deleteSuccess.setText("添加成功！");
            deleteSuccess.show();
            deleteSuccess.exec();
            this->close();
        }
        else{
            MyMessageBox deleteSuccess;
            deleteSuccess.setWindowTitle("提示");
            deleteSuccess.setText("添加失败！");
            deleteSuccess.show();
            deleteSuccess.exec();
        }
    });
}
