#ifndef TEST_H
#define TEST_H
//
#include "comm.h"
#include <QMainWindow>
//

namespace Ui {
class test;
}

class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    ~test();
    //
    QString st;
    comm* comm1;
    unsigned char empty_lim = 20;
    int total;

public slots:
    void log(QString s);
    void poll();

private:
    Ui::test *ui;

private slots:
};

#endif // TEST_H
