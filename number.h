#ifndef NUMBER_H
#define NUMBER_H

#include <QDialog>
#include <QTcpSocket>
#include <QMediaPlayer>

#pragma execution_character_set("utf-8")

namespace Ui {
class number;
}

class number : public QDialog
{
    Q_OBJECT

public:
    explicit number(QString ip, int port, QString num, QWidget *parent=0);
    void init();
    int initsock();
    void paintEvent(QPaintEvent *);
    ~number();

private slots:

    void timerUpdate();
    void on_start_clicked();

    void on_start_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::number *ui;
    QString m_ip;
    int m_port;
    QString m_num;
    QTcpSocket fd;//通信
    QMediaPlayer play;//音乐
};

#endif // NUMBER_H
