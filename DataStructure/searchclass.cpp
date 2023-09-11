#include "searchclass.h"
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include "mymessagebox.h"
#include <QDebug>
#include "activity.h"
#include <QTimer>

SearchClass::SearchClass(QWidget *parent) : QWidget(parent)
{

}

SearchClass::SearchClass(Activity*courses,int totalCourses)
{
    //this->setAttribute(Qt::WA_DeleteOnClose,true);

    this->setFixedSize(600,400);
    this->setFont(QFont("宋体",14));
    this->setWindowTitle("课程查询");

    QLabel * searchLabel = new QLabel("查询课程：",this);
    searchLabel->move(95,100);
    QLineEdit * lineCourseName = new QLineEdit(this);
    lineCourseName->move(220,100);
    lineCourseName->setPlaceholderText("请输入课程名");
    lineCourseName->setClearButtonEnabled(true);

    QPushButton * searchButton = new QPushButton("查询",this);
    searchButton->setGeometry(250,300,100,40);

    connect(searchButton,&QPushButton::clicked,[=](){
        QString resultText;
        QString tempweek[8]={"","星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
        MyMessageBox searchResultBox;
        searchResultBox.setMySize(600,400);
        searchResultBox.setWindowTitle("查询结果");

        QPushButton * argeeButton = searchResultBox.addButton("确定", QMessageBox::AcceptRole);
        int count=0;
        //qDebug()<<lineCourseName->text();
        for(int i=0;i<totalCourses;i++){
            if(courses[i].name==lineCourseName->text()){
                resultText += tempweek[courses[i].date.weekday] + QString::number(courses[i].beginTime) + ":00"
                        + " - " + QString::number(courses[i].endTime) + ":00" + "\n"
                        + (courses[i].onOffLine==ONLINE?"线上课程链接：":"线下课程地点：")
                        + courses[i].building + "\n";
                count++;
            }
        }
        if(count==0){
            resultText = "未查询到该课程！";
        }
        searchResultBox.setText(resultText);
        searchResultBox.show();
        searchResultBox.exec();
    });
}

SearchClass::~SearchClass()
{

}

