#pragma once

#include <list>
#include <boost/serialization/nvp.hpp>
#include <boost/shared_ptr.hpp>

#include "player.hpp"

namespace harmony{ namespace core{

class PlayerSetting;

class Setting
{
    // TODO DELETE public
public:
    std::list<boost::shared_ptr<harmony::core::PlayerSetting> > playersSettings;
    bool isParallel;

    short harmonyInHand;
    short boardSize;
    short distanceFromStart;
    short numberOfPlayers;


    short startingEnergy;
    short maxEnergy;
    short restEnergyRate;
    short feedingEnergyRate;
    short feedingBeverageCost;
    short feedingMealCost;
    short passiveEnergyResplenishmentRate;

    short startingBeverage;
    short maxBeverage;
    short beverageProductionRate;
    short beverageProductionEnergyCost;

    short startingMeal;
    short maxMeal;
    short mealProductionRate;
    short mealProductionEnergyCost;

    short EofDisharmony; // ?

    static const std::string defaultFilePath;
public:
    Setting();

    bool load();
    bool load(const std::string & filePath);
    bool save();
    bool save(const std::string & filePath);

    // Access
    friend class Game;
    friend class Player;
    friend class SettingInterface;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(playersSettings);
        ar & BOOST_SERIALIZATION_NVP(isParallel);

        ar & BOOST_SERIALIZATION_NVP(harmonyInHand);
        ar & BOOST_SERIALIZATION_NVP(boardSize);
        ar & BOOST_SERIALIZATION_NVP(distanceFromStart);
        ar & BOOST_SERIALIZATION_NVP(numberOfPlayers);


        ar & BOOST_SERIALIZATION_NVP(startingEnergy);
        ar & BOOST_SERIALIZATION_NVP(maxEnergy);
        ar & BOOST_SERIALIZATION_NVP(restEnergyRate);
        ar & BOOST_SERIALIZATION_NVP(feedingEnergyRate);
        ar & BOOST_SERIALIZATION_NVP(feedingBeverageCost);
        ar & BOOST_SERIALIZATION_NVP(feedingMealCost);
        ar & BOOST_SERIALIZATION_NVP(passiveEnergyResplenishmentRate);

        ar & BOOST_SERIALIZATION_NVP(startingBeverage);
        ar & BOOST_SERIALIZATION_NVP(maxBeverage);
        ar & BOOST_SERIALIZATION_NVP(beverageProductionRate);
        ar & BOOST_SERIALIZATION_NVP(beverageProductionEnergyCost);

        ar & BOOST_SERIALIZATION_NVP(startingMeal);
        ar & BOOST_SERIALIZATION_NVP(maxMeal);
        ar & BOOST_SERIALIZATION_NVP(mealProductionRate);
        ar & BOOST_SERIALIZATION_NVP(mealProductionEnergyCost);

        ar & BOOST_SERIALIZATION_NVP(EofDisharmony); // ?
    }
};

}}
