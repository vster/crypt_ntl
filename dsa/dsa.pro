TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    dsa.cpp

LIBS += \
   -L../../lib -lntl -lgmp
