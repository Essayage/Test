#include "login.h"
#include "ui_login.h"
#include "number.h"
#include "searchtools.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("彦祖号码吉凶预测登陆");//设置标题栏
    play.setMedia(QUrl::fromLocalFile(":/1.mp3"));
    play.setVolume(200);
    ui->ip->setText("47.88.61.15");
    ui->port->setText("80");
    QPalette p;
    QPixmap pix(":/img/bj.png");
    p.setBrush(backgroundRole(),QBrush(pix));
    setPalette(p);
}

login::~login()
{
    delete ui;
}

void login::on_log_clicked()
{
    if(ui->ip->text()==""||ui->port->text()==""||ui->num->text()==""){
        return;
    }
    number* c = new number(ui->ip->text(),
                       ui->port->text().toInt(),
                       ui->num->text());
    c->showNormal();
    close();
}

void login::on_clo_clicked()
{
    SearchTools *s = new SearchTools();
    s->showNormal();
    close();
}

void login::paintEvent(QPaintEvent *){
    QPixmap pix;
}
