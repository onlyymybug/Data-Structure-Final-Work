#include "deleteoutclass.h"
#include "activity.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "mymessagebox.h"
#include "record.h"
#include <QDebug>

QStringList outclassesNames;
QComboBox * outclassesBox;
QComboBox * weekdayChooseBox2;
extern QString resourcePath;

DeleteOutclass::DeleteOutclass(QWidget *parent){}

DeleteOutclass::DeleteOutclass(Activity*outclasses,int outclassesNum,QString username)
{

    Record * record = new Record(this);
    this->outclasses=outclasses;
    this->outclassesNum=outclassesNum;
    this->username=username;
    this->setWindowTitle("删除课程");
    this->setFont(QFont("宋体",12));
    this->resize(600,400);

    QLabel * weekdayChooseLabel = new QLabel("删除星期      的活动",this);
    weekdayChooseLabel->move(100,100);
    //QString tempWeekdays[8] = {"","一","二","三","四","五","六","日"};
    weekdayChooseBox2 = new QComboBox(this);
    weekdayChooseBox2->move(200,100);
    weekdayChooseBox2->addItems({"一","二","三","四","五","六","日"});

    QLabel * courseNameChooseLabel = new QLabel("活动名称",this);
    courseNameChooseLabel->move(100,200);
    outclassesBox = new QComboBox(this);
    outclassesBox->resize(300,30);
    confirmOutclasses();
    outclassesBox->move(200,200);
    connect(weekdayChooseBox2,SIGNAL(currentIndexChanged(int)),this,SLOT(confirmOutclasses()));
    QPushButton * deleteButton = new QPushButton("删除",this);
    deleteButton->move(250,300);

    connect(deleteButton,&QPushButton::clicked,this,&DeleteOutclass::deleteOneOutclass);
    connect(deleteButton,&QPushButton::clicked,[=](){
        record->writeRecord("学生"+username+"删除了星期"+weekdayChooseBox2->currentText()+"的活动"+outclassesBox->currentText());
        MyMessageBox deleteSuccess;
        deleteSuccess.setWindowTitle("提示");
        deleteSuccess.setText("删除成功！");
        deleteSuccess.show();
        deleteSuccess.exec();
        this->close();
    });
}

void DeleteOutclass::confirmOutclasses(){
    //qDebug()<<"老子更新了";
    outclassesBox->clear();
    outclassesNames.clear();
    for(int i=0;i<this->outclassesNum;i++){
        if(outclasses[i].frequency==EVERYDAY||
                weekdayChooseBox2->currentIndex()+1==outclasses[i].date.weekday){
            outclassesNames<<this->outclasses[i].name;
            qDebug()<<weekdayChooseBox2->currentIndex()+1<<outclasses[i].date.weekday;
        }
    }
    outclassesBox->addItems(outclassesNames);
}

void DeleteOutclass::deleteOneOutclass(){
    for(int i=0;i<this->outclassesNum;i++){
        if(this->outclasses[i].date.weekday==weekdayChooseBox2->currentIndex()+1
                &&this->outclasses[i].name==outclassesBox->currentText()){
            for(int j=i;j<this->outclassesNum;j++){
                this->outclasses[j].classfication=this->outclasses[j+1].classfication;
                this->outclasses[i].outClassType=this->outclasses[j+1].outClassType;
                this->outclasses[j].onOffLine=this->outclasses[j+1].onOffLine;
                this->outclasses[j].frequency=this->outclasses[j+1].frequency;
                this->outclasses[j].date=this->outclasses[j+1].date;
                this->outclasses[j].beginTime=this->outclasses[j+1].beginTime;
                this->outclasses[j].endTime=this->outclasses[j+1].endTime;
                this->outclasses[j].building=this->outclasses[j+1].building;
                this->outclasses[j].name=this->outclasses[j+1].name;
            }
            this->outclassesNum--;
            qDebug()<<this->outclassesNum<<"after";
            break;
        }
    }
    QString address = resourcePath+"/outClass/"+this->username+".txt";
    FILE * fp = fopen(address.toLatin1().data(),"w");
    for(int i=0;i<this->outclassesNum;i++){
        fprintf(fp,"%d %d %d %d",this->outclasses[i].classfication,this->outclasses[i].outClassType,
                    this->outclasses[i].onOffLine,this->outclasses[i].frequency);
        if(this->outclasses[i].frequency==EVERYDAY)
            fprintf(fp," %d %s %s\n",this->outclasses[i].beginTime,
                    this->outclasses[i].building.toStdString().data(),
                    this->outclasses[i].name.toStdString().data());
        if(this->outclasses[i].frequency==EVERYWEEK)
            fprintf(fp," %d %d %s %s\n",this->outclasses[i].date.weekday,
                    this->outclasses[i].beginTime,
                    this->outclasses[i].building.toStdString().data(),
                    this->outclasses[i].name.toStdString().data());
        if(this->outclasses[i].frequency==ONE_WEEK)
            fprintf(fp," %d %d %d %d %s %s\n",this->outclasses[i].date.month,
                    this->outclasses[i].date.day,this->outclasses[i].date.weekday,
                    this->outclasses[i].beginTime,
                    this->outclasses[i].building.toStdString().data(),
                    this->outclasses[i].name.toStdString().data());
    }
    fclose(fp);
}
