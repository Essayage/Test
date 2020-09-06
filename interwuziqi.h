#ifndef INTERWUZIQI_H
#define INTERWUZIQI_H

#include <QDialog>
#include <QMouseEvent>
#include "QMediaPlayer"
#include <QTcpSocket>


namespace Ui {
class interwuziqi;
}

class interwuziqi : public QDialog
{
    Q_OBJECT

public:
    explicit interwuziqi(QString ip,int port,QString name,QWidget *parent = 0);
    ~interwuziqi();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *m);
    int initsock();//初始化网络

    int chessboard[20][20];
    QMediaPlayer *musicPlayer;

    void init(int n);
    int judgeWin();
    void first();
    int dong(int,int,QString);
private slots:

    int Receive();

    void on_start_clicked();

    void on_exit_clicked();

    void on_playMusic_clicked();

    void on_horizontalSlider_actionTriggered(int action);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::interwuziqi *ui;
    QTcpSocket cFd;
    int cPort;
    QString cIp;
    QString cName;
    QString Himself;
};

#endif // INTERWUZIQI_H
