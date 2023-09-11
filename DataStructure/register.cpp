#include "register.h"
#include "QLabel"
#include "QPushButton"
#include <QLineEdit>
#include "mymessagebox.h"

extern QString resourcePath;

Register::Register(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("学生日程管理系统-注册");
    this->setFixedSize(600,400);
    this->setFont(QFont("宋体",14));
    FILE * usernameResource = fopen((resourcePath+"/login/username.txt").toLatin1().data(),"r");
    FILE * passwordResouece = fopen((resourcePath+"/login/password.txt").toLatin1().data(),"r");
//    FILE * usernameResource = fopen("F:/QtFile/DataStructure/resource/login/username.txt","a+");
//    FILE * passwordResouece = fopen("F:/QtFile/DataStructure/resource/login/password.txt","a+");

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

    QPushButton * confirmRegist = new QPushButton("注册",this);
    confirmRegist->setGeometry(250,300,100,40);


    connect(confirmRegist,&QPushButton::clicked,[=](){
        QString tempoutclassad=resourcePath+ "/outClass/"+lineUsername->text()+".txt";
        QString temptempad=resourcePath+ "/temporary/"+lineUsername->text()+".txt";
        FILE * fp1 = fopen(tempoutclassad.toStdString().data(),"w");
        FILE * fp2 = fopen(temptempad.toStdString().data(),"w");
        fprintf(usernameResource,"%s\n",lineUsername->text().toStdString().data());
        fprintf(passwordResouece,"%s\n",linePassword->text().toStdString().data());
        MyMessageBox deleteSuccess;
        deleteSuccess.setWindowTitle("提示");
        deleteSuccess.setText("注册成功！");
        deleteSuccess.show();
        deleteSuccess.exec();
        this->close();
    });

}
