#include "test.h"
//
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //
    test w;
    w.show();
    w.log("int main() доступных портов: "+
          QString::number(
              w.comm1->ports->count()
              ));
    //
    return a.exec();
}
