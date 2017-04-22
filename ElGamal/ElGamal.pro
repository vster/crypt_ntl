TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ElGamal.cpp

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl

