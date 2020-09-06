#include "saolei.h"
#include "ui_saolei.h"
#include "QPainter"
#include"QMouseEvent"
#include <QMessageBox>
#include <ctime>
#include "games.h"

int map[15][15],map1[15][15];
saolei::saolei(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saolei)
{

    ui->setupUi(this);
    x=0;
    times = 0;
    QPalette p;
    QPixmap pix(":/Mine/binz3.jpeg");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
    b = false;
   into();
   connect(&timer,SIGNAL(timeout()),this,SLOT(dong()));
  pan();


}

saolei::~saolei()
{
    delete ui;
}

void saolei::dong()
{
    times++;
    ui->time->setText("时间："+QString::number(times));
}

void saolei::into(){
    for (int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++){
            map1[i][j]=0;
            map[i][j]=0;
        }
    }
}


void saolei::paintEvent(QPaintEvent *){
    QPainter p(this);
    QPixmap pix(":/Mine/empty.png");
    QPixmap bomber(":/Mine/bomber.png");
    QPixmap know(":/Mine/know.png");
    QPixmap Nknow(":/Mine/Nknow.png");
    QPixmap Nbomber(":/Mine/Nbomber.png");
    QPixmap tix0(":/Mine/0.png");
    QPixmap tix1(":/Mine/1.png");
    QPixmap tix2(":/Mine/2.png");
    QPixmap tix3(":/Mine/3.png");
    QPixmap tix4(":/Mine/4.png");
    QPixmap tix5(":/Mine/5.png");
    QPixmap tix6(":/Mine/6.png");
    QPixmap tix7(":/Mine/7.png");
    QPixmap tix8(":/Mine/8.png");


    for (int i=0;i<16;i++){
        p.drawLine(20,20+i*40,620,20+i*40);
        p.drawLine(20+i*40,20,20+i*40,620);
    }
    for (int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++){
            if (map1[i][j]==0)
                p.drawPixmap(20+i*40,20+j*40,40,40,pix);
            if (map1[i][j]==110)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix0);
            if (map1[i][j]==1)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix1);
            if (map1[i][j]==2)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix2);
            if (map1[i][j]==3)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix3);
            if (map1[i][j]==4)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix4);
            if (map1[i][j]==5)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix5);
            if (map1[i][j]==6)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix6);
            if (map1[i][j]==7)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix7);
            if (map1[i][j]==8)
                p.drawPixmap(20+i*40,20+j*40,40,40,tix8);
            if (map1[i][j]==-1)
                p.drawPixmap(20+i*40,20+j*40,40,40,bomber);
            if (map1[i][j]==120)
                p.drawPixmap(20+i*40,20+j*40,40,40,know);
        }
   }
}




void saolei::di(int x,int y){//递归展开
    int a[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    int i=0;
    for(i=0;i<8;i++){
        int nx=x+a[i][0];
        int ny=y+a[i][1];
        if(nx<0||nx>14||ny<0||ny>14){
            continue;
        }else if(map1[nx][ny]!=0){
            continue;
        }else if(map[nx][ny]==0){
            map1[nx][ny]=110;
            di(nx,ny);
        }else{
            map1[nx][ny]=map[nx][ny];
        }
    }
}
void saolei::mousePressEvent(QMouseEvent *m){
    if(m->x()<20||m->x()>620||m->y()<20||m->y()>620) return;
        if(b==false) return;
    int x=(m->x()-20)/40;
    int y=(m->y()-20)/40;
    if (m->button()==1){
       //已经点击过
       if(map1[x][y]!=0) return;
       else if(map[x][y]==-1){//踩到雷
           //将真实地图中的雷全部虚拟地图
           int i=0,j=0;
           for(i=0;i<15;i++){
               for(j=0;j<15;j++){
                   if(map[i][j]==-1){
                       map1[i][j]=map[i][j];
                   }
               }
           }
           update();
           if (QMessageBox::information(NULL,"ti shi","LOSE",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
           {
              into();
              b=false;
              ui->num->setEnabled(true);
           }
           else
           close();


       }else if(map[x][y]==0){//空白-递归展开
           map1[x][y]=110;
           di(x,y);
       }else{//数字
           map1[x][y]=map[x][y];
       }
      // update();
    }
    if (m->button()==2){
        if (map1[x][y]==0)
        map1[x][y]=120;
       else
            map1[x][y]=0;
    }
    update();
    pan();
}

void saolei::pan(void){
    int n=ui->num->text().toInt();
    int i=0,j=0,k=0;
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(map1[i][j]==0||map1[i][j]==120){
                k++;
            }
        }
    }
    if(k==n){
        timer.stop();
        if (QMessageBox::information(NULL,"ti shi","WIN",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            times = 0;
           into();
           b=false;
             ui->num->setEnabled(true);
        }
        else
        close();
    }
}


void saolei::count(){//计算周围数字
  int a[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
  int x=0,y=0,k=0;
  for(x=0;x<15;x++){
    for(y=0;y<15;y++){
      if(map[x][y]==-1){
        for(k=0;k<8;k++){
          int nx=x+a[k][0];
          int ny=y+a[k][1];
          if(nx<0||nx>14||ny<0||ny>14){
            continue;
          }else if(map[nx][ny]==-1){
            continue;
          }else{
            map[nx][ny]++;
          }
        }
        }
    }
  }
}

void saolei::on_pushButton_3_clicked()
{
    GAMES *g = new GAMES();
    g->showNormal();
    timer.stop();
    close();
}

void saolei::on_pushButton_2_clicked()
{
    into();
    update();
    b=false;
      ui->num->setEnabled(true);
      times = 0;
      timer.stop();
}

void saolei::on_pushButton_clicked()
{
    time1 = time(0);
    x=1;
    int size=ui->num->text().toInt();
    int i = 0;
     for(i=0;i<size;){
         int x=rand()%15;
         int y=rand()%15;
         if(map[x][y]==0){
             map[x][y]=-1;
             i++;
         }
     }
     count();
     ui->num->setEnabled(false);
     b=true;
     timer.start(1000);
     update();

}
