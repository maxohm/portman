#include "mport.h"
//
QString byte2hexs(QByteArray* b){  // byte to hexadecimal string
    QString s = "";
    //
    for (int i=0; i<b->size(); i++){
        QString _s = QString::number(b->at(i), 16).toUpper();
        //
        switch(_s.size()){
        case 0:
            s+="00 ";
            break;
        case 1:
            s+="0"+_s+" ";
            break;
        default:
            s+=_s+" ";
            break;
        };
        //        switch(_s.length()){
        //        case 0:
        //            s+="0x00 ";
        //            break;
        //        case 1:
        //            s+="0x0"+_s+" ";
        //            break;
        //        default:
        //            s+="0x"+_s+" ";
        //            break;
        //        };
    }
    //
    return s;
}

QByteArray* hexs2byte(QString s){  // hexadecimal string to byte
    QByteArray b = QByteArray::fromHex(
                s.toUtf8()
                );
    return new QByteArray(b);
}

mport::mport(QObject *parent) : QObject(parent)
{
    this->buff = new QByteArray();
}

mport::~mport()
{
    delete this->port;
    delete this->buff;
}

bool mport::clear(){
    return this->port->clear(QSerialPort::AllDirections); // to clear or not to clear ...
}

QByteArray* mport::rx(){
    QByteArray* _rx = new QByteArray(
                this->port->readAll()
                );
    this->clear();
    return _rx;
};

void mport::tx(QByteArray* b){
    this->port->write(
                b->data(),
                b->size()
                );
};

void mport::poll(){
    QByteArray* _rx = this->rx();
    this->buff->append(
                _rx->right(_rx->length())
                );
}
