#include "libcomm.h"
#include "logger.h"
//
#include <QFile>
//#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSettings>
#include <QTimer>

comm::comm(QObject *parent) :
    QObject(parent)
  , ticker(new QTimer)
{
    _log::log("comm::comm()");
}

comm::~comm()
{
    _log::log("comm::~comm()");
    //delete this->info;
    this->ports.clear();
    delete this->ticker;
}

//QSerialPortInfo::availablePorts()
//    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
//        description = serialPortInfo.description();
//        manufacturer = serialPortInfo.manufacturer();
//        serialNumber = serialPortInfo.serialNumber();
//        out << endl
//            << "Port: " << serialPortInfo.portName() << endl
//            << "Location: " << serialPortInfo.systemLocation() << endl
//            << "Description: " << (!description.isEmpty() ? description : blankString) << endl
//            << "Manufacturer: " << (!manufacturer.isEmpty() ? manufacturer : blankString) << endl
//            << "Serial number: " << (!serialNumber.isEmpty() ? serialNumber : blankString) << endl
//            << "Vendor Identifier: " << (serialPortInfo.hasVendorIdentifier()
//                                         ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16)
//                                         : blankString) << endl
//            << "Product Identifier: " << (serialPortInfo.hasProductIdentifier()
//                                          ? QByteArray::number(serialPortInfo.productIdentifier(), 16)
//                                          : blankString) << endl
//            << "Busy: " << (serialPortInfo.isBusy() ? "Yes" : "No") << endl;
//    }
//
//port.setBaudRate(QSerialPort::Baud115200);        // скорость передачи - 115200
//port.setBaudRate(QSerialPort::Baud9600);
//port.setDataBits(QSerialPort::Data8);             // инф.бит в посылке - 8
//port.setStopBits(QSerialPort::OneStop);           // стоп.бит          - 1
//port.setParity(QSerialPort::NoParity);            // без проверки на четность
//port.setFlowControl(QSerialPort::NoFlowControl);  // управл.потоком данных отсутствует
//

bool comm::init()
{
    _log::log("comm::init()");
    //************************* serial init 20200124 ************************
    QList<QSerialPortInfo> _list = QSerialPortInfo::availablePorts();
    int i = _list.size();
    //
    this->list.clear();
    while(0<i){
        i--;
        //
        this->list.append(
                    _list.at(i).portName());
    };
    if (0<this->list.size())
        return true;
    //***********************************************************************
    //
    return false;
}

bool comm::init(QString ini){
    _log::log("comm::init() "+ini);
    //
    qDebug() << "comm::init() " << ini;
    if(!this->init())
        return false;
    //
    int i = this->list.size();
    if(0>=i)
        return false;
    //
    QSettings settings(ini,
                       QSettings::IniFormat);
    QStringList groups = settings.childGroups();
    while(0<i){
        i--;
        //
        if(groups.contains(
                    this->list.at(i))){

            //
            settings.beginGroup(
                        this->list.at(i));
            //
            qDebug() << this->list.at(i);
            //
            QSharedPointer<mport> p = QSharedPointer<mport>(
                        new mport());
            p->port.setPortName(
                        this->list.at(i));
            p->port.setBaudRate(
                        settings.value("baudRate", QSerialPort::Baud115200)
                        .toInt());
            p->port.setDataBits(
                        static_cast<QSerialPort::DataBits>(
                            settings.value("dataBits", QSerialPort::Data8)
                            .toInt()));
            p->port.setFlowControl(
                        static_cast<QSerialPort::FlowControl>(
                            settings.value("flowControl", QSerialPort::NoFlowControl)
                            .toInt()));
            p->port.setParity(
                        static_cast<QSerialPort::Parity>(
                            settings.value("parity", QSerialPort::NoParity)
                            .toInt()));
            p->port.setStopBits(
                        static_cast<QSerialPort::StopBits>(
                            settings.value("stopBits", QSerialPort::OneStop)
                            .toInt()));
            p->port.clearError();
            p->port.close();
            //
            bool readOnly = settings.value("readOnly", false)
                    .toBool();
            //
            if (readOnly)
                if (!p->port.open(QIODevice::ReadOnly)) {
                    qDebug() << "comm::init() config file " << ini << " error " << serr[p->port.error()];
                    continue;
                };
            //
            if (!readOnly)
                if (!p->port.open(QIODevice::ReadWrite)) {
                    qDebug() << "comm::init() config file " << ini << " error " << serr[p->port.error()];
                    continue;
                };
            //
            if (p->port.isOpen()){
                this->noUi = settings.value("disableUi", false)
                        .toBool();
                //
                p->filter = settings.value("setFilter", false)
                        .toBool();
                p->limit = settings.value("setLimit", false)
                        .toBool();
                p->p_size = settings.value("dataSize", 48)
                        .toInt();
                p->tick = settings.value("setTimer", 20)
                        .toInt();
                p->timeout = p->tick*1000;
                //
                qDebug() << "comm::init() "+this->list.at(i)+" ok";
                qDebug() << "   filter      = " << p->filter;
                qDebug() << "   tick        = " << p->tick;
                qDebug() << "   data size   = " << p->p_size;
                //
                connect(&p->port,
                        SIGNAL(
                            readyRead()),
                        p.get(),
                        SLOT(
                            poll()));
                //
                this->ports.append(p);
                //
                this->tick+=p->tick;
            };

        };
    };
    //
    int ps =this->ports.size();
    this->list.clear();
    if (0>=ps)
        return false;
    //
    while(0<ps)
    {
        ps--;
        this->list.append(
                    this->ports.at(ps)->port.portName());
    };
    //
    connect(this->ticker,
            SIGNAL(
                timeout()),this,
            SLOT(
                poll()));
    this->ticker->start(this->tick);
    //
    return true;
}

//bool comm::clear(int i){
//    _log::log("comm::clear() "+QString::number(i));
//    return this->ports[i]->clear();
//}

//bool comm::clear(QString s){
//    _log::log("comm::clear() "+s);
//    int i = this->list.indexOf(s);
//    //
//    if (0<=i)
//        return this->ports[i]->clear();
//    return false;
//}

QByteArray comm::rx(){
    _log::log("comm::rx()");
    return this->rx(0);
}

QByteArray comm::rx(int i){
    _log::log("comm::rx() "+
              QString::number(i));
    //
    QByteArray _rx;
    //******** serial read 20200124 ******
    int bs=this->ports.at(i)->rbuff.size();
    if(bs>=this->ports.at(i)->p_size){
        _rx = this->ports.at(i)->rbuff.left(bs);
        this->ports.at(i)->rbuff.remove(0,bs);
        // this->ports.at(i)->rbuff.replace(_rx, // реализация с удалением повторов
        // QByteArray(""));
    };
    //************************************
    return _rx;
}

bool comm::tx(QByteArray b){
    return this->tx(0,b);
}

bool comm::tx(int i, QByteArray b){
    _log::log("comm::tx() port "
              +QString::number(i)
              +" bytes "+QString::number(
                  b.size()));
    //
    //******** serial write 20200128 ******
    return this->ports.at(i)->tx(b);
    //************************************
}

/**
 * @brief comm::rx  Функция выбора из байтового массива
 * @param _rx       Необработанный байтовый массив
 * @param ps        Начало массива для поиска
 * @param pe        Конец массива для поиска
 * @return          Массив байтовых массивов с начальным байтом ps и окончанием pe
 */
QVector<QByteArray> comm::rx(QByteArray _rx, unsigned char ps, unsigned char pe){
    _log::log("comm::rx() start "+
              QString::number(ps)+" end "
              +QString::number(pe));
    //
    QVector<QByteArray> flist;
    if (_rx.isNull() || _rx.isEmpty() || 0>=_rx.size()) return flist;
    //
    // ************************************************************
    // ***************** filter engine 20190318 *******************
    // ************************************************************
    //
    int _pst = 0;
    int _pse = 1;
    int _psl;
    //
    int i = _rx.count(ps);
    //
    while (0<i) {
        _pse = _rx.lastIndexOf(pe);
        _pst = _rx.lastIndexOf(ps);
        _psl = _pse-_pst+1;
        //
        flist.push_front(
                    _rx.mid(_pst,_psl));
        _rx.truncate(_pst);
        i--;
    };
    //
    // ************************************************************
    // ************************************************************
    // ************************************************************
    return flist;
}

QVector<QByteArray> comm::rx(int i, QByteArray ps, QByteArray pe){
    _log::log("comm::rxs() port "
              +QString::number(i));
    //
    QByteArray _rx = this->rx(i);
    //
    QVector<QByteArray> flist;
    flist.clear();
    if (_rx.isNull()
            || _rx.isEmpty())
        return flist;
    //
    int _p_size = this->ports.at(i)->p_size;
    // ************************************************************
    // ***************** filter engine 20200120 *******************
    // ************************************************************
    //
    int k=_rx.count(ps);
    while(0<k && _p_size<=_rx.size())
    {
        k--;
        int _pst = _rx.indexOf(ps);
        QByteArray b = _rx.mid(_pst, _p_size);
        if(_p_size<=b.size())
            if (pe==b.right(
                        pe.size())){
                //qDebug() << b.toHex(':');
                flist.push_back(b);
            };
        _rx.remove(0,_pst+b.size());
    };
    //
    // ************************************************************
    // ************************************************************
    // ************************************************************
    if(0<_rx.size())
        this->ports.at(i)->rbuff.prepend(_rx);
    //
    return flist;
}

//QVector<QByteArray> comm::rx(int i, unsigned char ps, unsigned char pe){
//    _log::log("comm::rx() "
//              + QString::number(i) + " start "
//              + QString::number(ps) + " end "89027c7bbf31
//              + QString::number(pe));
//    //
//    QByteArray _rx = this->rx(i);
//    return this->rx(_rx,ps,pe);
//}

//QVector<QByteArray> comm::rx(QString s, unsigned char ps, unsigned char pe){
//    _log::log("comm::rx() " + s + " start "
//              + QString::number(ps) + " end "
//              + QString::number(pe));
//    //
//    QByteArray _rx = this->rx(s);
//    return this->rx(_rx,ps,pe);
//}

QByteArray comm::rx(QString s){
    _log::log("comm::rx() " + s);
    //
    int i = this->list.indexOf(s);
    //
    if (0<=i)
        return this->rx(i);
    //*************************************************************
    QByteArray r;
    QFile* f = new QFile(s);
    if (f->open(QIODevice::ReadOnly))
        r = f->readAll();
    //*************************************************************
    return r;
}

void comm::poll(){
    this->ticker->stop();
    //
    this->total = 0;
    //
    int i = this->ports.size();
    while(0<i)
    {
        i--;
        _log::log("comm::poll() "+
                  QString::number(i));
        //        if(this->ports.at(i)->limit)
        //            if (0>=this->ports.at(i)->timeout)
        //                continue;
        this->total += this->ports.at(i)->rbuff.size();
    }
    //
    if(0<this->total)
        emit this->readyRead();
    //
    this->ticker->start(this->tick);
}
