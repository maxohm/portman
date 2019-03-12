#include "ui_test.h"
#include "test.h"
//
#include <QDate>
#include <QDebug>

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    connect(this->ui->log->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this->ui->log, SLOT(scrollToBottom()));
    //
    this->comm1 = new comm();
    ui->rxlist->addItems(
                QStringList(this->comm1->list)
                );
    ui->txlist->addItems(
                QStringList(this->comm1->list)
                );
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
    this->log("test::poll() "+
              QString::number(this->comm1->polled)+
              " ports / "+
              QString::number(this->comm1->total)+
              " bytes "
              );
    //
    if (this->total!=this->comm1->total) {
        empty_lim = 20;
        this->total = this->comm1->total;
    } else empty_lim--;
    //
    if (0>=empty_lim)
        log("test::poll() no data - pollinq sequence aborted ...");
    if (0>=ui->rxlist->currentText().length()) return;
    //
    log("test::poll() "+
        ui->rxlist->currentText()+
        " data "+
        byte2hexs(
            this->comm1->rx(
                ui->rxlist->currentText()
                )));
};
