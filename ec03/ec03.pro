TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    convhex.cpp \
    ec03.cpp \
    QxyNTL.cpp

HEADERS += \
    convhex.h \
    QxyNTL.h

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
