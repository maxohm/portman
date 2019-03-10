#include "comm.h"
//
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

comm::comm(QObject *parent) : QObject(parent)
{
    this->init();
    //
    this->ticker = new QTimer();
    connect(this->ticker,SIGNAL(timeout()),this,SLOT(poll()));
    this->ticker->start(1000);
}

comm::~comm()
{
    delete this->info;
    delete this->list;
    delete this->ports;
    delete this->ticker;
}

void comm::init(){
    this->info = new QSerialPortInfo();
    this->list = new QStringList();
    this->ports = new QList<mport*>(); // с каких таких QList*<> ???
    //
    const auto _info = this->info->availablePorts();
    //
    for (int i=0; i<_info.count(); i++)
    {
        this->list->append(
                    _info.at(i).portName()
                    );
        //
        mport* p = new mport();
        p->port = new QSerialPort();
        p->port->setPort(
                    _info.at(i)
                    );
        //        p->setBaudRate(QSerialPort::Baud115200);        // скорость передачи - 115200
        //        p->setDataBits(QSerialPort::Data8);             // инф.бит в посылке - 8
        //        p->setStopBits(QSerialPort::OneStop);           // стоп.бит          - 1
        //        P->setParity(QSerialPort::NoParity);            // без проверки на четность
        //        p->setFlowControl(QSerialPort::NoFlowControl);  // управл.потоком данных отсутствует
        connect(p->port,SIGNAL(readyRead()),p,SLOT(poll()));
        //
        this->ports->append(p);
    };
};

//QByteArray* comm::rx(){
//    QByteArray* _rx = new QByteArray(
//                this->ports->at(i)->readAll()
//                );
//    return _rx;
//};

//void comm::tx(QByteArray* b){

//};

void comm::poll(){
    this->ticker->stop();
    this->polled = this->ports->size();
    this->total = 0;

    for (int i=0; i<this->polled; i++)
    {
       this->total += this->ports->at(i)->buff->size();
    };

    emit this->readyRead();
    this->ticker->start(1000);
}
