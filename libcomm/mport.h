#ifndef MPORT_H
#define MPORT_H
//
#include <QtSerialPort/QSerialPort>

class mport : public QObject
{
    Q_OBJECT
public:
    explicit mport(QObject *parent = 0);
    //~mport();
    //
    QByteArray rbuff;
    QByteArray wbuff;
    QSerialPort port;
    //
    bool filter = false;
    bool limit = false;
    int tick = 20;
    int p_size = 48;
    int timeout;
    //
    bool clear();
    bool tx(QByteArray b);

private:
    //
    QByteArray rx();

private slots:
    void poll();

public slots:

signals:

};

#endif //MPORT_H
