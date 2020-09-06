#include "interlogin.h"
#include "ui_interlogin.h"
#include "interwuziqi.h"
#include "games.h"

interlogin::interlogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::interlogin)
{
    ui->setupUi(this);
    QPalette p;
    QPixmap pix(":/imgs/Search_bg.jpg");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
}

interlogin::~interlogin()
{
    delete ui;
}

void interlogin::on_login_clicked()
{

    interwuziqi *w = new interwuziqi(ui->ip->text(),
                           ui->port->text().toInt(),
                           ui->name->text());
    w->showNormal();
    close();

}

void interlogin::on_cancel_clicked()
{
    GAMES *G = new GAMES();
    G->showNormal();
    close();
}
