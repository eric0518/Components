#include "JwMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JwMainWindow w;
    w.show();

    return a.exec();
}
