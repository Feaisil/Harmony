#pragma once

#include "event.hpp"

namespace harmony{ namespace core{ namespace events{

class ChooseBetweenEvents:public PlayerEvent
{
public:
    ChooseBetweenEvents(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, std::vector<boost::shared_ptr<PlayerEvent>> playerEvents);
private:
    virtual void trigger();
    ChooseBetweenEvents(){}
private:
    std::vector<boost::shared_ptr<PlayerEvent>> playerEvents;

private:
    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PlayerEvent);
        ar & BOOST_SERIALIZATION_NVP(playerEvents);
    }
};

}}}
