#include "deletetemp.h"
#include "activity.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "mymessagebox.h"
#include "record.h"
#include <QDebug>

QStringList temporarysNames;
QComboBox * temporarysBox;
QComboBox * weekdayChooseBox3;
extern QString resourcePath;

DeleteTemp::DeleteTemp(QWidget *parent) : QWidget(parent)
{

}

DeleteTemp::DeleteTemp(Activity*temporarys,int temporarysNum,QString username)
{

    Record * record = new Record(this);
    this->temporarys=temporarys;
    this->temporarysNum=temporarysNum;
    this->username=username;
    this->setWindowTitle("删除事务");
    this->setFont(QFont("宋体",12));
    this->resize(600,400);

    QLabel * weekdayChooseLabel = new QLabel("删除星期      的事务",this);
    weekdayChooseLabel->move(100,100);
    //QString tempWeekdays[8] = {"","一","二","三","四","五","六","日"};
    weekdayChooseBox3 = new QComboBox(this);
    weekdayChooseBox3->move(200,100);
    weekdayChooseBox3->addItems({"一","二","三","四","五","六","日"});

    QLabel * NameChooseLabel = new QLabel("事务名称",this);
    NameChooseLabel->move(100,200);
    temporarysBox = new QComboBox(this);
    temporarysBox->resize(300,30);
    confirmTemp();
    temporarysBox->move(200,200);
    connect(weekdayChooseBox3,SIGNAL(currentIndexChanged(int)),this,SLOT(confirmTemp()));
    QPushButton * deleteButton = new QPushButton("删除",this);
    deleteButton->move(250,300);

    connect(deleteButton,&QPushButton::clicked,this,&DeleteTemp::deleteOneTemp);
    connect(deleteButton,&QPushButton::clicked,[=](){
        record->writeRecord("学生"+username+"删除了星期"+weekdayChooseBox3->currentText()+"的临时事务"+temporarysBox->currentText());
        MyMessageBox deleteSuccess;
        deleteSuccess.setWindowTitle("提示");
        deleteSuccess.setText("删除成功！");
        deleteSuccess.show();
        deleteSuccess.exec();
        this->close();
    });
}

void DeleteTemp::confirmTemp(){
    qDebug()<<"老子更新了";
    temporarysBox->clear();
    temporarysNames.clear();
    for(int i=0;i<this->temporarysNum;i++){
        if(weekdayChooseBox3->currentIndex()+1==temporarys[i].date.weekday){
            temporarysNames<<this->temporarys[i].name;
        }
    }
    temporarysBox->addItems(temporarysNames);
}

void DeleteTemp::deleteOneTemp(){
    for(int i=0;i<this->temporarysNum;i++){
        if(this->temporarys[i].date.weekday==weekdayChooseBox3->currentIndex()+1
                &&this->temporarys[i].name==temporarysBox->currentText()){
            for(int j=i;j<this->temporarysNum;j++){
                this->temporarys[j].date=this->temporarys[j+1].date;
                this->temporarys[j].beginTime=this->temporarys[j+1].beginTime;
                this->temporarys[j].building=this->temporarys[j+1].building;
                this->temporarys[j].name=this->temporarys[j+1].name;
            }
            this->temporarysNum--;
            break;
        }
    }
    QString address = resourcePath+"/temporary/"+this->username+".txt";
    FILE * fp = fopen(address.toLatin1().data(),"w");
    for(int i=0;i<this->temporarysNum;i++){
        fprintf(fp,"%d %d %s %s\n",this->temporarys[i].date.weekday,this->temporarys[i].beginTime,
                this->temporarys[i].name.toUtf8().data(),this->temporarys[i].building.toUtf8().data());
    }
    fclose(fp);
}
