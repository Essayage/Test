#ifndef WUZIQI_H
#define WUZIQI_H

#include <QDialog>
#include <QMouseEvent>
#include "QMediaPlayer"

namespace Ui {
class wuziqi;
}

class wuziqi : public QDialog
{
    Q_OBJECT

public:
    explicit wuziqi(QWidget *parent = 0);
    ~wuziqi();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *m);

    int chessboard[20][20];
    int n;
    QMediaPlayer *musicPlayer;

    void init(int n);
    int judgeWin();
    void first();
private slots:

    void on_start_clicked();

    void on_exit_clicked();

    void on_playMusic_clicked();

    void on_horizontalSlider_actionTriggered(int action);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::wuziqi *ui;
};

#endif // WUZIQI_H
