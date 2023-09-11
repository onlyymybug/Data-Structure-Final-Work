#include "addoutclass.h"
#include <QComboBox>
#include "activity.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "mymessagebox.h"
#include <QDebug>
#include "record.h"

extern QString resourcePath;

AddOutclass::AddOutclass(QWidget *parent){}

AddOutclass::AddOutclass(Activity*courses,Activity*outclasses,int coursesNum,int outclassNum,QString username)
{
    Record * record = new Record(this);
    this->courses=courses;
    this->coursesNum=coursesNum;
    this->outclasses=outclasses;
    this->outclassNum=outclassNum;
    this->setWindowTitle("添加课程");
    this->setFont(QFont("宋体",12));
    this->resize(600,800);

    QLabel * weekdayChooseLabel = new QLabel("添加星期      的活动",this);
    weekdayChooseLabel->move(100,100);
    QComboBox * weekdayChooseBox2;
    weekdayChooseBox2 = new QComboBox(this);
    weekdayChooseBox2->move(200,100);
    weekdayChooseBox2->addItems({"一","二","三","四","五"});

    QLabel * NameChooseLabel = new QLabel("活动名称",this);
    NameChooseLabel->move(100,180);
    QLineEdit * outclassName = new QLineEdit(this);
    outclassName->move(200,180);

    QLabel * chooseOnofflineLabel = new QLabel("活动形式",this);
    chooseOnofflineLabel->move(100,260);
    QComboBox * onofflineBox = new QComboBox(this);
    onofflineBox->move(200,260);
    onofflineBox->addItems({"个人","集体"});

    QLabel * buildingChooseLabel = new QLabel("活动地点",this);
    buildingChooseLabel->move(100,340);
    QLineEdit * buildingName = new QLineEdit(this);
    buildingName->move(200,340);

    QLabel * beginTimeLabel = new QLabel("开始时间",this);
    beginTimeLabel->move(100,420);
    QComboBox * beginTimeBox = new QComboBox(this);
    beginTimeBox->move(200,420);
    beginTimeBox->addItems({"6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21"});

    QLabel * frequencyLabel = new QLabel("活动频率",this);
    frequencyLabel->move(100,500);
    QComboBox * frequencyBox = new QComboBox(this);
    frequencyBox->move(200,500);
    frequencyBox->addItems({"每天","每周","一周"});

    QLabel * dateLabel = new QLabel("活动时间      月      日",this);
    dateLabel->move(100,580);
    QComboBox * monthBox = new QComboBox(this);
    monthBox->move(200,580);
    monthBox->addItems({"3","4","5","6"});
    QLineEdit * dayEdit = new QLineEdit(this);
    dayEdit->resize(60,30);
    dayEdit->move(300,580);

    QPushButton * confirmAdd = new QPushButton("添加活动",this);
    confirmAdd->move(240,700);

    connect(confirmAdd,&QPushButton::clicked,[=](){
        bool canAdd = true;
        Date tempDate;
        tempDate.weekday=weekdayChooseBox2->currentIndex()+1;
        for(int i=0;i<this->coursesNum;i++){
            if(this->courses[i].date.weekday==tempDate.weekday&&
                    beginTimeBox->currentText().toInt()>=courses[i].beginTime&&
                    beginTimeBox->currentText().toInt()<courses[i].endTime){
                canAdd=false;
                break;
            }
        }
        for(int i=0;i<this->outclassNum;i++){
            if(this->outclasses[i].frequency==EVERYDAY&&
                    this->outclasses[i].beginTime==beginTimeBox->currentText().toInt()){
                canAdd=false;
            }else if(this->outclasses[i].frequency==EVERYWEEK&&
                     this->outclasses[i].date.weekday==tempDate.weekday&&
                    beginTimeBox->currentText().toInt()==courses[i].beginTime){
                canAdd=false;
                break;
            }else if(this->outclasses[i].frequency==ONE_WEEK){
                tempDate.month=monthBox->currentText().toInt();
                tempDate.day=dayEdit->text().toInt();
                    if(this->outclasses[i].date.month==monthBox->currentText().toInt()&&
                        this->outclasses[i].date.day==dayEdit->text().toInt()&&
                            this->outclasses[i].beginTime==beginTimeBox->currentText().toInt()){
                    canAdd=false;
                    break;
                     }
            }
        }
        if(canAdd){

            record->writeRecord("学生"+username+"添加了星期"+weekdayChooseBox2->currentText()+"的活动"+outclassName->text());
            this->outclasses[outclassNum].setOutClassActivity(1,onofflineBox->currentIndex(),onofflineBox->currentIndex(),
                                                              frequencyBox->currentIndex(), tempDate , beginTimeBox->currentText().toInt(),
                                                              beginTimeLabel->text().toInt()+1, buildingName->text(),
                                                              outclassName->text());
            this->coursesNum++;
            QString address = resourcePath+"/outclass/"+username+".txt";
            FILE * fp = fopen(address.toLatin1().data(),"a+");
            fprintf(fp,"%d %d %d %d",this->outclasses[outclassNum].classfication,this->outclasses[outclassNum].outClassType,
                        this->outclasses[outclassNum].onOffLine,this->outclasses[outclassNum].frequency);
            if(this->outclasses[outclassNum].frequency==EVERYDAY)
                fprintf(fp," %d %s %s\n",this->outclasses[outclassNum].beginTime,
                        this->outclasses[outclassNum].building.toStdString().data(),
                        this->outclasses[outclassNum].name.toStdString().data());
            if(this->outclasses[outclassNum].frequency==EVERYWEEK)
                fprintf(fp," %d %d %s %s\n",this->outclasses[outclassNum].date.weekday,
                        this->outclasses[outclassNum].beginTime,
                        this->outclasses[outclassNum].building.toStdString().data(),
                        this->outclasses[outclassNum].name.toStdString().data());
            if(this->outclasses[outclassNum].frequency==ONE_WEEK)
                fprintf(fp," %d %d %d %d %s %s\n",this->outclasses[outclassNum].date.month,
                        this->outclasses[outclassNum].date.day,this->outclasses[outclassNum].date.weekday,
                        this->outclasses[outclassNum].beginTime,
                        this->outclasses[outclassNum].building.toStdString().data(),
                        this->outclasses[outclassNum].name.toStdString().data());

            fclose(fp);
            MyMessageBox deleteSuccess;
            deleteSuccess.setWindowTitle("提示");
            deleteSuccess.setText("添加成功！");
            deleteSuccess.show();
            deleteSuccess.exec();
            this->close();
        }
        else {
            record->writeRecord("学生添加活动失败");
            qDebug()<<"添加你摩洛哥炒饼";
            MyMessageBox deleteFailed;
            deleteFailed.setWindowTitle("提示");
            deleteFailed.setText("添加失败！\n时间与现有活动课程冲突！");
            deleteFailed.show();
            deleteFailed.exec();
        }
    });
}
