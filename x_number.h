#ifndef NUMBER_H
#define NUMBER_H

#include <QDialog>
#include <QTcpSocket>
#pragma execution_character_set("utf-8")

namespace Ui {
class x_number;
}

class x_number : public QDialog
{
    Q_OBJECT

public:
    explicit x_number(QString ip, int port, QString num, QWidget *parent=0);
    void init();
    int initsock();
    ~x_number();

private slots:

    void on_start_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::x_number *ui;
    QString m_ip;
    int m_port;
    QString m_num;
    QTcpSocket fd;//通信
    char name[12][12];
};

#endif // NUMBER_H
