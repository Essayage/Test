#ifndef GAMES_H
#define GAMES_H

#include <QDialog>

namespace Ui {
class GAMES;
}

class GAMES : public QDialog
{
    Q_OBJECT

public:
    explicit GAMES(QWidget *parent = 0);
    ~GAMES();

private slots:
    void on_game1_clicked();

    void on_game2_clicked();

    void on_game1_2_clicked();

    void on_game3_clicked();

    void on_game4_clicked();

    void on_game5_clicked();

    void on_game1_3_clicked();

private:
    Ui::GAMES *ui;
};

#endif // GAMES_H
