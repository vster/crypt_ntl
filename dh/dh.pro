TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    dh.cpp

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
