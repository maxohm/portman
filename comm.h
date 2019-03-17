#ifndef COMM_H
#define COMM_H
//
#include "mport.h"
//
#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
//#include <QtSerialPort/QSerialPort>
//#include <QList>

class comm : public QObject
{
    Q_OBJECT
public:
    explicit comm(QObject *parent = nullptr);
    ~comm();
    //
    QSerialPortInfo* info;
    QStringList list;
    QList<mport*>* ports;
    //
    QTimer* ticker;
    int polled;
    int total;
    //
    QByteArray* rx(QString s);
    QByteArray* rx(int i);
    //
    QList<QByteArray*>* rx(QByteArray* _rx, unsigned char ps, unsigned char pe);
    QList<QByteArray*>* rx(int i, unsigned char ps, unsigned char pe);
    QList<QByteArray*>* rx(QString s, unsigned char ps, unsigned char pe);
    //
    bool clear(int i);
    bool clear(QString s);

signals:
    void readyRead();

private slots:
    void init();
    void poll();
};

#endif // COMM_H
