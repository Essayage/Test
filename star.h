#ifndef STAR_H
#define STAR_H

#include <QDialog>
#include <time.h>
#include <QMouseEvent>


namespace Ui {
class Star;
}

class Star : public QDialog
{
    Q_OBJECT

public:
    explicit Star(QWidget *parent = 0);
    ~Star();

    void paintEvent(QPaintEvent *);//绘图事件
    /*void mousePressEvent(QMouseEvent *m);//鼠标事件
    void mouseReleaseEvent(QMouseEvent *m);*/
    void mouseMoveEvent(QMouseEvent *m);
    void closeEvent(QCloseEvent *);
    void init();
    void xiao(int b,int a);
    void move();
    void clear();
    void pan();
    int big(int x,int y);


private:
    Ui::Star *ui;

    int map[11][11];
    int next[4][2];
    int sum;
    int book[11][11];
};

#endif // STAR_H
