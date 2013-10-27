TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp \
    core/board.cpp \
    core/common.cpp

HEADERS += \
    core/board.hpp \
    core/common.hpp

