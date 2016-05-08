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
    /usr/local/include

LIBS += \
    -L/usr/local/lib -lntl
