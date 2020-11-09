TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        parser.cpp \
        virtualmachine.cpp

HEADERS += \
    exceptions.h \
    keyword.h \
    parser.h \
    virtualmachine.h
