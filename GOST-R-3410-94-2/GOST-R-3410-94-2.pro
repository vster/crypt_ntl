TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    convhex.cpp \
    zzhex.cpp \
    GOST-R-3410-94-2.cpp

HEADERS += \
    convhex.h \
    zzhex.h

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
