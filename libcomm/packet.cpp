#include "logger.h"
#include "packet.h"
//
#include <QByteArray>

const QByteArray packet1::p_start = QByteArrayLiteral("\x7E\x81");
const QByteArray packet1::p_end = QByteArrayLiteral("\x0A");

packet1::packet1(QByteArray a)
{
    _log::log("packet1::packet1()");

    if (a.isNull() || a.isEmpty() || 0>=a.size()) return;
    //
    //if(48 != a.size()) return;     //size????
    //
    //        if (a.at(0) != this->sync0) return;
    //        if (a.at(1) != this->sync1) return;
    //
    //        switch(a.at(2)){
    //        case 0x10:
    //        case 0x11:
    //        case 0x50:
    //        case 0x80:
    this->svc = a.at(2);
    //            break;
    //        default:
    //            return;
    //            break;
    //        };
    //
    //        if (0x01 > a.at(3)) return;
    //        if (0x08 < a.at(3)) return;
    this->lzone = a.at(3);
    //  qDebug() << byte2hexs(a);
    //
    //this->res1 = a.at(4);
    //    if (0x01 > a.at(5)) return;
    //    if (0x08 < a.at(5)) return;
    this->rzone = a.at(5);
    //this->res2 = a.at(6);
    this->sig = a.mid(7,16);
    //
    //    for (int i=0; i<this->sig.count(); i++)
    //        if (0x0A > this->sig.at(i))
    //            return;
    //
    //new QByteArray(
    //          a.mid(7,16)
    //        );
    //
    //    if (0x01 > a.at(23)) return;
    //    if (0x03 < a.at(23)) return;
    this->mod = a.at(23);
    //qDebug() << " mod=" << QString::number(this->mod, 16).toUpper();
    //
    //    if (0x01 > a.at(24)) return;
    //    if (0x09 < a.at(24)) return;
    this->lim = a.at(24);
    //qDebug() << " lim=" << QString::number(this->lim, 16).toUpper();

    //
    //qDebug() << " spd=" << QString::number(a.at(25), 16).toUpper();
    switch (a.at(25)){
    case 0x06:
        this->spd = 3;
        break;
    case 0x05:
        this->spd = 6;
        break;
    case 0x04:
        this->spd = 9;
        break;
    default:
        this->spd = 0;
        break;
    }

    //qDebug() << " spd=" << QString::number(this->spd, 16).toUpper();
    //
    //this->res3 = a.mid(26,21);
    //new QByteArray(
    //  a.mid(26,21)
    //);
    //
    //if (p_end != a.at(47)) return;
}

packet1::packet1(){
    _log::log("packet1::packet1()");
    //
    this->rzone=0;
    this->lzone=0;
    this->spd=0;
    //
    this->sig = QByteArray::fromHex(
                QVariant("00000000000000000000000000000000")
                .toByteArray());
}
