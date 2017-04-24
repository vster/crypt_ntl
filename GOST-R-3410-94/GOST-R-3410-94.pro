TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    GOST-R-3410-94.cpp

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
