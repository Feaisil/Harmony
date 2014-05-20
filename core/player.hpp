#pragma once

#include "board/position.hpp"
#include "harmonycard.hpp"

#include <list>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/serialization/list.hpp>

namespace harmony{ namespace core{

class Game;
namespace events{
class Event;
class PureHarmony;
}

struct PlayerSettings
{

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    { 
    }
};

class Player
{
public:
    Player();

private:
    board::Position position;
    std::list<boost::shared_ptr<HarmonyCard>> harmonyDeck;
    std::list<boost::shared_ptr<HarmonyCard>> playerBoard;
    int money;
    int stock;
    PlayerSettings settings;

    friend class events::Event;
    friend class events::PureHarmony;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(position);
	ar & BOOST_SERIALIZATION_NVP(harmonyDeck);
	ar & BOOST_SERIALIZATION_NVP(playerBoard);
	ar & BOOST_SERIALIZATION_NVP(money);
	ar & BOOST_SERIALIZATION_NVP(stock);
	ar & BOOST_SERIALIZATION_NVP(settings);
    }

};

template <typename Functor, bool isParallel = false>
struct SimultaneousQuery
{
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
};

}}
