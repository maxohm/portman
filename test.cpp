#include "ui_test.h"
#include "test.h"
//
#include <QDate>
#include <QDebug>
#include <QFileDialog>

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    this->ui->setupUi(this);
    connect(this->ui->log->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this->ui->log, SLOT(scrollToBottom()));
    //
    this->comm1 = new comm();
    this->on_pushButton_clicked();
    connect(this->comm1,SIGNAL(readyRead()),this,SLOT(poll()));
    //
    this->infile = new QFile();
}

test::~test()
{
    delete ui;
    delete infile;
    delete outfile;
}

void test::log(QString s)
{
    QDate d = QDate::currentDate();
    QTime c = QTime::currentTime();
    //
    int rc = this->ui->log->rowCount();
    //
    this->ui->log->insertRow(rc);
    QTableWidgetItem *t= new QTableWidgetItem (d.toString("dd.MM.yy")+" "+c.toString("hh:mm:ss")+" "+s);
    this->ui->log->setItem(rc,0,t);
    this->ui->log->resizeColumnsToContents();
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
    if (0<this->comm1->total) {
        empty_lim = 20;
        this->total += this->comm1->total;
    } else empty_lim--;
    //
    if (0>=empty_lim)
        log("test::poll() нет данных - опрос прерван ...");
    if (0>=this->ui->rxlist->currentText().length()) return;

    // ***************************************************
    if(0<=this->ui->rxlist->currentText().indexOf("файл")){
        if (!this->infile->isOpen()){
            this->infile = new QFile(
                        QFileDialog::getOpenFileName(this,"Посл.порты отсутствуют - выберете файл данных","~/")
                        );
            if (!this->infile->open(QIODevice::ReadOnly)){
                empty_lim=0;
                log("test::poll() нет данных - опрос прерван ...");
            };
            return;
        } else {
            log("test::poll()"+this->infile->fileName());
            log("data");
            log(
                        byte2hexs(this->comm1->rx(
                                      this->infile->fileName()
                                      )));
                    return;
        };
    };
    // ***************************************************

    log("test::poll() "+
        this->ui->rxlist->currentText()+
        " data "+
        byte2hexs(
            this->comm1->rx(
                this->ui->rxlist->currentText()
                )));
};

void test::on_pushButton_clicked()
{
    this->ui->rxlist->clear();
    this->ui->rxlist->addItems(
                QStringList(this->comm1->list)
                );
    this->ui->rxlist->addItem("<файл>");
    this->ui->txlist->clear();
    this->ui->txlist->addItems(
                QStringList(this->comm1->list)
                );
    this->ui->txlist->addItem("<файл>");
}

void test::on_pushButton_2_clicked()
{
    this->empty_lim = 20;
    //
    if (0>=this->ui->rxlist->currentText().length()) return;
    this->comm1->clear(
                this->ui->rxlist->currentText()
                );
}

void test::on_pushButton_4_clicked()
{

}
