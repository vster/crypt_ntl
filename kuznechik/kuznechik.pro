TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    kuznechik.cpp \
    util.cpp

HEADERS += \
    util.h

INCLUDEPATH += \
    ../../include

LIBS += \
    -L../../lib -lntl
