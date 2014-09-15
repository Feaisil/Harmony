#pragma once

#include "board/board.hpp"
#include "player.hpp"
#include "harmonycard.hpp"
#include "disharmonycard.hpp"
#include "settings.hpp"

#include <list>
#include <memory>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>

namespace harmony{ namespace core{

class Turn;
class Setting;

namespace events{
class Event;
class ChooseAction;
class PureHarmony;
class EliminatePlayers;
class DrawDisharmony;
class MoveAllTowardsElement;
}

class Game
{
public:
    enum class Status
    {
        notStarted,
        ongoing,
        finished,
        lost
    };

    Game(const Setting& settings);
    const std::vector<boost::shared_ptr<Player> > &getEliminatedPlayers() const;
    const std::vector<boost::shared_ptr<Player> > &getPlayers() const;
    const std::list<boost::shared_ptr<DisharmonyCard>> &getDisharmonyDiscard() const;
    const board::Board& getBoard() const;
    Game::Status getStatus() const;

private:
    Setting settings;

    std::vector<boost::shared_ptr<Player>> players;
    std::vector<boost::shared_ptr<Player>> eliminatedPlayers;
    board::Board board;
    std::list<boost::shared_ptr<HarmonyCard>> harmonyDeck;
    std::list<boost::shared_ptr<HarmonyCard>> harmonyDiscard;
    std::list<boost::shared_ptr<DisharmonyCard>> disharmonyDeck;
    std::list<boost::shared_ptr<DisharmonyCard>> disharmonyDiscard;

    Status status;

private:
    friend class Player;
    friend class Engine;
    friend class Turn;
    friend class events::Event;
    friend class events::ChooseAction;
    friend class events::PureHarmony;
    friend class events::EliminatePlayers;
    friend class events::DrawDisharmony;
    friend class events::MoveAllTowardsElement;

    Game(): board(0){}
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(settings);

        ar & BOOST_SERIALIZATION_NVP(players);
        ar & BOOST_SERIALIZATION_NVP(eliminatedPlayers);
        ar & BOOST_SERIALIZATION_NVP(board);
        ar & BOOST_SERIALIZATION_NVP(harmonyDeck);
        ar & BOOST_SERIALIZATION_NVP(harmonyDiscard);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDeck);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDiscard);
    }

};

}}
