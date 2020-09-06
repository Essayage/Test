#ifndef INTERLOGIN_H
#define INTERLOGIN_H

#include <QTcpSocket>
#include <QWidget>

namespace Ui {
class interlogin;
}

class interlogin : public QWidget
{
    Q_OBJECT

public:
    explicit interlogin(QWidget *parent = 0);
    ~interlogin();

private slots:
    void on_login_clicked();

    void on_cancel_clicked();

private:
    Ui::interlogin *ui;
};

#endif // INTERLOGIN_H
