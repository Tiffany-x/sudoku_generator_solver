#include "maingame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainGame w;
    w.show();
    return a.exec();
}
