TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    dh.cpp

LIBS += \
    -L/usr/local/lib -lntl -lgmp
