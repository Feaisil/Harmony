#include "settings.hpp"

#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>

namespace harmony{ namespace core{

const std::string Setting::defaultFilePath("harmony.config");
Setting::Setting():
    isParallel(false),

    harmonyInHand(4),
    boardSize(5),
    distanceFromStart(2),
    numberOfPlayers(0),

    startingEnergy(3),
    maxEnergy(15),
    restEnergyRate(4),
    feedingEnergyRate(8),
    feedingBeverageCost(2),
    feedingMealCost(2),
    passiveEnergyResplenishmentRate(1),

    startingBeverage(1),
    maxBeverage(15),
    beverageProductionRate(5),
    beverageProductionEnergyCost(3),

    startingMeal(1),
    maxMeal(15),
    mealProductionRate(5),
    mealProductionEnergyCost(3),

    EofDisharmony(0)
{}

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
        // An error occured while decoding the archive, logging to cerr and continuins
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
