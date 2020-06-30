include(../../soordeenka.pri)

QT       -= gui network
QT       += serialport

TARGET = libcomm
TEMPLATE = lib
CONFIG += c++11

#QMAKE_CXXFLAGS += retpoline -std=c++11
DESTDIR = $$SOORD_BIN_PATH

DEFINES += LIBCOMM_LIBRARY

HEADERS += \
        comm.h \
        filter.h \
        libcomm.h \
        libcomm_global.h \
        logger.h \
        mport.h

SOURCES += \
        libcomm.cpp \
        filter.cpp \
        mport.cpp

win32 {
    RC_FILE = version.rc
    CONFIG += static
}
