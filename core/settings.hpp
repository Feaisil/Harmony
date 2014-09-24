#pragma once

#include <list>
#include <boost/serialization/nvp.hpp>
#include <boost/shared_ptr.hpp>

#include "player.hpp"

namespace harmony{ namespace core{

class PlayerSetting;
class HarmonyCard;
class DisharmonyCard;

class Setting
{
public:
    std::list<boost::shared_ptr<harmony::core::PlayerSetting> > playersSettings;
    bool isParallel;

    int numberOfPlayers;

    int harmonyInHand;
    int boardSize;
    int distanceFromStart;
    int startingDisharmonyDraw;
    int disharmonyDraw;
    int removedDisharmonyPerPlayer;

    int startingEnergy;
    int maxEnergy;
    int restEnergyRate;
    int restBonus;
    int feedingEnergyRate;
    int feedingBeverageCost;
    int feedingMealCost;
    int feedingBonus;
    int passiveEnergyResplenishmentRate;

    int startingBeverage;
    int maxBeverage;
    int beverageProductionRate;
    int beverageProductionEnergyCost;
    int beverageProductionBonusPersonal;
    int beverageProductionBonusShared;
    int beverageProductionBonusSharedOther;

    int startingMeal;
    int maxMeal;
    int mealProductionRate;
    int mealProductionEnergyCost;
    int mealProductionBonusPersonal;
    int mealProductionBonusShared;
    int mealProductionBonusSharedOther;

    int numberOfDisharmonyTier1;
    int numberOfDisharmonyTier2;
    int numberOfDisharmonyTier3;

    std::list<boost::shared_ptr<HarmonyCard>> harmonyDeck;
    std::list<boost::shared_ptr<DisharmonyCard>> disharmonyDeckTier1;
    std::list<boost::shared_ptr<DisharmonyCard>> disharmonyDeckTier2;
    std::list<boost::shared_ptr<DisharmonyCard>> disharmonyDeckTier3;

    static const std::string defaultFilePath;
public:
    Setting();

    bool load();
    bool load(const std::string & filePath);
    bool save();
    bool save(const std::string & filePath);
private:
    void buildDisharmonyDeck();
    void buildHarmonyDeck();
    // Access
    friend class Game;
    friend class Player;
    friend class SettingInterface;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_NVP(playersSettings);
        ar & BOOST_SERIALIZATION_NVP(isParallel);

        ar & BOOST_SERIALIZATION_NVP(numberOfPlayers);

        ar & BOOST_SERIALIZATION_NVP(harmonyInHand);
        ar & BOOST_SERIALIZATION_NVP(boardSize);
        ar & BOOST_SERIALIZATION_NVP(distanceFromStart);
        ar & BOOST_SERIALIZATION_NVP(startingDisharmonyDraw);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDraw);
        ar & BOOST_SERIALIZATION_NVP(removedDisharmonyPerPlayer);

        ar & BOOST_SERIALIZATION_NVP(startingEnergy);
        ar & BOOST_SERIALIZATION_NVP(maxEnergy);
        ar & BOOST_SERIALIZATION_NVP(restEnergyRate);
        ar & BOOST_SERIALIZATION_NVP(restBonus);
        ar & BOOST_SERIALIZATION_NVP(feedingEnergyRate);
        ar & BOOST_SERIALIZATION_NVP(feedingBeverageCost);
        ar & BOOST_SERIALIZATION_NVP(feedingMealCost);
        ar & BOOST_SERIALIZATION_NVP(feedingBonus);
        ar & BOOST_SERIALIZATION_NVP(passiveEnergyResplenishmentRate);

        ar & BOOST_SERIALIZATION_NVP(startingBeverage);
        ar & BOOST_SERIALIZATION_NVP(maxBeverage);
        ar & BOOST_SERIALIZATION_NVP(beverageProductionRate);
        ar & BOOST_SERIALIZATION_NVP(beverageProductionEnergyCost);
        ar & BOOST_SERIALIZATION_NVP(beverageProductionBonusPersonal);
        ar & BOOST_SERIALIZATION_NVP(beverageProductionBonusShared);
        ar & BOOST_SERIALIZATION_NVP(beverageProductionBonusSharedOther);

        ar & BOOST_SERIALIZATION_NVP(startingMeal);
        ar & BOOST_SERIALIZATION_NVP(maxMeal);
        ar & BOOST_SERIALIZATION_NVP(mealProductionRate);
        ar & BOOST_SERIALIZATION_NVP(mealProductionEnergyCost);
        ar & BOOST_SERIALIZATION_NVP(mealProductionBonusPersonal);
        ar & BOOST_SERIALIZATION_NVP(mealProductionBonusShared);
        ar & BOOST_SERIALIZATION_NVP(mealProductionBonusSharedOther);

        ar & BOOST_SERIALIZATION_NVP(harmonyDeck);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDeckTier1);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDeckTier2);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDeckTier3);
    }
};

}}
