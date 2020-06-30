#include "termin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    termin w;
    w.show();
    //
    return a.exec();
}
