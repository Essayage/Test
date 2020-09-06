#ifndef SAOLEI_H
#define SAOLEI_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class saolei;
}

class saolei : public QDialog
{
    Q_OBJECT

public:
    explicit saolei(QWidget *parent = 0);
    ~saolei();
    void paintEvent(QPaintEvent *);
    void di(int ,int );
    void mousePressEvent(QMouseEvent *m);
    void count();
    void pan();
    void into();


private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void dong();

private:
    Ui::saolei *ui;
    int map[15][15];//真实地图
    int map1[15][15];//虚拟地图
    bool b;
    int x;
    int time1;
    QTimer timer;
    int times;

};

#endif // SAOLEI_H
