#ifndef SEARCHTOOLS_H
#define SEARCHTOOLS_H

#include <QDialog>

namespace Ui {
class SearchTools;
}

class SearchTools : public QDialog
{
    Q_OBJECT

public:
    explicit SearchTools(QWidget *parent = 0);
    ~SearchTools();
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::SearchTools *ui;
};

#endif // SEARCHTOOLS_H
