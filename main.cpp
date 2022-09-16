#include "pcscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PCScreen w;
    w.show();
    return a.exec();
}
