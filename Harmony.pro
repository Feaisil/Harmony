TEMPLATE = app lib
CONFIG -= qt core
CONFIG += c++11 

QMAKE_CXXFLAGS += -std=c++11\
    -isystem $$PWD/../boost
INCLUDEPATH += . ../boost

SOURCES += main.cpp \
    core/board/board.cpp \
    core/board/position.cpp \
    core/events/event.cpp \
    core/events/chooseaction.cpp \
    core/events/drawdisharmony.cpp \
    core/events/checkforendconditions.cpp \
    core/turn.cpp \
    core/game.cpp \
    core/player.cpp \
    core/engine.cpp \
    core/harmonycard.cpp \
    core/disharmonycard.cpp \
    core/element.cpp \
    core/settings.cpp \
    interface/commandlineinterface.cpp \
    core/events/produce.cpp \
    core/events/addmodifier.cpp \
    core/events/playharmonycards.cpp \
    core/events/movetowardselement.cpp \
    core/events/harmoniousmeal.cpp \
    core/events/destroyressource.cpp \
    core/events/choosebetweenevents.cpp

HEADERS += \
    core/board/board.hpp \
    core/board/position.hpp \
    core/events/event.hpp \
    core/events/chooseaction.hpp \
    core/events/drawdisharmony.hpp \
    core/events/checkforendconditions.hpp \
    core/turn.hpp \
    core/game.hpp \
    core/player.hpp \
    core/engine.hpp \
    core/harmonycard.hpp \
    core/disharmonycard.hpp \
    core/element.hpp \
    core/settings.hpp \
    interface/commandlineinterface.hpp \
    core/interface/playerinterface.hpp \
    core/interface/settinginterface.hpp \
    core/modifier.hpp \
    core/events/produce.hpp \
    core/events/addmodifier.hpp \
    core/events/playharmonycards.hpp \
    core/events/movetowardselement.hpp \
    core/events/harmoniousmeal.hpp \
    core/events/destroyressource.hpp \
    core/events/choosebetweenevents.hpp

win32:LIBS += -L"F:\home\feaisil\Developments\harmony-boardgame\boost\lib" -lboost_serialization-mgw48-mt-1_55 -lboost_system-mgw48-mt-d-1_55 -lboost_thread-mgw48-mt-d-1_55
unix: LIBS += -lboost_serialization -lboost_system -lboost_thread

TARGET = Harmony
