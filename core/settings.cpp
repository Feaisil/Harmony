#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>

#include "settings.hpp"
#include "game.hpp"
#include "DisharmonyCard.hpp"
#include "events/movealltowardselement.hpp"
#include "HarmonyCard.hpp"


namespace harmony{ namespace core{

const std::string Setting::defaultFilePath("harmony.config");
Setting::Setting():
    isParallel(false),

    numberOfPlayers(0),
    boardSize(5),
    distanceFromStart(2),
    startingDisharmonyDraw(0),
    disharmonyDraw(2),
    removedDisharmonyPerPlayer(1),

    harmonyInHand(4),

    startingEnergy(3),
    maxEnergy(15),
    restEnergyRate(3),
    feedingEnergyRate(8),
    feedingBeverageCost(2),
    feedingMealCost(2),
    passiveEnergyResplenishmentRate(1),

    startingBeverage(2),
    maxBeverage(15),
    beverageProductionRate(4),
    beverageProductionEnergyCost(3),

    startingMeal(1),
    maxMeal(15),
    mealProductionRate(3),
    mealProductionEnergyCost(3)
{
    boost::shared_ptr<DisharmonyCard> card(new DisharmonyCard());
    card->name = "Dummy";
    boost::shared_ptr<events::Event> event(new events::MoveAllTowardsElement());
    card->events.push_back(event);
    disharmonyDeckTier1.push_back(card);
}

bool Setting::load()
{
    return load(defaultFilePath);
}

bool Setting::load(const std::string & filePath)
{
    std::ifstream settingsFile;
    settingsFile.open (filePath);
    try
    {
        boost::archive::xml_iarchive arc(settingsFile);
        arc >> boost::serialization::make_nvp("Setting", *this );
    }
    catch(const boost::archive::archive_exception &e)
    {
        // An error occured while decoding the archive, logging to cerr and continuing
        std::cerr << "Failed to read file " << filePath << "! Got archive error: " << e.what() << "." << std::endl;
        return false;
    }
    return true;
}

bool Setting::save()
{
    return save(defaultFilePath);
}

bool  Setting::save(const std::string & filePath)
{
    std::ofstream settingsFile;
    settingsFile.open (filePath);

    boost::archive::xml_oarchive arc(settingsFile);
    arc << boost::serialization::make_nvp("Setting", *this );

    settingsFile.close();
    return true;
}

}}
