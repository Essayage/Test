#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include<QKeyEvent>
#include "games.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    init();
    QPalette p;
       QPixmap pix(":/2048imgs/sw.JPG");
       p.setBrush(backgroundRole(),QBrush(pix));
       setPalette(p);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::keyPressEvent(QKeyEvent *k){
    switch(k->key())
    {
    case Qt::Key_W:on_pushButton_clicked();
        break;
        case Qt::Key_S:on_pushButton_5_clicked();
        break;
         case Qt::Key_A:on_pushButton_2_clicked();
        break;
        case Qt::Key_D:on_pushButton_4_clicked();
        break;
    }
}
void Dialog::on_pushButton_6_clicked()
{
    GAMES *g = new GAMES();
    g->showNormal();
    close();
}

void Dialog::paintEvent(QPaintEvent *){
   QPixmap pix;
   pix.load(":/2048imgs/"+QString::number(map[0][0])+".png");
   ui->show1->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[0][1])+".png");
   ui->show2->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[0][2])+".png");
   ui->show3->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[0][3])+".png");
   ui->show4->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[1][0])+".png");
   ui->show5->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[1][1])+".png");
   ui->show6->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[1][2])+".png");
   ui->show7->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[1][3])+".png");
   ui->show8->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[2][0])+".png");
   ui->show9->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[2][1])+".png");
   ui->show10->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[2][2])+".png");
   ui->show11->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[2][3])+".png");
   ui->show12->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[3][0])+".png");
   ui->show13->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[3][1])+".png");
   ui->show14->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[3][2])+".png");
   ui->show15->setPixmap(pix);
   pix.load(":/2048imgs/"+QString::number(map[3][3])+".png");
   ui->show16->setPixmap(pix);

   ui->sum->setText(QString::number(sum));
}


void Dialog::init(){
    for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                map[i][j]=0;
            }
        }
        sum = 0;
        sui();
        sui();
}

void Dialog::sui(){
    int size = 0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(map[i][j]==0) size++;
            }
        }
        while(size){
            int x = rand()%4;
            int y = rand()%4;
            if(map[x][y]==0){
                if(rand()%20 ==4){
                    map[x][y]=4;
                }else{
                    map[x][y]=2;
                }
                sum+=map[x][y];
                break;
            }
        }
}

void Dialog::on_pushButton_clicked()
{
    int x = 0,y = 0,k = 0;
            for(k=0;k<3;k++){
                for(x=1;x<4;x++){
                    for(y=0;y<4;y++){
                        if(map[x-1][y]==0&&map[x][y]){
                            map[x-1][y]=map[x][y];
                            map[x][y]=0;
                        }
                        else if(map[x][y]&&map[x-1][y]==map[x][y]){
                            map[x-1][y]*=2;
                            map[x][y]=0;
                        }
                    }
                 }
             }
     sui();

}

int Dialog::pan(){
    int x = 0,y = 0,k = 0;
       int num[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
       for(x=0;x<4;x++){
           for(y=0;y<4;y++){
               if(map[y][x]==0){
                   return 1;
               }
               for(k=0;k<4;k++){
                   int nx = x+num[k][0];
                   int ny = y+num[k][1];
                   if(nx<0||nx>3||ny<0||ny>3){
                       continue;
                   }
                   else if(map[nx][ny]==map[x][y]){
                       return 1;
                   }

               }
           }
       }
       return -1;
}


void Dialog::on_pushButton_2_clicked()
{
    int x = 0,y = 0,k = 0;
        for(k=0;k<3;k++){
            for(y=1;y<4;y++){
                for(x=0;x<4;x++){
                    if(map[x][y-1]==0&&map[x][y]){
                        map[x][y-1]=map[x][y];
                        map[x][y]=0;
                    }
                    else if(map[x][y]&&map[x][y-1]==map[x][y]){
                        map[x][y-1]*=2;
                        map[x][y]=0;
                    }
                }
             }
         }
        sui();



}

void Dialog::on_pushButton_4_clicked()
{
    int x = 0,y = 0,k = 0;
        for(k=0;k<3;k++){
            for(y=2;y>=0;y--){
                for(x=0;x<4;x++){
                    if(map[x][y+1]==0&&map[x][y]){
                        map[x][y+1]=map[x][y];
                        map[x][y]=0;
                    }
                    else if(map[x][y]&&map[x][y+1]==map[x][y]){
                        map[x][y+1]*=2;
                        map[x][y]=0;
                    }
                }
             }
         }
        sui();



}

void Dialog::on_pushButton_5_clicked()
{
    int x = 0,y = 0,k = 0;
    for(k=0;k<3;k++){
        for(x=0;x<3;x++){
            for(y=0;y<4;y++){
                if(map[x+1][y] ==0 && map[x][y]){
                    map[x+1][y]=map[x][y];
                    map[x][y]=0;
                }
                else if(map[x][y]&&map[x+1][y]==map[x][y]){
                    map[x+1][y]*=2;
                    map[x][y]=0;
                }
            }
         }
     }

        sui();


}

void Dialog::on_pushButton_3_clicked()
{
    init();
}
