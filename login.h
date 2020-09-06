#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    void paintEvent(QPaintEvent *);

private slots:
    void on_log_clicked();

    void on_clo_clicked();

private:
    Ui::login *ui;
    QMediaPlayer play;//音乐
};

#endif // LOGIN_H
