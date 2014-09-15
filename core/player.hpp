#pragma once

#include "settings.hpp"
#include "board/position.hpp"
#include "harmonycard.hpp"

#include "interface/playerinterface.hpp"

#include <list>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/list.hpp>

namespace harmony{ namespace core{

namespace events{
class Event;
class PureHarmony;
class MoveAllTowardsElement;
}

namespace interface{
class PlayerInterface;
}

class Player;
class Game;
class Setting;

class PlayerSetting
{
public:
    PlayerSetting(interface::PlayerInterface* interface);
    std::string name;
    common::Element element;

    const interface::PlayerInterface* interface;
private:
    friend class SettingInterface;
    friend class Player;

    PlayerSetting(){}
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(name);
        ar & BOOST_SERIALIZATION_NVP(element);
    }
};

class Player
{
public:
    Player(const Setting &settings, const PlayerSetting &playerSettings);

    const PlayerSetting& accessSettings() const{ return settings; }
    const board::Position& getPosition() const;
private:
    board::Position position;
    std::list<boost::shared_ptr<HarmonyCard>> harmonyDeck;
    std::list<boost::shared_ptr<HarmonyCard>> playerBoard;
    short energy;
    short beverage;
    short meal;
    short score;

    PlayerSetting settings;

    friend class events::Event;
    friend class events::PureHarmony;
    friend class events::MoveAllTowardsElement;
    friend class Game;
    friend class Engine;
    friend class PlayerInterface;

    Player(){}
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(position);
        ar & BOOST_SERIALIZATION_NVP(harmonyDeck);
        ar & BOOST_SERIALIZATION_NVP(playerBoard);
        ar & BOOST_SERIALIZATION_NVP(energy);
        ar & BOOST_SERIALIZATION_NVP(beverage);
        ar & BOOST_SERIALIZATION_NVP(meal);
        ar & BOOST_SERIALIZATION_NVP(settings);
    }

};

template <typename Functor>
struct SimultaneousQuery
{
    SimultaneousQuery(bool isParallel = false):isParallel(isParallel){}

    std::vector<typename Functor::_returnType > operator()(std::vector<boost::shared_ptr<Player> > &players, typename Functor::_argumentType& argument)
    {
        std::vector<typename Functor::_returnType > result;
        result.assign(players.size(), typename Functor::_returnType() );
        boost::thread_group threads;
        for(size_t index = 0; index < players.size(); ++index)
        {
            if(not isParallel)
            {
                this->operator ()(index, players[index], argument, &result);
            }
            else
            {
                threads.add_thread(new boost::thread(*this, index, players[index], argument, &result));
            }
        }
        if(isParallel)
        {
            threads.join_all();
        }
        return result;
    }
    void operator()(size_t index, boost::shared_ptr<Player> &player, typename Functor::_argumentType& argument, std::vector<typename Functor::_returnType > *result)
    {
        Functor f;
        (*result)[index] = f(player, argument);
    }
private:
    const bool isParallel;
};

}}
