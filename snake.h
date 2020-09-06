#ifndef SNAKE_H
#define SNAKE_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
#include <qdebug.h>
#include <QMessageBox>

struct Sn{
    int x;
    int y;
    Sn* next;
};
namespace Ui {
class Snake;
}

class Snake : public QDialog
{
    Q_OBJECT

public:
    explicit Snake(QWidget *parent = 0);
    ~Snake();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);
    void suifood();
    void pan();
    void init();//初始化
private slots:
    void on_dong_clicked();//按钮
    void move1();//定时器
    void on_ting_clicked();

private:
    Ui::Snake *ui;
    Sn head;
    int score;
    int direc[2];//控制横纵变化
    int direction;//蛇方向
    Sn food;
    int sn_body;
    int i;
    QTimer timer;
};

#endif // SNAKE_H
