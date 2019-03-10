#ifndef TEST_H
#define TEST_H

#include <QMainWindow>

namespace Ui {
class test;
}

class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    ~test();

public slots:
    void log(QString s);

private:
    Ui::test *ui;

private slots:
};

#endif // TEST_H
