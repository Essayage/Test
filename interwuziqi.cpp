#include "interwuziqi.h"
#include "ui_interwuziqi.h"
#include <QPainter>
#include <QMessageBox>
#include "QMediaPlayer"
#include <cstring>
#include <QHostAddress>
#include <QDebug>

interwuziqi::interwuziqi(QString ip,int port,QString name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::interwuziqi)
{
    ui->setupUi(this);

    musicPlayer = new QMediaPlayer();
    musicPlayer->setMedia(QUrl::fromLocalFile("/home/tarena/Music/12.mp3"));
    musicPlayer->setVolume(50);

    cIp = ip;
    cPort = port;
    cName = name;
    ui->prompt_2->setText(cName);
    init(1);
    initsock();
    first();
}

interwuziqi::~interwuziqi()
{
    delete ui;
}

int interwuziqi::initsock()
{
    cFd.connectToHost(QHostAddress(cIp),cPort);
    if(!cFd.waitForConnected(2000))
    {
        cFd.disconnectFromHost();//连接失败，断开连接
        ui->internetText->setText("未连接网络");
        return -1;
    }
    ui->internetText->setText("已连接网络");
    connect(&cFd,SIGNAL(readyRead()),this,SLOT(Receive()));
}

int interwuziqi::Receive()  //服务器发送消息格式 Name:Position:x:y:Name
{
    int x,y;
    QString buf = cFd.readAll();
    QStringList ls = buf.split(":");
    if(ls.size() == 5)
    {
        ui->prompt->setText("");
        ui->prompt->setText("轮到:" + ls.at(4));
        x = ls.at(2).toInt();
        y = ls.at(3).toInt();
        dong(x,y,ls.at(0));
        return 1;

    }
    else
    {
        init(0);
        update();
        ui->prompt->setText("");
        ui->prompt->setText("轮到:" + buf);
    }
    return -1;

}

int interwuziqi::dong(int x,int y,QString Name)
{
    int i,j;
    j = (x - 60 + 17) / 34 + 2;  //左偏移  上偏移
    i = (y - 50 + 17) / 34 + 2;
    if (Name == cName)
    {
        chessboard[i][j] = 1;
    }
    else
    {
        chessboard[i][j] = 2;
    }
    update();
    if(judgeWin() == 1)
    {
        if(QMessageBox::information(NULL,"PROMPT","玩家 " + Name + " 赢了！是否继续？",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
                {
                    cFd.write("bye",3);
                    close();
                }
                else
                {
                    cFd.write("bye",3);
                    close();
                }
    }
}

void interwuziqi::mousePressEvent(QMouseEvent *m)
{
    int i,j;
    if (m->x() < 60 || m->x() > 570 || m->y() < 50 || m->y() > 560)
            return;
    j = (m->x() - 60 + 17) / 34 + 2;  //左偏移  上偏移
    i = (m->y() - 50 + 17) / 34 + 2;
    if (chessboard[i][j] != 0)
    {
        return;
    }
    QString who = ui->prompt->text();
    QStringList ls = who.split(":");
    qDebug()<<ls.at(1);
    if (ls.at(1) == cName)
    {
        QString send;
        send = cName + ":Position:" + QString::number(m->x()) + ":" + QString::number(m->y()) + ":";
        char* n = send.toLocal8Bit().data();
        cFd.write(n,strlen(n));
    }

}

void interwuziqi::paintEvent(QPaintEvent *)
{
    int i,j;
    QPixmap chessbg1(":/imgs/bg.png");
    //QPixmap chessbg2(":/imgs/chessbox.png");
    //QPixmap pexit(":/imgs/exit.jpg");
    QPixmap pWhite(":/imgs/white.png");
    QPixmap pBlack(":/imgs/black.png");


    QPainter p(this);
    p.setPen(Qt::black);
    p.drawPixmap(60,50,510,510,chessbg1);
    //p.drawPixmap(24,16,574,574,chessbg2);
    for ( i = 0 ; i < 16; i ++)     //棋盘最左上格子坐标为 60，50
    {
        p.drawLine(60 ,50 + i * 34,570,50 + i * 34); //起始横坐标为60，末坐标为570 ，15个格子
    }
    for (i = 0; i < 16; i++)
    {
        p.drawLine(60 + i * 34,50,60 + i * 34,560); //起始纵坐标为50，末坐标为560， 15个格子
    }


    for (i = 2; i < 18; i++)  //棋盘数组大小为20 X 20 ，但用户界面棋盘大小为16 X 16，目的是在判断输赢时不越界
    {
        for (j = 2; j < 18; j++)
            if(chessboard[i][j] == 1)   //1为黑棋
            {
                p.drawPixmap(60 - 17 + (j - 2) * 34, 50 - 17 + (i - 2) * 34, pBlack); //横纵坐标减格子的一半长度
            }
            else if (chessboard[i][j] == 2)
            {
                p.drawPixmap(60 - 17 + (j - 2) * 34, 50 - 17 + (i - 2) * 34, pWhite);
            }
    }
    //p.drawPixmap(610,480,150,85,pexit);

}

void interwuziqi::init(int t)
{
    int i,j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20;j++)
            if( t >= 0 && t < 3)
            {
                chessboard[i][j] = t;
            }
            else
            {
                return;
            }
    }
}
void interwuziqi::first()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        chessboard[7][3 + i] = 2;
        chessboard[9][3 + i] = 2;
    }
    for(i = 0; i < 7; i++)
    {
        chessboard[7 + i][3] = 2;
        chessboard[7 + i][16 - i] = 2;
        chessboard[7 + i][10 + i] = 2;
    }
}

int interwuziqi::judgeWin()
{
    int i,j,k,o;
    int t[5];
    int a1[4][2] = {{0,1},{0,2},{0,-1},{0,-2}};
    int a2[4][2] = {{2,0},{1,0},{-1,0},{-2,0}};
    int a3[4][2] = {{-2,-2},{-1,-1},{1,1},{2,2}};
    int a4[4][2] = {{-2,2},{-1,1},{1,-1},{2,-2}};
    for (i = 2; i < 18; i++)  //棋盘数组大小为19 X 19 ，但用户界面棋盘大小为15 X 15，目的是在判断输赢时不越界
    {
        for (j = 2; j < 18; j++)
        {
            t[0] = t[1] = t[2] = t[3] = t[4] = 0;
            if (chessboard[i][j] != 0)
            {
                for (k = 0; k  < 4; k++)
                {
                    if (chessboard[i][j] == chessboard[i + a1[k][0]][j + a1[k][1]])
                    {
                        t[1]++;
                    }
                    if (chessboard[i][j] == chessboard[i + a2[k][0]][j + a2[k][1]])
                    {
                        t[2]++;
                    }
                    if (chessboard[i][j] == chessboard[i + a3[k][0]][j + a3[k][1]])
                    {
                        t[3]++;
                    }
                    if (chessboard[i][j] == chessboard[i + a4[k][0]][j + a4[k][1]])
                    {
                        t[4]++;
                    }
                    for (o = 0; o < 5; o++)
                    {
                        if (t[o] == 4)
                        {
                            return 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;

}



void interwuziqi::on_start_clicked()
{
    if(ui->start->text() == "已准备")
        return;
    QString NAME;
    NAME = "@" + cName;
    char *c = NAME.toLocal8Bit().data();
    cFd.write(c,strlen(c));
    ui->start->setText("已准备");
    update();
}

void interwuziqi::on_exit_clicked()
{
    cFd.write("bye",3);
    close();
}

void interwuziqi::on_playMusic_clicked()
{
    if(ui->playMusic->text() == "播放音乐")
    {
        musicPlayer->play();
        ui->playMusic->setText("暂停");
    }
    else
    {
        musicPlayer->stop();
        ui->playMusic->setText("播放音乐");
    }

}

void interwuziqi::on_horizontalSlider_actionTriggered(int action)
{
    musicPlayer->setVolume(ui->horizontalSlider->value());

}

void interwuziqi::on_pushButton_3_clicked()
{
    QMessageBox::information(NULL,"PROMPT","开发者正在吐血开发中....",QMessageBox::Ok);
}

void interwuziqi::on_pushButton_2_clicked()
{
    QMessageBox::information(NULL,"PROMPT","鄙人QQ:272390256",QMessageBox::Ok);
}

