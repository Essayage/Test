#include "x_number.h"
#include "ui_x_number.h"
#include <QHostAddress>
#include <cstring>
#include <QMessageBox>
#include "x_login.h"
#include "searchtools.h"
x_number::x_number(QString ip, int port, QString num, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::x_number)
{
    ui->setupUi(this);
    m_ip = ip;
    m_port = port;
    m_num = num;
    QPalette p;
    QPixmap pix(":/img/l1.png");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
    init();
    initsock();
}

void x_number::init(){
    this->setFixedSize(800,520);//不让用户改变窗口大小
    this->setWindowTitle("吴彦组星座查询");//设置标题栏
    strcpy(name[0],"aries");//白羊
    strcpy(name[1],"taurus");//金牛
    strcpy(name[2],"gemini");//双子
    strcpy(name[3],"cancer");//巨蟹
    strcpy(name[4],"leo");//狮子
    strcpy(name[5],"virgo");//处女
    strcpy(name[6],"libra");//天秤
    strcpy(name[7],"scorpio");//天蝎
    strcpy(name[8],"sagittarius");//射手
    strcpy(name[9],"capricornus");//摩羯
    strcpy(name[10],"aquarius");//水瓶
    strcpy(name[11],"pisces");//双鱼
}

int x_number::initsock(){
    fd.connectToHost(QHostAddress(m_ip),m_port);
    if(!fd.waitForConnected(4000)){//判断链接
        fd.disconnectFromHost();//链接失败，断开链接
        ui->text->insertPlainText("链接失败\n");
        return -1;
    }
    ui->text->insertPlainText("链接成功\n");
    //connect(&fd,SIGNAL(readyRead()),this,SLOT(Recv()));
    return 1;
}

x_number::~x_number()
{
    delete ui;
}


void x_number::on_start_clicked()
{

        char buf[1024]={0};
        char y[12];
        char* ch;
        int flag=12;
        QByteArray ba = m_num.toLatin1();
        ch=ba.data();
        strcpy(y,ch);
        for(int i=0;i<12;i++){
            if(strcmp(y,"baiyang")==0) flag=0;
            else if(strcmp(y,"jinniu")==0) flag=1;
            else if(strcmp(y,"shuangzi")==0) flag=2;
            else if(strcmp(y,"juxie")==0) flag=3;
            else if(strcmp(y,"shizi")==0) flag=4;
            else if(strcmp(y,"chunv")==0) flag=5;
            else if(strcmp(y,"tiancheng")==0) flag=6;
            else if(strcmp(y,"tianxie")==0) flag=7;
            else if(strcmp(y,"sheshou")==0) flag=8;
            else if(strcmp(y,"mojie")==0) flag=9;
            else if(strcmp(y,"shuiping")==0) flag=10;
            else if(strcmp(y,"shuangyu")==0) flag=11;
        }
        if(flag!=12){
            //发送
            sprintf(buf,"GET /astro/%s/ HTTP/1.1\r\n",name[flag]);
            strcat(buf,"HOST: www.xzw.com\r\n");
            strcat(buf,"Connection: close\r\n");
            strcat(buf,"\r\n");
            fd.write(buf,strlen(buf));
            //接受
            char Recv[4096*1000]={0};
            int l=0,res;
            while(1)
            {
                res=fd.read(Recv+l,1024);
                if(res<=0)break;
                l+=res;
            }
            char *p;
            p=strstr(Recv,"</i></span><h1><strong class=\"f_yh\">");
            ui->text->insertHtml(p);
        }
        else{
            if(QMessageBox::information(NULL,"提示","没有这个星座\n是否继续查询？",
                                        QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
                x_login *l = new x_login();
                l->showNormal();
                close();
            }else close();
        }
}


void x_number::on_pushButton_clicked()
{
    x_login *l = new x_login();
    l->showNormal();
    close();
}

void x_number::on_pushButton_2_clicked()
{
    SearchTools *s = new SearchTools();
    s->showNormal();
    close();
}
