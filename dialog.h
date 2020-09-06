#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *k);
    ~Dialog();


private:
    void init();//初始化
    void sui();
    void paintEvent(QPaintEvent *);
    int pan();

private slots:
    void on_pushButton_6_clicked();


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    int map[4][4];
    int sum;


};

#endif // DIALOG_H
