#include "searchtools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchTools w;
    w.show();

    return a.exec();
}
