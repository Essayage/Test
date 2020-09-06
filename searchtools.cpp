#include "searchtools.h"
#include "ui_searchtools.h"
#include "games.h"
#include "login.h"
#include "x_login.h"
#include "tianqi.h"
#include <QPainter>
#include "cha.h"

SearchTools::SearchTools(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchTools)
{
    ui->setupUi(this);
    QPalette p;
    QPixmap pix(":/imgs/Search_bg.jpg");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
    //QPainter p2(this);
    //p2.drawPixmap(0,0,840,500,pix);

}

void SearchTools::paintEvent(QPaintEvent *)
{
//    QPainter p2(this);
//    QPixmap S_1(":/imgs/S_1.jpg");
//    QPixmap S_2(":/imgs/S_2.jpeg");
//    QPixmap S_3(":/imgs/S_3.jpg");
//    QPixmap S_4(":/imgs/S_4.jpg");
//    p2.drawPixmap(40,350,360,250,S_1);
//    p2.drawPixmap(420,350,360,250,S_2);
//    p2.drawPixmap(800,350,360,250,S_3);
//    p2.drawPixmap(1180,350,360,250,S_4);

}

SearchTools::~SearchTools()
{
    delete ui;
}

void SearchTools::on_pushButton_5_clicked()
{
    GAMES *g = new GAMES();
    g->showNormal();
    close();
}

void SearchTools::on_pushButton_3_clicked()
{
    login *l = new login();
    l->showNormal();
    close();
}

void SearchTools::on_pushButton_4_clicked()
{
    x_login *x = new x_login();
    x->showNormal();
    close();
}

void SearchTools::on_pushButton_2_clicked()
{
      tianqi *t = new tianqi();
      t->showNormal();
      close();
}

void SearchTools::on_pushButton_clicked()
{
    Cha* c=new Cha("120.92.201.157",80);
    c->showNormal();
    close();
}
