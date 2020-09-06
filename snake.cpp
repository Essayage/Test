#include "snake.h"
#include "ui_snake.h"
#include <QPainter>
#include <QDebug>
#include "games.h"
Snake::Snake(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Snake)
{
    qsrand(time(0));
    init();
    suifood();
    ui->setupUi(this);
}

void Snake::init(){
    i=0;
    score=0;
    sn_body=20;//蛇身的宽度
    //direc[i],i==0控制x横,i==1控制y纵加减

    int a,b;
    a=(rand()%24+3)*sn_body;
    b=(rand()%24+3)*sn_body;
    direction=rand()%4;//随机一个方向
    switch(direction){//上、下、左、右
    case 0:{
        direc[1]=-1;//上
        direc[0]=0;
        head.x=a;//横
        head.y=b;//纵
        Sn* n1 =new Sn;
        head.next=n1;
        n1->x=head.x+sn_body*direc[0];
        n1->y=head.y+sn_body*direc[1];
        n1->next=NULL;
    }
        break;
    case 1:{
        direc[1]=1;//下
        direc[0]=0;
        head.x=a;//横
        head.y=b;//纵
        Sn* n1 =new Sn;
        head.next=n1;
        n1->x=head.x+sn_body*direc[0];
        n1->y=head.y+sn_body*direc[1];
        n1->next=NULL;}
        break;
    case 2:{
        direc[0]=-1;//左
        direc[1]=0;
        head.x=a;//横
        head.y=b;//纵
        Sn* n1 =new Sn;
        head.next=n1;
        n1->x=head.x+sn_body*direc[0];
        n1->y=head.y+sn_body*direc[1];
        n1->next=NULL;}
        break;
    case 3:{
        direc[0]=1;//右
        direc[1]=0;
        head.x=a;//横
        head.y=b;//纵
        Sn* n1 =new Sn;
        head.next=n1;
        n1->x=head.x+sn_body*direc[0];
        n1->y=head.y+sn_body*direc[1];
        n1->next=NULL;}
        break;
    }
    connect(&timer,SIGNAL(timeout()),this,SLOT(move1()));//当点击开始按钮启动计时器
}
void Snake::suifood(){

    Sn *q=&head;
    while(1){
        food.x=rand()%30*sn_body;
        food.y=rand()%30*sn_body;
        food.next=NULL;
        if(food.x==q->x&&food.y==q->y){
            food.x=rand()%30*sn_body;
            food.y=rand()%30*sn_body;
            food.next=NULL;
            q=&head;
        }
        if(q->next==NULL){
            break;
        }
        q=q->next;
    }
}

void Snake::pan(){
    int x1,y1;
    int flag=0;
    x1=head.x;
    y1=head.y;
    if(head.x==food.x&&head.y==food.y){
        Sn *q = new Sn;
        q->next=head.next;
        head.next=q;
        i++;
        ui->fen->setText(QString::number(i));
        suifood();
    }
    Sn *p = &head;
    if(i>1){
        while(p->next!=NULL){
            p=p->next;
            if(p->x==head.x&&p->y==head.y){
                flag=1;
                break;
            }
        }}
    if(x1<0||x1>600||y1<0||y1>600-sn_body||flag){
        if(QMessageBox::warning(NULL,"提示","是否重玩",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            disconnect(&timer,SIGNAL(timeout()),this,SLOT(move1()));
            init();
            suifood();
        }else{
            GAMES *g = new GAMES();
            disconnect(&timer,SIGNAL(timeout()),this,SLOT(move1()));
            g->showNormal();
            close();
        }
    }
}


void Snake::move1(){//使蛇移动

    Sn *p = &head;
    int a1,a2,b1,b2;
    a1=head.x+sn_body*direc[0];
    a2=head.y+sn_body*direc[1];


    while(1){
        b1=p->x;
        b2=p->y;
        p->x=a1;
        p->y=a2;
        if(p->next!=NULL){
            p=p->next;
            a1=b1;
            a2=b2;
        }
        else break;
    }
    pan();
    update();
}

Snake::~Snake()
{
    delete ui;
}

void Snake::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setBrush(QBrush(Qt::yellow));
    Sn* sp = &head;
    p.drawRect(food.x,food.y,sn_body,sn_body);
    p.drawLine(620,0,620,600);
    while(sp){
        p.drawRect(sp->x,sp->y,sn_body,sn_body);
        sp=sp->next;
    }
}

void Snake::on_dong_clicked()
{//开始
    timer.start(200);
}

void Snake::keyPressEvent(QKeyEvent *e){
    //int key = e->key();
    //qDebug()<<key;//获取键盘事件
    if((e->key()== Qt::Key_W)&&(direction==2||direction==3)){//代表移动方向上
        direc[0]=0;
        direc[1]=-1;
        direction=0;
    }else if((e->key()== Qt::Key_S)&&(direction==2||direction==3)){//代表移动方向下
        direc[0]=0;
        direc[1]=1;
        direction=1;
    }else if((e->key()==Qt::Key_A)&&(direction==1||direction==0)){//代表移动方向左
        direc[1]=0;
        direc[0]=-1;
        direction=2;
    }else if((e->key()==Qt::Key_D)&&(direction==1||direction==0)){//代表移动方向右
        direc[1]=0;
        direc[0]=1;
        direction=3;
    }
}

void Snake::on_ting_clicked()
{
    GAMES *g = new GAMES();
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(move1()));
    g->showNormal();
    close();
}
