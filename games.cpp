#include "games.h"
#include "ui_games.h"
#include "wuziqi.h"
#include "dialog.h"
#include "star.h"
#include "saolei.h"
#include "snake.h"
#include "searchtools.h"
#include "interlogin.h"

GAMES::GAMES(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GAMES)
{
    ui->setupUi(this);
    QPalette p;
    QPixmap pix(":/imgs/Search_bg.jpg");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
}

GAMES::~GAMES()
{
    delete ui;
}

void GAMES::on_game1_clicked()
{
    wuziqi *w = new wuziqi();
    w->showNormal();
    close();
}

void GAMES::on_game2_clicked()
{
    Dialog *d = new Dialog();
    d->showNormal();
    close();
}

void GAMES::on_game1_2_clicked()
{
    SearchTools *s = new SearchTools();
    s->showNormal();
    close();
}

void GAMES::on_game3_clicked()
{
    Star *s = new Star();
    s->showNormal();
    close();
}

void GAMES::on_game4_clicked()
{
    saolei *sl = new saolei();
    sl->showNormal();
    close();
}

void GAMES::on_game5_clicked()
{
    Snake *s = new Snake();
    s->showNormal();
    close();
}

void GAMES::on_game1_3_clicked()
{
    interlogin *l = new interlogin();
    l->showNormal();
    close();
}
