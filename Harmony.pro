TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += .

SOURCES += main.cpp \
    core/board/board.cpp \
    core/board/position.cpp \
    core/events/event.cpp \
    core/events/chooseaction.cpp \
    core/events/pureharmony.cpp \
    core/turn.cpp \
    core/game.cpp \
    core/player.cpp \
    core/engine.cpp \
    core/harmonycard.cpp \
    core/disharmonycard.cpp \
    core/card.cpp \
    core/element.cpp

HEADERS += \
    core/board/board.hpp \
    core/board/position.hpp \
    core/events/event.hpp \
    core/events/chooseaction.hpp \
    core/events/pureharmony.hpp \
    core/turn.hpp \
    core/game.hpp \
    core/player.hpp \
    core/engine.hpp \
    core/harmonycard.hpp \
    core/disharmonycard.hpp \
    core/card.hpp \
    core/element.hpp

LIBS += -lboost_serialization-mgw48-mt-1_55
