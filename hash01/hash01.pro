TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    hash.cpp

HEADERS += \
    hash.h

INCLUDEPATH += \
    /usr/local/include

LIBS += \
    -L/usr/local/lib -lntl
