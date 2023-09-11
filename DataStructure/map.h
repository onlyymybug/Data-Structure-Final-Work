#ifndef MAP_H
#define MAP_H

#include <QMainWindow>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <QCloseEvent>
#define NUM 200
typedef struct Node{
    char name[21];
    int weight,num;
    struct Node* next;
}NODE;
typedef struct vnode{
    char name[21];
    int x,y;
    struct Node* first;
}VNODE;
int order(char*);
void vertex(VNODE*);
void edge(VNODE*);
int jie(int);
//void map::shortest(VNODE*,int,char *,char *);
extern FILE* fp;
extern int visit[10000];

namespace Ui {
class map;
}

class map : public QMainWindow
{
    Q_OBJECT

public:
    QString finalName;
    int locationsNum;
    QString passnames[20];

    explicit map(QWidget *parent = 0);

    ~map();
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent*);
    void setFinalName(QString finalName);
    void setPassnames(QString*passnames);
    void setLocationsNum(int n);
    void showButton1();
    void showButton2();
    void showButton3();
    void clearLineEdit();


private slots:
    int shortest(VNODE*,int,char *,char *,int);
    void shortestN(VNODE *,int,char[][20],int);



private:
    Ui::map *ui;
};

#endif // MAP_H
