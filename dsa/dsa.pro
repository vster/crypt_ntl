TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    dsa.cpp

INCLUDEPATH += \
    ../../include

LIBS += \
   -L../../lib -lntl
