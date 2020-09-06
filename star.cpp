#include "star.h"
#include "ui_star.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include "games.h"

Star::Star(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Star)
{
    ui->setupUi(this);

    srand(time(0));

    init();
    QPalette p;
    QPixmap pix(":/消灭星星/bg.png");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
}

Star::~Star()
{
    delete ui;
}

void Star::init()
{
    int t;
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
        {
            t=rand()%5+1;

            map[i][j]=t;
        }
    }
    sum=0;
}

void Star::xiao(int a,int b)
{
    int flag=0;
    int tx,ty;
    int next[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
    book[a][b]=1;
    //printf("%d,%d\n",a,b);
    for(int k=0;k<4;k++)
    {
        tx=a+next[k][0];
        ty=b+next[k][1];

        if(tx>10||ty>10||tx<1||ty<1)continue;

        if(book[tx][ty]==0&&map[a][b]==map[tx][ty])
        {
            xiao(tx,ty);
            sum+=map[tx][ty];
            map[tx][ty]=0;
            flag=1;
        }
    }
    if(flag)
    {
        sum+=map[a][b];
        map[a][b]=0;
    }

}

int Star::big(int x,int y)
{
    return x>y?x:y;
}

void Star::move()
{
    int tx,lx,flag;

    for(int i=9;i>=1;i--)
        {
            for(int j=1;j<=10;j++)
            {
                if(map[j][i]!=0)
                {
                    flag=0;
                    lx=i;
                    tx=i+1;
                    while(map[j][tx]==0&&tx<=10)
                    {
                        lx=tx;
                        tx++;
                        flag=1;
                    }
                    if(lx==10)
                    {
                        map[j][lx]=map[j][i];
                        map[j][i]=0;
                    }
                    else
                    {
                        if(flag)
                        {
                            map[j][lx]=map[j][i];
                            map[j][i]=0;
                        }
                    }
                }
            }
    }

    int flag2;
    int time=0;
    for(int i=1;i<=10;i++)
    {
        flag2=0;
        for(int j=1;j<=10;j++)
        {
            if(map[i][j]!=0)
            {
                    flag2=1;
                    break;
            }
        }
        if(flag2==0)
        {
            time++;
        }
        else
        {
            if(time!=0)
            {
                for(int q=time;q>=1;q--)
                {
                    for(int k=1;k<=10;k++)
                    {
                        map[i-q][k]=map[i][k];
                        map[i][k]=0;
                    }
                }
                i=i-time;
                time=0;
            }
        }

    }
}

void Star::paintEvent(QPaintEvent *){
    QPixmap pix;
    QPainter p(this);
    ui->sum->setText(QString::number(sum));
    for(int i=10;i>=1;i--){
        for(int j=1;j<=10;j++){
            if(map[i][j]==0) continue;
            pix.load(":/消灭星星/"+QString::number(map[i][j])+".png");
            p.drawPixmap((i*40)-40,j*40+60,40,40,pix);
        }
    }
    p.end();
}

void Star::mouseMoveEvent(QMouseEvent *m){
    int x=(m->x())/40+1;//横坐标
    int y=(m->y()-100)/40+1;//纵坐标
    // printf("%d,%d\n",x,y);
    //map[x][y]=0;
    xiao(x,y);
    move();
    pan();
    clear();
    update();
}

void Star::clear()
{
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
        {
            book[i][j]=0;
        }
    }
}

void Star::pan()
{
    int next[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
    int tx,ty;
    int flag;

    flag=0;
    for(int i=1;i<=10;i++)
    {
        for(int j=1;j<=10;j++)
        {
            if(map[i][j]!=0)
            {

                for(int k=0;k<4;k++)
                {
                    tx=i+next[k][0];
                    ty=j+next[k][1];

                    if(tx>10||ty>10||tx<1||ty<1)continue;

                    if(map[i][j]==map[tx][ty])
                        flag=1;
                }
            }
        }
    }
    if(flag==0)
    {
        QMessageBox::warning(NULL,"提示",
           "游戏结束",QMessageBox::Ok);
        close();
    }
}

void Star::closeEvent(QCloseEvent *)
{
    GAMES *g = new GAMES;
    g->showNormal();
    close();
}
