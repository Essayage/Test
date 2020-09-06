#include "number.h"
#include "login.h"
#include "ui_number.h"
#include <QHostAddress>
#include <cstring>
#include <QDebug>
#include <QTimer>
#include <qdatetime.h>
#include "searchtools.h"

number::number(QString ip, int port, QString num, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::number)
{
    ui->setupUi(this);
    m_ip = ip;
    m_port = port;
    m_num = num;
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    //timerUpdate();
    init();
    initsock();
}

void number::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd-hh:mm:ss dddd");
    ui->time->setText(str);
                        }

void number::init(){
    //this->setFixedSize(440,298);//不让用户改变窗口大小
    this->setWindowTitle("彦祖号码吉凶预测");//设置标题栏
    play.setMedia(QUrl::fromLocalFile("./1.mp3"));
    play.setVolume(200);
    /*QPixmap pix(":/image/bj.jpg");
    QPalette p;
    p.setBrush(backgroundRole(),QBrush(pix));
    this->setPalette(p);
    p.setBrush(QPalette::Base,QBrush(Qt::NoBrush));
*/


}

int number::initsock(){
    fd.connectToHost(QHostAddress(m_ip),m_port);
    if(!fd.waitForConnected(2000)){//判断链接
        fd.disconnectFromHost();//链接失败，断开链接
        ui->text->insertPlainText("链接失败\n");
        return -1;
    }

    ui->text->insertPlainText(m_num);
    ui->text->insertPlainText("链接成功\n");
    connect(&fd,SIGNAL(readyRead()),this,SLOT(Recv()));
    /*char* n = m_num.toLocal8Bit().data();
    fd.write(n,strlen(n));*/

    return 1;
}

number::~number()
{
    delete ui;
}


void number::on_start_clicked()
{
    char buf[1024]={0};
    char y[13],y2[13];
    char* ch;
    QByteArray ba = m_num.toLatin1();
    ch=ba.data();
    strcpy(y,ch);
    for(int i=0;i<6;i++)y2[i]=y[i];
    y2[6]='\0';

          //发送
          sprintf(buf,"GET /%s/%s.html HTTP/1.1\r\n",y2,y);
          strcat(buf,"HOST: mobile.9om.com\r\n");
/*
          sprintf(buf,"GET /fetion.asp?mp=%s HTTP/1.1\r\n",y);
          strcat(buf,"HOST: sjxiong.supfree.net\r\n");*/
          strcat(buf,"Connection: close\r\n");
          strcat(buf,"\r\n");
          fd.write(buf,strlen(buf));
          //qDebug()<<buf;
          //接受
          char Recv[4096*100]={0};
          int l=0,res;
          while(1)
          {
              res=fd.read(Recv+l,1024);
              if(res<=0)break;
              l+=res;
          }
          char y3[4096*1000],*y4,*y5;
          y4=strstr(Recv,"五行数理");

          //qDebug()<<y4;
          //strcpy(y3,y4);
          //qDebug()<<y3;
          //y5=strstr(y3,"New");
          //(*y5)='\0';

          ui->text->insertHtml(y4);
          //qDebug()<<y;

      /*  qDebug()<<Recv;
          QString str;
          str = QString(QLatin1String(Recv));
          ui->text->insertPlainText(QObject::trUtf8(str.toLocal8Bit().data()));
          qDebug()<<QObject::trUtf8(str.toLocal8Bit().data());
          qDebug()<<str;*/
}

void number::paintEvent(QPaintEvent *){
    QPixmap pix;
    pix.load(":/img/l1.png");
    ui->l1->setPixmap(pix);

    pix.load(":/img/l2.png");
    ui->l2->setPixmap(pix);

    pix.load(":/img/l3.png");
    ui->l3->setPixmap(pix);

    pix.load(":/img/l5.png");
    ui->l5->setPixmap(pix);

}

void number::on_start_2_clicked()
{
    SearchTools *s = new SearchTools();
    s->showNormal();
    close();
}

void number::on_pushButton_clicked()
{
    login* l = new login();
    l->showNormal();
    close();
}
