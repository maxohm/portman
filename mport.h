#ifndef MPORT_H
#define MPORT_H
//
#include <QObject>
#include <QtSerialPort>
//
QString byte2hexs(QByteArray* b);
//
class mport : public QObject
{
    Q_OBJECT
public:
    explicit mport(QObject *parent = 0);
    ~mport();
    //
    QSerialPort* port;
    QByteArray* buff;

public slots:
    void poll();
    QByteArray* rx();
    void tx(QByteArray* b);

signals:

};

#endif // MPORT_H
