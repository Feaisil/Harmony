TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp \
    core/board/board.cpp \
    core/common.cpp \
    core/events/event.cpp \
    core/board/position.cpp \
    core/events/chooseaction.cpp \
    core/turn.cpp \
    core/game.cpp \
    core/player.cpp \
    core/events/pureharmony.cpp

HEADERS += \
    core/board/board.hpp \
    core/common.hpp \
    core/board/position.hpp \
    core/events/event.hpp \
    core/events/chooseaction.hpp \
    core/turn.hpp \
    core/game.hpp \
    core/player.hpp \
    core/events/pureharmony.hpp

