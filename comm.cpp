#include "comm.h"
//
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

comm::comm(QObject *parent) : QObject(parent)
{
    this->info = new QSerialPortInfo();
    this->list = new QStringList();
    const auto _info = this->info->availablePorts();
    //
    for (int i=0; i<_info.count(); i++)
    {
        this->list->append(
                    _info.at(i).portName()
                    );
        //
        QSerialPort* _port = new QSerialPort();
        _port->setPort(
                    _info.at(i)
                    );
//        _port->setBaudRate(QSerialPort::Baud115200);        // скорость передачи - 115200
//        _port->setDataBits(QSerialPort::Data8);             // инф.бит в посылке - 8
//        _port->setStopBits(QSerialPort::OneStop);           // стоп.бит          - 1
//        _port->setParity(QSerialPort::NoParity);            // без проверки на четность
//        _port->setFlowControl(QSerialPort::NoFlowControl);  // управл.потоком данных отсутствует
        //
        this->port->append(_port);
    };
    //
//    return _list;
}

QStringList* comm::init(){
};

QByteArray* comm::rx(){
};

void comm::tx(QByteArray* b){
};
