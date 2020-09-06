#include "tianqi.h"
#include "ui_tianqi.h"
#include <QHostAddress>
#include <cstring>
#include <QDebug>
#include "QPainter"
#include <QTimer>
#include <qdatetime.h>
#include "searchtools.h"

tianqi::tianqi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tianqi)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    //timerUpdate();
    init();
    initsock();
}

void tianqi::timerUpdate(){
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->day->setText(str);
}

void tianqi::paintEvent(QPaintEvent *){
   QPainter p(this);
   QPixmap pix(":/3.jpg");
   QPixmap bei(":/7.jpg");
   QPixmap zhao(":/8.jpg");
    p.drawPixmap(0,0,761,666,pix);
    p.drawPixmap(550,150,250,440,bei);
    p.drawPixmap(10,590,81,61,zhao);
}


void tianqi::into(){//重置函数
    ui->num->setEnabled(true);

    m_num=ui->num->text();


}

void tianqi::init(){
    this->setFixedSize(760,659);//不让用户改变窗口大小
    this->setWindowTitle("彦祖天气预测");//设置标题栏

}

int tianqi::initsock(){
    fd.connectToHost(QHostAddress("122.228.95.136"),80);
    if(!fd.waitForConnected(2000)){//判断链接
        fd.disconnectFromHost();//链接失败，断开链接
        ui->lianjie->insertPlainText("链接失败");
        return -1;
    }

    ui->lianjie->insertPlainText("链接成功");
    connect(&fd,SIGNAL(readyRead()),this,SLOT(Recv()));
    return 1;
}

tianqi::~tianqi()
{
    delete ui;
}


void tianqi::on_start_clicked(){//开始查询
    into();
    ui->num->setEnabled(false);

    char buf[1024]={0};
    char y[50];
    char* ch;
    QByteArray ca = m_num.toLatin1();
    ch=ca.data();
    strcpy(y,ch);
   qDebug()<<y;
          sprintf(buf,"GET /%s HTTP/1.1\r\n",y);
          strcat(buf,"HOST: www.tianqi.com \r\n");
          strcat(buf,"Connection: close\r\n");
          strcat(buf,"\r\n");

          fd.write(buf,strlen(buf));
          qDebug()<<buf;
          //接受
          char Recv[4096*1000]={0};
          int l=0,res;
          while(1)
          {
              res=fd.read(Recv+l,1024);
              if(res<=0)break;
              l+=res;
          }
          qDebug()<<Recv;
          char* s1;
           s1=strstr(Recv,"设为默认");
           //s1=s1+8;
           ui->text->insertHtml(s1);
}

void tianqi::on_start_2_clicked()//重置函数
{
    into();
    ui->text->clear();
    ui->num->clear();
    ui->lianjie->clear();
    initsock();
}

void tianqi::on_back_clicked()//关闭
{
    SearchTools *s = new SearchTools();
    s->showNormal();
    close();
}

