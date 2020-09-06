#ifndef X_LOGIN_H
#define X_LOGIN_H

#include <QWidget>

namespace Ui {
class x_login;
}

class x_login : public QWidget
{
    Q_OBJECT

public:
    explicit x_login(QWidget *parent = 0);
    ~x_login();

private slots:
    void on_log_clicked();

    void on_clo_clicked();


private:
    Ui::x_login *ui;
};

#endif // LOGIN_H
