#include "mport.h"

mport::mport(QObject *parent) : QObject(parent)
{
    //this->ticker = new QTimer();
    this->buff = new QByteArray();
}

mport::~mport()
{
    delete this->port;
    delete this->buff;
}

QByteArray* mport::rx(){
    QByteArray* _rx = new QByteArray(
                this->port->readAll()
                );
    return _rx;
};

void mport::tx(QByteArray* b){
    this->port->write(
                b->data(),
                b->size()
                );
};

void mport::poll(){
    this->buff->append(
                this->rx()->data()
                );
}
