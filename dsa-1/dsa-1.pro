TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    convhex.cpp \
    dsa-main.cpp \
    dsa.cpp

HEADERS += \
    convhex.h \
    dsa.h

LIBS += \
    -L/usr/local/lib -lntl
