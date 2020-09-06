#ifndef CHA_H
#define CHA_H
#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class Cha;
}

class Cha : public QDialog
{
    Q_OBJECT



public:
    explicit Cha(QString ip, int port,QWidget *parent = 0);
    ~Cha();
    void init();
    int initsock();
private slots:

    void on_chaxun_clicked();

    void on_pushButton_clicked();

private:
    Ui::Cha *ui;
    QString mip;
    int mport;
    QString m_d;
    QTcpSocket fd;
};

#endif // CHA_H
