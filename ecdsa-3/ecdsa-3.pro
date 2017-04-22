TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ecdsa-main.cpp \
    ecdsa.cpp \
    QxyNTL.cpp \
    zzhex.cpp

HEADERS += \
    ecdsa.h \
    QxyNTL.h \
    zzhex.h

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl

