#include "logger.h"
#include "mport.h"
//
mport::mport(QObject *parent) :
    QObject(parent)
{
    _log::log("mport::mport()");
}

//mport::~mport()
//{
//    _log::log("mport::~mport()");
//    //delete this->port;
//}

bool mport::clear(){
    _log::log("mport::clear()");
    return this->port.clear(QSerialPort::AllDirections); // to clear or not to clear ...
}

QByteArray mport::rx(){
    _log::log("mport::rx()");
    //******** serial read 20200114 ******
    QByteArray _rx = this->port.readAll();
    this->port.clear(QSerialPort::Input);
    //************************************
    return _rx;
}

bool mport::tx(QByteArray b){
    _log::log("mport::tx()");
    //******** serial write 20200114 *****
    this->port.clear(QSerialPort::Output);
    this->port.write(
                b.data(),
                b.size());
    return this->port.flush();
    //************************************
}

void mport::poll(){
    _log::log("mport::poll()");
    //
    QByteArray _rx = this->rx();
    this->rbuff.append(_rx);
}
