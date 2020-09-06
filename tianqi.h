#ifndef TIANQI_H
#define TIANQI_H
#include <QDialog>
#include <QTcpSocket>
#pragma execution_character_set("utf-8")

namespace Ui {
class tianqi;
}

class tianqi : public QDialog
{
    Q_OBJECT

public:
    explicit tianqi(QWidget *parent = 0);
    void init();
    void into();
    int initsock();

    void paintEvent(QPaintEvent *);
    ~tianqi();


private slots:
    void timerUpdate();

    void on_start_clicked();

    void on_start_2_clicked();

    void on_back_clicked();

private:
    Ui::tianqi *ui;
    QString m_num;

    QTcpSocket fd;//通信
};

#endif // TIANQI_H
