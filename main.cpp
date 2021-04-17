#include "mont.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mont w;
    w.show();
    return a.exec();
}
