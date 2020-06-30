#ifndef COMM_H
#define COMM_H
//
#include <QVector>
class QTimer;
//
#include "mport.h"

static const QStringList serr  = QStringList() << "QSerialPort::NoError" << "QSerialPort::DeviceNotFoundError" << "QSerialPort::PermissionError" << "QSerialPort::OpenError" << "QSerialPort::ParityError" << "QSerialPort::FramingError" << "QSerialPort::BreakConditionError" << "QSerialPort::WriteError" << "QSerialPort::ReadError" << "QSerialPort::ResourceError" << "QSerialPort::UnsupportedOperationError" << "QSerialPort::UnknownError" << "QSerialPort::TimeoutError" << "QSerialPort::NotOpenError";

class comm : public QObject
{
    Q_OBJECT
public:
    explicit comm(QObject* parent = nullptr);
    ~comm();
    //
    bool init(QString ini);
    QStringList list;
    //
    QVector<QByteArray> rx(int i, QByteArray ps, QByteArray pe);
    QByteArray rx(int i);
    bool tx(QByteArray b);
    bool tx(int i, QByteArray b);
    //
    int tick = 0;
    bool noUi = false;

private:
    bool clear(int i);
    bool clear(QString s);
    //
    bool init();
    // QSerialPortInfo* info = nullptr;
    QVector<QSharedPointer<mport>> ports;
    QTimer* ticker = nullptr;
    //
    //QVector<QByteArray> rx(int i, unsigned char ps, unsigned char pe);
    QVector<QByteArray> rx(QString s, unsigned char ps, unsigned char pe);
    //
    //
    QByteArray rx();
    QByteArray rx(QString s);
    //
    //QVector<QByteArray> rx(int j, unsigned char ps, unsigned char pe);
    QVector<QByteArray> rx(QByteArray _rx, unsigned char ps, unsigned char pe);
    //
    int total = 0;

public slots:

signals:
    void readyRead();

private slots:
    void poll();

};
#endif //COMM_H
