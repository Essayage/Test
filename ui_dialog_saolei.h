/********************************************************************************
** Form generated from reading UI file 'dialog_saolei.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SAOLEI_H
#define UI_DIALOG_SAOLEI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_saolie
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *num;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_2;
    QLineEdit *num_2;

    void setupUi(QDialog *Dialog_saolie)
    {
        if (Dialog_saolie->objectName().isEmpty())
            Dialog_saolie->setObjectName(QStringLiteral("Dialog_saolie"));
        Dialog_saolie->resize(1001, 723);
        Dialog_saolie->setFocusPolicy(Qt::WheelFocus);
        Dialog_saolie->setContextMenuPolicy(Qt::ActionsContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral("Mine/bomber.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog_saolie->setWindowIcon(icon);
        pushButton = new QPushButton(Dialog_saolie);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(760, 520, 161, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        label = new QLabel(Dialog_saolie);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(740, 40, 71, 61));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        num = new QLineEdit(Dialog_saolie);
        num->setObjectName(QStringLiteral("num"));
        num->setGeometry(QRect(810, 50, 113, 41));
        pushButton_2 = new QPushButton(Dialog_saolie);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(760, 340, 161, 51));
        pushButton_2->setFont(font);
        pushButton_3 = new QPushButton(Dialog_saolie);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(760, 440, 161, 51));
        pushButton_3->setFont(font);
        label_2 = new QLabel(Dialog_saolie);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(740, 160, 71, 61));
        label_2->setFont(font1);
        num_2 = new QLineEdit(Dialog_saolie);
        num_2->setObjectName(QStringLiteral("num_2"));
        num_2->setGeometry(QRect(810, 170, 113, 41));

        retranslateUi(Dialog_saolie);

        QMetaObject::connectSlotsByName(Dialog_saolie);
    } // setupUi

    void retranslateUi(QDialog *Dialog_saolie)
    {
        Dialog_saolie->setWindowTitle(QApplication::translate("Dialog_saolie", "liujt&saolei", 0));
        pushButton->setText(QApplication::translate("Dialog_saolie", "close", 0));
        label->setText(QApplication::translate("Dialog_saolie", "Level :", 0));
        pushButton_2->setText(QApplication::translate("Dialog_saolie", "begin", 0));
        pushButton_3->setText(QApplication::translate("Dialog_saolie", "again", 0));
        label_2->setText(QApplication::translate("Dialog_saolie", "time :", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_saolie: public Ui_Dialog_saolie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SAOLEI_H
