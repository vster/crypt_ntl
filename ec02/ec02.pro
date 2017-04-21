TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    convhex.cpp \
    ec02.cpp

HEADERS += \
    convhex.h

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
