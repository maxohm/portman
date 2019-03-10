#include "test.h"
#include "comm.h"
//
#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    //QCoreApplication coreApplication(argc, argv);
    QApplication a(argc, argv);

    //    QTextStream out(stdout);
    //    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    //    out << "Total number of ports available:  " << serialPortInfos.count() << endl;

    //    const QString blankString = "N/A";
    //    QString description;
    //    QString manufacturer;
    //    QString serialNumber;

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

    //return 0;

    comm* comm1;
    comm1 = new comm();

    test w;
    w.show();
    w.log("int main()");

    w.log("ports available:  "+QString::number(comm1->list->size()));


    return a.exec();
}
