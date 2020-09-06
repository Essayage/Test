#include "cha.h"
#include "ui_cha.h"
#include <QHostAddress>
#include <cstring>
#include <QDebug>
#include "searchtools.h"
Cha::Cha(QString ip, int port,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cha)
{
    ui->setupUi(this);
    mip=ip;
    mport=port;
    init();
    initsock();
}

Cha::~Cha()
{
    delete ui;
}

void Cha::init(){
this->setWindowTitle("吴彦祖版爱词霸");
}

int Cha::initsock(){
    fd.connectToHost(QHostAddress(mip),mport);
    if(!fd.waitForConnected(10000)){
        fd.disconnectFromHost();
        ui->text->insertPlainText("链接失败\n");
        return -1;
    }
    ui->text->insertPlainText(m_d);
    ui->text->insertPlainText("链接成功\n");
    return 1;
}

void Cha::on_chaxun_clicked()
{
    if(ui->d->text()=="") return;
    ui->text->setText("");
    initsock();
    QString y = "GET /"+ui->d->text()+" HTTP/1.1\r\n";
    char buf[1024]={0};
    strcpy(buf,y.toLocal8Bit().data());
    strcat(buf,"HOST: www.iciba.com\r\n");
    strcat(buf,"Connection: close\r\n");
    strcat(buf,"\r\n");
    fd.write(buf,strlen(buf));
    char Recv[4096*100]={0};
    int l=0,res=0;
    while(1){
        res=fd.read(Recv+l,1024);
        if(res<=0)
            break;
        l+=res;
    }
   if(strlen(Recv)<=0){
       ui->text->insertPlainText("获取失败请重试");
       return;
   }
   char* s1=strstr(Recv,"base-list switch_part")+33;
   if(s1==NULL){
       ui->text->insertPlainText("获取失败请重试");
       return;
   }
   char* s2=strstr(s1,"</ul>");
   if(s2==NULL){
       ui->text->insertPlainText("获取失败请重试");
       return;
   }
   *s2='\0';
   ui->text->insertHtml(s1);
   fd.close();
}

void Cha::on_pushButton_clicked()
{
    SearchTools *s = new SearchTools;
    s->showNormal();
    close();
}
