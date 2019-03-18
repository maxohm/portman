#include "comm.h"
//

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
    //delete this->list;
    delete this->ports;
    delete this->ticker;
}

void comm::init(){
    this->info = new QSerialPortInfo();
    this->ports = new QList<mport*>();  // с каких таких QList*<> ???
    const auto _info = this->info->availablePorts();
    //
    for (int i=0; i<_info.count(); i++)
    {
        this->list.append(
                    _info.at(i).portName()
                    );
        //
        mport* p = new mport();
        p->port = new QSerialPort();
        p->port->setPort(
                    _info.at(i)
                    );
        //p->port->setBaudRate(QSerialPort::Baud115200);      // скорость передачи - 115200
        p->port->setBaudRate(QSerialPort::Baud9600);
        p->port->setDataBits(QSerialPort::Data8);             // инф.бит в посылке - 8
        p->port->setStopBits(QSerialPort::OneStop);           // стоп.бит          - 1
        p->port->setParity(QSerialPort::NoParity);            // без проверки на четность
        p->port->setFlowControl(QSerialPort::NoFlowControl);  // управл.потоком данных отсутствует
        connect(p->port,SIGNAL(readyRead()),p,SLOT(poll()));
        //
        p->port->open(QIODevice::ReadOnly);
        //
        this->ports->append(p);
    };
};

bool comm::clear(int i){
    return this->ports->at(i)->clear();
}

bool comm::clear(QString s){
    int i = this->list.indexOf(s);
    //
    if (0<=i)
        return this->ports->at(i)->clear();
    return false;
}

QByteArray* comm::rx(int i){
    QByteArray* _rx = new QByteArray(
                this->ports->at(i)->buff->remove(
                    0, this->ports->at(i)->buff->length()
                    ));
    //this->ports->at(i)->buff->clear();
    return _rx;
};

QList<QByteArray*>* comm::rx(QByteArray* _rx, unsigned char ps, unsigned char pe){
    //
    QList<QByteArray*>* flist = new QList<QByteArray*>();
    if (_rx->isNull() || _rx->isEmpty() || 0>=_rx->size()) return flist;
    //
    // ************************************************************
    // ***************** filter engine 20190318 *******************
    // ************************************************************
    //
    int _pst = 0;
    int _pse = 1;
    int _psl;
    //
    int i = _rx->count(ps);
    //
    while (0<i) {
        _pse = _rx->lastIndexOf(pe);
        _pst = _rx->lastIndexOf(ps);
        _psl = _pse-_pst+1;
        //
        flist->push_front(
                    new QByteArray(
                        _rx->mid(_pst,_psl)));
        //                    );
        _rx->truncate(_pst);
        i--;
    };
    //
    // ************************************************************
    // ************************************************************
    // ************************************************************
    return flist;
};

QList<QByteArray*>* comm::rx(int i, unsigned char ps, unsigned char pe){
    QByteArray* _rx = this->rx(i);
    return this->rx(_rx,ps,pe);
};

QList<QByteArray*>* comm::rx(QString s, unsigned char ps, unsigned char pe){
    QByteArray* _rx = this->rx(s);
    return this->rx(_rx,ps,pe);
};


QByteArray* comm::rx(QString s){
    int i = this->list.indexOf(s);
    //
    if (0<=i)
        return this->rx(i);
    //*************************************************************
    QFile* f = new QFile(s);
    if (f->open(QIODevice::ReadOnly))
        return new QByteArray(
                    f->readAll()
                    );
    //*************************************************************
    return new QByteArray();
};

void comm::poll(){
    this->ticker->stop();
    this->polled = this->ports->size();
    this->total = 0;
    //
    for (int i=0; i<this->polled; i++)
        this->total += this->ports->at(i)->buff->size();
    //
    emit this->readyRead();
    this->ticker->start(1000);
}
