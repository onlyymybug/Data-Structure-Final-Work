#include "map.h"
#include "ui_map.h"
#include <QDebug>
#include<QPainter>
#include "record.h"
#include <QPixmap>;


VNODE* city;
int line1[10000]={0};
int line1num=0;
int total1=0;
int enabled_draw_map=1;
int enabled_N=0;
int lineN[20][1000]={0};//记录多段路径
int lineNnum[20]={0};//记录每段路径长度
int Nnum=0;//记录当前有多少段路径
int jie(int);
extern QString resourcePath;
FILE* fp/*=fopen((resourcePath+"/map/map.txt").toLatin1().data(),"r")*/;
int visit[10000]={0};
int visitNUM[NUM]={0};

map::map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::map)
{
    fp=fopen((resourcePath+"/map/map.txt").toLatin1().data(),"r");
    Record * record = new Record(this);
    ui->setupUi(this);
    this->setFixedSize(1600,1000);
    this->setFont(QFont("宋体",14));
    int total=0;
    while(!feof(fp)){
        char s[100];
        fscanf(fp,"%s",s);
        int a=order(s);
        if(a==4)//BYE
            break;
        else if(a==0)//CREATE
        {
            fscanf(fp,"%d",&total);
            city=(VNODE*)malloc(sizeof(VNODE)*total);
            total1=total;
        }
        else if(a==1)//VERTEX
        {
            vertex(city);
        }
        else if(a==2)//EDGE
        {
            edge(city);
        }
    }

    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        record->writeRecord("进行了导航");
        enabled_N=1;
        char shortNnamelist[10][20];
        strcpy(shortNnamelist[0],ui->lineEdit->text().toLocal8Bit().data());
        for(int i=1;i<this->locationsNum;i++){
            strcpy(shortNnamelist[i],this->passnames[i].toLocal8Bit().data());
        }
        shortestN(city,total,shortNnamelist,this->locationsNum);
        if(enabled_N)
        update();
        enabled_draw_map=1;
    });
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        record->writeRecord("进行了导航");
        enabled_N=0;
        QString startPlace=ui->lineEdit->text();
        QString endPlace=ui->lineEdit_3->text();
        char * start;
        QByteArray a=startPlace.toLocal8Bit();
        start=a.data();
        char * final;
        QByteArray b=endPlace.toLocal8Bit();
        final=b.data();
        shortest(city,total,start,final,1);
        if(!enabled_N)
        update();
        enabled_draw_map=1;
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        record->writeRecord("进行了导航");
        enabled_N=0;
        QString startPlace=ui->lineEdit->text();
        QString endPlace=this->finalName;
        char * start;
        QByteArray a=startPlace.toLocal8Bit();
        start=a.data();
        char * final;
        QByteArray b=endPlace.toLocal8Bit();
        final=b.data();
        shortest(city,total,start,final,1);
        if(!enabled_N)
        update();
        enabled_draw_map=1;
    });

}



map::~map()
{
    delete ui;
}
int map:: shortest(VNODE *city,int total,char * start,char * final,int outputable)
{
    Record * record = new Record(this);
    int numbera,numberb,aflag=0,bflag=0,a,b;
    /*char start[20];
    char final[20];
    fscanf(fp,"%s%s",start,final);*/
    for(int i=0;i<total;i++)
    {
        if(!aflag&&!strcmp(start,city[i].name))
        {
            a=i;
            numbera=i;
            aflag=1;
        }
        if(!bflag&&!strcmp(final,city[i].name))
        {
            b=i;
            numberb=i;
            bflag=1;
        }
        if(aflag&&bflag)
            break;
        if(i==total-1)
        {
            if(outputable){
            printf("Failed\n");
            ui->listWidget->addItem("输入错误地址，请重新输入");
            QString list2;
            list2.append("输入错误地址，请重新输入");
            record->writeRecord(list2);
            }
            return 0;
        }
    }
    if(outputable){
    printf("SHORTEST-PATH(%s=>%s): ",city[a].name,city[b].name);
    }
    QString  list;
    QString  acity=QString::fromLocal8Bit(city[a].name);
    QString  bcity=QString::fromLocal8Bit(city[b].name);
    list.append( "步行导航(").append(acity).append("=>").append(bcity).append("): ");
    int dis[10000];
    int front[10000];
    int data[10000][2];
    for(int i=0;i<10000;i++)
    {
        visit[i]=0;
        dis[i]=100000000;
        front[i]=-1;
        data[i][0]=0;
        data[i][1]=0;
    }
    dis[a]=0;
    NODE *r;
    r=(NODE*)malloc(sizeof(NODE));
    r=city[a].first;
    while(r->next!=NULL)
    {
        dis[r->num]=r->weight;
        front[r->num]=a;
        r=r->next;
    }
    dis[r->num]=r->weight;
    front[r->num]=a;
    visit[a]=1;
    for(int i=0;i<total-1;i++)
    {
        int min=100000000;
        int minnum=-1;
        for(int j=0;j<total;j++)
        {
            if(visit[j]==1&&city[j].first!=NULL)
            {
                NODE *q;
                q=(NODE*)malloc(sizeof(NODE));
                q=city[j].first;
                while(q->next!=NULL)
                {
                    if(q->weight+dis[j]<min&&visit[q->num]==0)
                    {
                        min=q->weight+dis[j];
                        minnum=q->num;
                    }
                    if(front[q->num]==-1)
                        front[q->num]=a;
                    q=q->next;
                }
                if(visit[q->num]==0)
                {
                    if(q->weight+dis[j]<min)
                    {
                        min=q->weight+dis[j];
                        minnum=q->num;
                    }
                    if(front[q->num]==-1)
                        front[q->num]=a;
                }
            }
        }
        visit[minnum]=1;
        dis[minnum]=min;
        data[minnum][0]=front[minnum];
        data[minnum][1]=minnum;
        NODE *p;
        p=(NODE*)malloc(sizeof(NODE));
        p=city[minnum].first;
        while(p->next!=NULL)
        {
            if(dis[p->num]!=100000000&&p->weight+dis[minnum]<dis[p->num])
            {
                dis[p->num]=p->weight+dis[minnum];
                front[p->num]=minnum;
            }
            else if(dis[p->num]==100000000)
            {
                dis[p->num]=p->weight+dis[minnum];
                front[p->num]=minnum;
            }
            p=p->next;
        }
        if(dis[p->num]!=100000000&&p->weight+min<dis[p->num])
        {
            dis[p->num]=p->weight+dis[minnum];
            front[p->num]=minnum;
        }
        else if(dis[p->num]==100000000)
        {
            dis[p->num]=p->weight+dis[minnum];
            front[p->num]=minnum;
        }
        a=minnum;
    }
    int i=1;
    int line[10000]={0};
    line[0]=b;
    line1[0]=b;
    lineN[Nnum][0]=b;
    while(data[b][0]!=numbera)
    {
        line[i]=data[b][0];
        line1[i]=data[b][0];
        lineN[Nnum][i]=data[b][0];
        b=data[b][0];
        i++;
    }
    line[i]=numbera;
    line1[i]=numbera;
    lineN[Nnum][i]=numbera;
    line1num=i;
    lineNnum[Nnum]=i;
    QString  ccity;
    for(int z=i;z>=0;z--)
    {
        printf(" %s",city[line[z]].name);
        ccity=QString::fromLocal8Bit(city[line[z]].name);
        if(z!=i)
            list.append( " ->").append(ccity);
        else
            list.append( " ").append(ccity);
    }
    if(outputable){
    ui->listWidget->addItem(list);
    printf("\n\tDistance %d\n",dis[numberb]);
    QString  list1;
    list1.append("距离 ").append(QString::number(dis[numberb]));
    ui->listWidget->addItem(list1);
    record->writeRecord(list);
    record->writeRecord(list1);
    }

    return dis[numberb];
}

int order(char *s)
{
    if(!strcmp(s,"CREATE"))
        return 0;
    if(!strcmp(s,"VERTEX"))
        return 1;
    if(!strcmp(s,"EDGE"))
        return 2;
}
void vertex(VNODE *city)
{
    int a,c,d;
    char b[20];
    fscanf(fp,"%d%d%d%s",&a,&c,&d,b);
    strcpy(city[a].name,b);
    city[a].first=NULL;
    city[a].x=c+10;
    city[a].y=d+30;
}
void edge(VNODE *city)
{
    int a,b,c;
    fscanf(fp,"%d%d%d",&a,&b,&c);
    if(city[a].first==NULL)
    {
        NODE* p;
        p=(NODE*)malloc(sizeof(NODE));
        strcpy(p->name,city[b].name);
        p->weight=(int)sqrt((city[a].x-city[b].x)*(city[a].x-city[b].x)+(city[a].y-city[b].y)*(city[a].y-city[b].y));
        p->next=NULL;
        p->num=b;
        city[a].first=p;
    }
    else
    {
        NODE* p;
        p=(NODE*)malloc(sizeof(NODE));
        strcpy(p->name,city[b].name);
        p->weight=(int)sqrt((city[a].x-city[b].x)*(city[a].x-city[b].x)+(city[a].y-city[b].y)*(city[a].y-city[b].y));
        p->num=b;
        p->next=city[a].first;
        city[a].first=p;
    }
    if(city[b].first==NULL)
    {
        NODE* p;
        p=(NODE*)malloc(sizeof(NODE));
        strcpy(p->name,city[a].name);
        p->weight=(int)sqrt((city[a].x-city[b].x)*(city[a].x-city[b].x)+(city[a].y-city[b].y)*(city[a].y-city[b].y));
        p->num=a;
        p->next=NULL;
        city[b].first=p;
    }
    else
    {
        NODE* p;
        p=(NODE*)malloc(sizeof(NODE));
        strcpy(p->name,city[a].name);
        p->weight=(int)sqrt((city[a].x-city[b].x)*(city[a].x-city[b].x)+(city[a].y-city[b].y)*(city[a].y-city[b].y));
        p->num=a;
        p->next=city[b].first;
        city[b].first=p;
    }
    return;
}
void map:: paintEvent(QPaintEvent * event)
{
    QPainter * painter1 = new QPainter(this);

        QPixmap pic = QPixmap((resourcePath+"/map/map.jpg").toLatin1().data());
        //pic = pic.scaled(this->width(),this->height());

        painter1->drawPixmap(10,30,660,930,pic);
    QPainter painter(this);
    QPen pen (QColor(255,0,0));
    pen.setWidth(5);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    if(!enabled_N){
    for(int z=line1num-1;z>=0;z--)
    {
        static int aflag1=0,bflag1=0,x1=0,y1=0,x2=0,y2=0;
        aflag1=0,bflag1=0;
        for(int i=0;i<total1;i++)
        {
            if(!aflag1&&!strcmp(city[i].name,city[line1[z+1]].name))
            {
                x1=city[i].x;
                y1=city[i].y;
                aflag1=1;
            }
            if(!bflag1&&!strcmp(city[i].name,city[line1[z]].name))
            {
                x2=city[i].x;
                y2=city[i].y;
                bflag1=1;
            }
            if(aflag1&&bflag1)
                break;
        }
        painter.drawLine(x1,y1,x2,y2);
    }
    line1num=0;
    for(int j=0;j<10000;j++){
        line1[j]=0;
    }
    }
    else
    {
        for(int k=0;k<=Nnum;k++)
        {
            for(int z=lineNnum[k]-1;z>=0;z--)
            {
                static int aflag1=0,bflag1=0,x1=0,y1=0,x2=0,y2=0;
                aflag1=0,bflag1=0;
                for(int i=0;i<total1;i++)
                {
                    if(!aflag1&&!strcmp(city[i].name,city[lineN[k][z+1]].name))
                    {
                        x1=city[i].x;
                        y1=city[i].y;
                        aflag1=1;
                    }
                    if(!bflag1&&!strcmp(city[i].name,city[lineN[k][z]].name))
                    {
                        x2=city[i].x;
                        y2=city[i].y;
                        bflag1=1;
                    }
                    if(aflag1&&bflag1)
                        break;
                }
                painter.drawLine(x1,y1,x2,y2);
            }
        }
//        update();
        line1num=0;
        for(int j=0;j<10000;j++){
            line1[j]=0;
        }
        for(int k=0;k<=Nnum;k++)
        {
            for(int p=0;p<=lineNnum[k];p++)
            {
                lineN[k][p]=0;
            }
            lineNnum[k]=0;
        }
        Nnum=0;
    }
    painter.end();
}
void map :: shortestN(VNODE * city,int total,char shortNnamelist[][20],int shortNtotal)
{
    //city为存储的信息，total为总点数，shortNnamelist用于存储路上经过的点的名字
    //shortNnamelist[0]为出发地与终止地，shortNtotal为需要从shortNnamelist中读取的名字个数
    //存储不同地点间距离
    int shortNdis[100][100]={0};
    //用shortest函数计算各点间距离，计算时不允许输出
    for(int i=0;i<shortNtotal;i++)
    {
        for(int j=0;j<i;j++)
        {
            shortNdis[i][j]=shortNdis[j][i]=shortest(city,total,shortNnamelist[i],shortNnamelist[j],0);
        }
    }
    int shortestDis=10000000;//用于记录最短距离
    int caseN=jie(shortNtotal-1);//记录共有几种情况，排除出发点的其他途径点的组合，最后将出发点与第一个点与最后一个点的距离加上就可以了,计算的是阶乘
    int order[shortNtotal-1]={0};//用caseN分析当前路径顺序，并记录
    int shortestorder[shortNtotal-1]={0};//用于记录当前已知的最短路径顺序
    //对不同种遍历情况依次通过 shortNdis数组 计算总长度，记录最短路径
    for(int i=0;i<caseN;i++)
    {
        enabled_N=1;
        int visit[shortNtotal]={0};
        int temp=i;
        for(int j=0;j<shortNtotal-1;j++)
        {
            int p=0;
            int caseNstate=temp/jie(shortNtotal-2-j);
            temp=temp%jie(shortNtotal-2-j);
            for(int k=caseNstate;k>=0;k--)
            {
                while(visit[p+1]!=0)
                {
                    p++;
                }
                p++;
            }
            order[j]=p;
            visit[p]=1;
        }
        int dis=0;//shortest(city,total,shortNnamelist[order[0]],shortNnamelist[order[1]],0);
        for(int j=1;j<shortNtotal-1;j++)
        {
            dis=dis+shortNdis[order[j-1]][order[j]];
            //dis+shortest(city,total,shortNnamelist[order[j-1]],shortNnamelist[order[j]],0);
        }
        dis=dis+shortNdis[0][order[0]]+shortNdis[0][order[shortNtotal-2]];
        //dis+shortest(city,total,shortNnamelist[0],shortNnamelist[order[0]],0)+shortest(city,total,shortNnamelist[order[shortNtotal-2]],shortNnamelist[0],0);
        if(dis<shortestDis)
        {
            shortestDis=dis;
            for(int j=0;j<shortNtotal-1;j++)
            {
                shortestorder[j]=order[j];
            }
        }
    }//计算出shortestorder数组，记录最短遍历顺序
    shortest(city,total,shortNnamelist[0],shortNnamelist[shortestorder[0]],1);
    Nnum++;
    for(int j=1;j<shortNtotal-1;j++)
    {
        shortest(city,total,shortNnamelist[shortestorder[j-1]],shortNnamelist[shortestorder[j]],1);
        Nnum++;
    }
    shortest(city,total,shortNnamelist[shortestorder[shortNtotal-2]],shortNnamelist[0],1);
}
int jie(int n)
{
    int ans=1;
    for(int i=2;i<=n;i++)
    {
        ans *= i;
    }
    return ans;
}

void map::setFinalName(QString finalName){
    this->finalName=finalName;
}

void map::setLocationsNum(int n){
    this->locationsNum=n;
}

void map::setPassnames(QString*passnames){
    //this->passnames=passnames;
}

void map::showButton1(){
    this->ui->pushButton->show();
    this->ui->pushButton_2->hide();
    this->ui->pushButton_3->hide();
    this->ui->lineEdit_3->show();
    this->ui->label_3->show();
    this->ui->listWidget->clear();
}

void map::showButton2(){
    this->ui->pushButton->hide();
    this->ui->pushButton_2->show();
    this->ui->pushButton_3->hide();
    this->ui->lineEdit_3->hide();
    this->ui->label_3->hide();
    this->ui->listWidget->clear();
}

void map::showButton3(){
    this->ui->pushButton->hide();
    this->ui->pushButton_2->hide();
    this->ui->pushButton_3->show();
    this->ui->lineEdit_3->hide();
    this->ui->label_3->hide();
    this->ui->listWidget->clear();
}

void map::clearLineEdit(){
    this->ui->lineEdit->clear();
    this->ui->lineEdit_3->clear();
}
