#include "wuziqi.h"
#include "ui_wuziqi.h"
#include <QPainter>
#include <QMessageBox>
#include "QMediaPlayer"
#include "games.h"

wuziqi::wuziqi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wuziqi)
{
    ui->setupUi(this);
//    QPalette p;
//    QPixmap pix(":/imgs/bg1.png");
//    p.setBrush(backgroundRole(),QBrush(pix));
//    setPalette(p);
    musicPlayer = new QMediaPlayer();
    musicPlayer->setMedia(QUrl::fromLocalFile("/home/tarena/Music/12.mp3"));
    musicPlayer->setVolume(50);

    init(1);
    first();
    n = 0;
}

wuziqi::~wuziqi()
{
    delete ui;
}

void wuziqi::paintEvent(QPaintEvent *)
{
    int i,j;
    QPixmap chessbg(":/imgs/bg.png");
    QPixmap bg(":/imgs/bg1.png");
    QPixmap pexit(":/imgs/exit.jpg");
    QPixmap pWhite(":/imgs/white.png");
    QPixmap pBlack(":/imgs/black.png");


    QPainter p(this);
    p.setPen(Qt::black);
    //p.drawPixmap(0,0,bg);
    p.drawPixmap(60,50,510,510,chessbg);
    for ( i = 0 ; i < 16; i ++)     //棋盘最左上格子坐标为 60，50
    {
        p.drawLine(60 ,50 + i * 34,570,50 + i * 34); //起始横坐标为60，末坐标为570 ，15个格子
    }
    for (i = 0; i < 16; i++)
    {
        p.drawLine(60 + i * 34,50,60 + i * 34,560); //起始纵坐标为50，末坐标为560， 15个格子
    }


    for (i = 2; i < 18; i++)  //棋盘数组大小为19 X 19 ，但用户界面棋盘大小为16 X 16，目的是在判断输赢时不越界
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
    p.drawPixmap(610,480,150,85,pexit);

}

void wuziqi::init(int t)
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
void wuziqi::first()
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

void wuziqi::mousePressEvent(QMouseEvent *m)
{
    n = n % 2;
    int i,j;
    if (m->x() < 60 || m->x() > 570 || m->y() < 50 || m->y() > 560)
        return;
    if(m->button() == 1)
    {
        j = (m->x() - 60 + 17) / 34 + 2;  //左偏移  上偏移
        i = (m->y() - 50 + 17) / 34 + 2;
        if (chessboard[i][j] != 0)
        {
            //n--; //因为进来时，n++了，所以要减一次
            return;
        }
        if (n == 0)
        {
            chessboard[i][j] = 1;
            n++;
        }
        else
        {
            chessboard[i][j] = 2;
            n++;
        }
    }
    ui->prompt->setText("轮到玩家 " + QString::number(n % 2  + 1)); //这里的n是上一玩家，所以要n + 1 提示下一玩家
    update();
    if(judgeWin() == 1)
    {
        if(QMessageBox::information(NULL,"PROMPT","玩家 " + QString::number((n +1) % 2  + 1) + " 赢了！是否继续？",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            init(0);
        }
        else
            close();
    }
}

int wuziqi::judgeWin()
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



void wuziqi::on_start_clicked()
{
    init(0);
    ui->prompt->setText("轮到玩家 1");
    n = 0;
    update();
}

void wuziqi::on_exit_clicked()
{
    GAMES *g = new GAMES();
    g->showNormal();
    musicPlayer->stop();
    close();
}

void wuziqi::on_playMusic_clicked()
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

void wuziqi::on_horizontalSlider_actionTriggered(int action)
{
    musicPlayer->setVolume(ui->horizontalSlider->value());

}

void wuziqi::on_pushButton_3_clicked()
{
    QMessageBox::information(NULL,"PROMPT","开发者正在吐血开发中....",QMessageBox::Ok);
}

void wuziqi::on_pushButton_2_clicked()
{
    QMessageBox::information(NULL,"PROMPT","鄙人QQ:272390256",QMessageBox::Ok);
}
