TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    convhex.cpp \
    ec04.cpp \
    QxyNTL.cpp

HEADERS += \
    convhex.h \
    QxyNTL.h

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
