TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    rsa.cpp

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
