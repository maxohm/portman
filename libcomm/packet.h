#ifndef PACKET_H
#define PACKET_H
//
class QByteArray;
//

class packet1
{
public:
    packet1(QByteArray a);
    packet1();
    //
    static const QByteArray p_start;    // начало пакета

    unsigned char sync0 = 0x7E;         // байт синхронизации
    unsigned char sync1 = 0x81;         // байт синхронизации
    unsigned char svc = 0;              // служебный байт
    unsigned char lzone = 0x00;         // инд.номера зоны левого канала
    //unsigned char res1;               // резерв 1
    unsigned char rzone = 0x00;         // инд.номера зоны правого канала
    //unsigned char res2;               // резерв 2
    QByteArray sig;                     // уровень сигнала
    unsigned char mod = 0x00;           // режим
    unsigned char lim = 0x05;           // порог
    unsigned char spd = 0x00;           // скорость
    //QByteArray res3;                  // резерв 3

    static const QByteArray p_end;      // конец пакета
};

#endif //PACKET_H
