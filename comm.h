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

signals:
    void readyRead();

public slots:
    QByteArray* rx(int i);
    QByteArray* rx(QString s);

private slots:
    void init();
    void poll();
};

#endif // COMM_H
