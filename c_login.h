#ifndef C_LOGIN_H
#define C_LOGIN_H
#include <QWidget>

namespace Ui {
class c_Login;
}

class c_Login : public QWidget
{
    Q_OBJECT

public:
    explicit c_Login(QWidget *parent = 0);

    ~c_Login();
public slots:

    void on_login_clicked();

private:
    Ui::c_Login *ui;
};

#endif // LOGIN_H
