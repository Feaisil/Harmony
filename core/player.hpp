#pragma once

#include "settings.hpp"
#include "board/position.hpp"
#include "harmonycard.hpp"
#include "modifier.hpp"

#include "interface/playerinterface.hpp"

#include <list>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/list.hpp>

namespace harmony{ namespace core{

namespace events{
class Event;
class HarmoniousMeal;
class MoveAllTowardsElement;
class MovePlayerTowardsElement;
struct DoChooseAction;
class ChooseAction;
class Produce;
class AddModifierToPlayer;
class PlayHarmonyCards;
class DestroyResource;
class CheckForEndConditions;
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
    void serialize(Archive & ar, const unsigned int)
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
    const board::Position& getPosition() const{ return position; }
    int getBeverage() const{ return beverage; }
    int getMeal() const{ return meal; }
    int getEnergy() const{ return energy; }

    const std::vector<Modifier>& getModifiers() const{ return modifiers; }
    const std::vector<boost::shared_ptr<HarmonyCard>>& getPlayerBoard() const{ return playerBoard; }

private:
    board::Position position;
    int energy;
    int beverage;
    int meal;
    int score;
    std::vector<boost::shared_ptr<HarmonyCard>> harmonyHand;
    std::vector<boost::shared_ptr<HarmonyCard>> playerBoard;
    std::vector<Modifier> modifiers;

    PlayerSetting settings;

private:
    friend class events::Event;
    friend class events::HarmoniousMeal;
    friend class events::MoveAllTowardsElement;
    friend class events::MovePlayerTowardsElement;
    friend struct events::DoChooseAction;
    friend class events::ChooseAction;
    friend class events::Produce;
    friend class events::AddModifierToPlayer;
    friend class events::PlayHarmonyCards;
    friend class events::DestroyResource;
    friend class events::CheckForEndConditions;
    friend class Game;
    friend class Engine;
    friend class PlayerInterface;

    Player(){}
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_NVP(position);
        ar & BOOST_SERIALIZATION_NVP(energy);
        ar & BOOST_SERIALIZATION_NVP(beverage);
        ar & BOOST_SERIALIZATION_NVP(meal);
        ar & BOOST_SERIALIZATION_NVP(score);
        ar & BOOST_SERIALIZATION_NVP(harmonyHand);
        ar & BOOST_SERIALIZATION_NVP(playerBoard);
        ar & BOOST_SERIALIZATION_NVP(modifiers);
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
