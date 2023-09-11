#include "login.h"
#include "ui_login.h"
#include <QPushButton>
#include "studentoperation.h"
#include <QDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <stdio.h>
#include "teacheroperation.h"
#include <QApplication>

#define MAX_USER_NUM 20
#define MAX_INFORMATION_LEN 100

char usernames[MAX_USER_NUM][MAX_INFORMATION_LEN];
char passwords[MAX_USER_NUM][MAX_INFORMATION_LEN];
int userNum=0;
QString resourcePath;


bool match(char*username,char*password){
    for(int i=0;i<MAX_USER_NUM;i++);
    return false;
}

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    this->setWindowTitle("学生日程管理系统-登录");
    resourcePath = QApplication::applicationDirPath()+"/../resource";

//    FILE * usernameResource = fopen("F:/QtFile/DataStructure/resource/login/username.txt","r");
//    FILE * passwordResouece = fopen("F:/QtFile/DataStructure/resource/login/password.txt","r");

    FILE * usernameResource = fopen((resourcePath+"/login/username.txt").toLatin1().data(),"r");
    FILE * passwordResouece = fopen((resourcePath+"/login/password.txt").toLatin1().data(),"r");
    for(int i=0;feof(usernameResource)==0;i++){
        fscanf(usernameResource,"%s",usernames[i]);
        fscanf(passwordResouece,"%s",passwords[i]);
        userNum++;
    }
    userNum--;
    fclose(usernameResource);
    fclose(passwordResouece);

    qDebug()<<userNum;
    for(int i=0;i<userNum;i++){
        qDebug()<<usernames[i];
        qDebug()<<passwords[i];
    }

    ui->setupUi(this);
    this->setFixedSize(600,400);
    this->setFont(QFont("宋体",14));

    QLabel * loginUserName = new QLabel("用户名",this);
    loginUserName->move(120,100);
    QLineEdit * lineUsername = new QLineEdit(this);
    lineUsername->move(220,100);
    lineUsername->setPlaceholderText("请输入用户名");
    lineUsername->setClearButtonEnabled(true);

    QLabel * loginPassword = new QLabel("密  码",this);
    loginPassword->move(120,180);
    QLineEdit * linePassword = new QLineEdit(this);
    linePassword->move(220,180);
    linePassword->setPlaceholderText("请输入密码");
    linePassword->setClearButtonEnabled(true);
    linePassword->setEchoMode(QLineEdit::Password);

    QPushButton * login = new QPushButton("登录",this);

    login->setGeometry(230,300,100,40);




    connect(login,&QPushButton::clicked,[=](){
        QString tempUsername = lineUsername->text();
        QString tempPassword = linePassword->text();
        //StudentOperation * studentOperation = new StudentOperation(tempUsername);
        QString strU,strP;
        //qDebug()<<tempUsername<<tempPassword;
        bool b=false;
        if(tempUsername=="admin"&&tempPassword=="admin"){
            TeacherOperation * teacherOperation = new TeacherOperation();
            teacherOperation->show();
            this->close();
        }
        else{
            StudentOperation * studentOperation = new StudentOperation(tempUsername);
            for(int i=0;i<userNum;i++){
                //qDebug()<<tempUsername<<tempPassword;
                strU = QString(QLatin1String(usernames[i]));
                if(strU==tempUsername){
                   qDebug()<<"1";
                   strP = QString(QLatin1String(passwords[i]));
                   if(strP==tempPassword){
                       b=true;
                       qDebug()<<"2";
                   }
                   else{
                       qDebug()<<"3";
                       qDebug()<<tempPassword<<passwords[i];
                   }

                   break;
                }

            }
            if(b){
                studentOperation->setStudentUsername(tempUsername);
                qDebug()<<studentOperation->studentUsername;
                studentOperation->resize(1600,1000);
                studentOperation->show();
                this->close();
            }
            else
                QMessageBox::critical(this,"错误","用户名或密码错误");
        }
    });




}

Login::~Login()
{
    delete ui;
}

