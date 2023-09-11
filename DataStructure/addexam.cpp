#include "addexam.h"
#include "exam.h"
#include "record.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "mymessagebox.h"

extern QString resourcePath;

AddExam::AddExam(QWidget *parent) : QWidget(parent)
{

}

AddExam::AddExam(examInformation *exams,int examNum){
    Record * record = new Record(this);
    this->exams=exams;
    this->examNum=examNum;
    this->setWindowTitle("添加考试");
    this->setFont(QFont("宋体",12));
    this->resize(600,400);

    QLabel * courseNameChooseLabel = new QLabel("课程名称",this);
    courseNameChooseLabel->move(100,80);
    QLineEdit * courseName = new QLineEdit(this);
    courseName->move(200,80);

    QLabel * examBuildingLabel = new QLabel("考试地点",this);
    examBuildingLabel->move(100,160);
    QLineEdit * buildingName = new QLineEdit(this);
    buildingName->move(200,160);

    QLabel * examTimeLabel = new QLabel("考试时间 6 月      日",this);
    examTimeLabel->move(100,240);
    QComboBox * examDayBox = new QComboBox(this);
    examDayBox->move(260,240);
    examDayBox->addItems({"12","13","14","15","16","17","18"});

    QPushButton * confirmAddButton = new QPushButton("确认添加",this);
    confirmAddButton->move(250,330);

    connect(confirmAddButton,&QPushButton::clicked,[=](){
        record->writeRecord("管理员添加了课程"+courseName->text()+"的考试");
        this->exams[examNum].name=courseName->text();
        this->exams[examNum].building=buildingName->text();
        this->exams[examNum].month=6;
        this->exams[examNum].day=examDayBox->currentText().toInt();

        FILE * fp = fopen((resourcePath+"/exam/exam.txt").toLatin1().data(),"w+");
        for(int i=0;i<examNum+1;i++)
        fprintf(fp,"%s %s %d %d\n",this->exams[i].name.toStdString().data(),
                this->exams[i].building.toStdString().data(),
                this->exams[i].month,this->exams[i].day);
        fclose(fp);
        this->examNum++;
        MyMessageBox addSuccess;
        addSuccess.setWindowTitle("提示");
        addSuccess.setText("添加成功！");
        addSuccess.show();
        addSuccess.exec();
        this->close();
    });
}
