QT       += core gui serialport

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = seritest
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    test.cpp \
    comm.cpp \
    mport.cpp


HEADERS += \
    test.h \
    comm.h \
    mport.h

FORMS += \
    test.ui
