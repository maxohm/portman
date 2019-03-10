#include "ui_test.h"
#include "test.h"
//
#include <QDate>

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    connect(this->ui->log->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this->ui->log, SLOT(scrollToBottom()));
    //
    this->comm1 = new comm();
    connect(this->comm1,SIGNAL(readyRead()),this,SLOT(poll()));
}

test::~test()
{
    delete ui;
}

void test::log(QString s)
{
    QDate d = QDate::currentDate();
    QTime c = QTime::currentTime();
    //
    int rc = ui->log->rowCount();
    //
    ui->log->insertRow(rc);
    QTableWidgetItem *t= new QTableWidgetItem (d.toString("dd.MM.yy")+" "+c.toString("hh:mm:ss")+" "+s);
    ui->log->setItem(rc,0,t);
    ui->log->resizeColumnsToContents();
}

void test::poll(){
    if (0>=empty_lim) return;
    //
    this->log("poll "+
              QString::number(this->comm1->polled)+
              " port buffers filled with "+
              QString::number(this->comm1->total)+
              " bytes "
              );
    //
    if (0<this->comm1->total) {
        empty_lim = 20;
    } else empty_lim--;
    //
    if (0>=empty_lim) log(" 20 sec. no data - pollinq sequence stopped ...");
};
