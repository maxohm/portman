#ifndef COMM_H
#define COMM_H
//
#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QList>

class comm : public QObject
{
    Q_OBJECT
public:
    explicit comm(QObject *parent = nullptr);
    QSerialPortInfo* info;
    QStringList* list;
    QList<QSerialPort*>* port;

signals:

public slots:
    QStringList* init();
    QByteArray* rx();
    void tx(QByteArray* b);

};

#endif // COMM_H
