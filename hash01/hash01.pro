TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    hash.cpp

HEADERS += \
    hash.h

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
