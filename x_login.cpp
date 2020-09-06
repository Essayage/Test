#include "x_login.h"
#include "ui_x_login.h"
#include "x_number.h"
#include <QDesktopWidget>
#include <QPainter>
#include "searchtools.h"
x_login::x_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::x_login)
{
    this->setWindowTitle("吴彦组星座查询");//设置标题栏
    ui->setupUi(this);
    //是窗口居中
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2-60, (desktop->height() - this->height())/2-60);
    QPalette p;
    QPixmap pix(":/3.jpg");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
}

x_login::~x_login()
{
    delete ui;
}

void x_login::on_log_clicked()
{
    if(ui->ip->text()==""||ui->port->text()==""||ui->num->text()==""){
        return;
    }
    x_number* c = new x_number(ui->ip->text(),
                       ui->port->text().toInt(),
                       ui->num->text());

    c->showNormal();
    close();
}

void x_login::on_clo_clicked()
{
    SearchTools *s = new SearchTools();
    s->showNormal();
    close();
}

