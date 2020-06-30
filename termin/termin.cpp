#include "termin.h"
#include "ui_termin.h"
//

QString oldstyle(QString s){
    _log::log("style1()");
    QString pref="<html><body style=\" font-family:'Monospace'; font-size:8pt;\"><span style=\" font-size:10; font-weight: bold; color:#80ff80;\">";
    QString suf="</span></body></html>";
    //
    return pref+s+suf;
}

termin::termin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::termin)
{
    ui->setupUi(this);
    //
    this->comm1 = QSharedPointer<comm>(
                new comm());
    //
    qDebug() << QCoreApplication::arguments().at(0)+".ini";
    //
    if(this->comm1->init(
                QCoreApplication::arguments().at(0)+".ini"))
    {

        int ls = this->comm1->list.size();
        while(0<ls){
            ls--;
            this->ui->portList->addItem(
                        this->comm1->list.at(ls));
        };
        //
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::black);
        palette->setColor(QPalette::Text,
                          QColor("#80ff80"));
        //
        this->ui->lineEdit_2->setPalette(*palette);
        this->ui->lineEdit_2->setText("$");
        this->ui->lineEdit_2->setEnabled(false);
        //
        this->ui->lineEdit->setPalette(*palette);
        connect(this->ui->lineEdit, &QLineEdit::returnPressed, [this]
                () {
            QString msg = this->ui->lineEdit->text();
            this->ui->textEdit->append(
                        oldstyle(msg));
            this->ui->lineEdit->clear();
            //
            if(this->comm1->tx(
                        this->ui->portList->currentIndex(),
                        msg.toUtf8().toHex()))
                this->ui->textEdit->append("ok");
        });
        //
        this->ui->textEdit->setPalette(*palette);
        this->ui->textEdit->setOverwriteMode(false);
        this->ui->textEdit->setEnabled(false);
        //
        connect(this->comm1.get(),
                SIGNAL(
                    readyRead()),this,
                SLOT(
                    poll()));
    }
}

termin::~termin()
{
    delete ui;
}

void termin::poll(){
    //    _log::log("termin::poll() опрос портов "
    //              +QString::number(this->comm1->total)
    //              +" байт ");
    //
    filter2 filter(
                this->ui->portList->currentIndex(), this->comm1);
    int fs = filter.size();
    while (0<fs){
        fs--;
        this->buff.append(
                    filter.at(fs));
        this->ui->textEdit->append(
                    oldstyle(
                        QByteArray::fromHex(this->buff.last()->data())+"\n"));
    };
    //
}


