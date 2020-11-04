TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        parse.cpp \
        virtualmachine.cpp

HEADERS += \
    parse.h \
    virtualmachine.h
