#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>

#include "settings.hpp"
#include "game.hpp"
#include "disharmonycard.hpp"
#include "events/movetowardselement.hpp"
#include "events/addmodifier.hpp"
#include "events/destroyressource.hpp"
#include "modifier.hpp"
#include "harmonycard.hpp"


namespace harmony{ namespace core{

const std::string Setting::defaultFilePath("harmony.config");
Setting::Setting():
    isParallel(false),

    numberOfPlayers(0),

    harmonyInHand(5),
    boardSize(10),
    distanceFromStart(2),
    startingDisharmonyDraw(0),
    disharmonyDraw(2),
    removedDisharmonyPerPlayer(1),

    startingEnergy(3),
    maxEnergy(15),
    restEnergyRate(3),
    restBonus(2),
    feedingEnergyRate(8),
    feedingBeverageCost(2),
    feedingMealCost(2),
    feedingBonus(4),
    passiveEnergyResplenishmentRate(1),

    startingBeverage(2),
    maxBeverage(15),
    beverageProductionRate(4),
    beverageProductionEnergyCost(3),
    beverageProductionBonusPersonal(3),
    beverageProductionBonusShared(2),
    beverageProductionBonusSharedOther(1),

    startingMeal(1),
    maxMeal(15),
    mealProductionRate(3),
    mealProductionEnergyCost(3),
    mealProductionBonusPersonal(1),
    mealProductionBonusShared(2),
    mealProductionBonusSharedOther(1),


    numberOfDisharmonyTier1(20),
    numberOfDisharmonyTier2(20),
    numberOfDisharmonyTier3(30)

{
    buildDisharmonyDeck();
    buildHarmonyDeck();
}

bool Setting::load()
{
    return true;//load(defaultFilePath);
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
    return true;//save(defaultFilePath);
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

void Setting::buildDisharmonyDeck()
{

    for(int i = 0; i < 10; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Do nothing";
        {

        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="wind";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Beverage 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Beverage;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Meal 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Meal;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Energy 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Energy;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier1.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="wind";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Beverage 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Beverage;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Meal 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Meal;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Energy 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Energy;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire wind";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="wind water";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water aether";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether earth";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth fire";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Wind Fire";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water wind";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether water";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth aether";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire earth";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Beverage 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Beverage;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Meal 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Meal;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Energy 1";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Energy;
                event->power=1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Beverage 2";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Beverage;
                event->power=2;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Meal 2";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Meal;
                event->power=2;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 3; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Energy 2";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Energy;
                event->power=2;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier2.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire wind";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="wind water";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water aether";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether earth";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth fire";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Wind Fire";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water wind";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether water";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth aether";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire earth";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire 2";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="wind 2";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water 2";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether 2";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth 2";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="fire 3";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Fire;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="wind 3";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Wind;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="water 3";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Water;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="aether 3";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Aether;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="earth 3";
        {
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }
            {
                boost::shared_ptr<events::MoveAllTowardsElement> event(new events::MoveAllTowardsElement());
                event->element=core::common::Element::Earth;
                event->negative=true;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Beverage 3";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Beverage;
                event->power=3;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Meal 3";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Meal;
                event->power=3;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Destroy Energy 3";
        {
            {
                boost::shared_ptr<events::DestroyResource> event(new events::DestroyResource());
                event->type=core::events::DestroyType::Energy;
                event->power=3;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Increase costs Energy";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::IncreaseCostsEnergy;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Increase costs Beverage";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::IncreaseCostsBeverage;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Increase coasts Meals";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::IncreaseCostsMeal;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Diminish max cards";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::DiminishMaximumCards;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Produce less Energy";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::ProduceLessEnergyRest;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Produce less Beverage";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::ProduceLessBeverage;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 1; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Produce less Meals";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::ProduceLessMeal;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
    for(int i = 0; i < 2; ++i)
    {
        boost::shared_ptr<DisharmonyCard> disharmonyCard(new DisharmonyCard());
        disharmonyCard->name="Reduce auto rest by 1";
        {
            {
                boost::shared_ptr<events::AddModifierToGame> event(new events::AddModifierToGame());
                event->modifier=core::Modifier::ReduceAutoRestBy1;
                disharmonyCard->events.push_back(boost::static_pointer_cast<core::events::Event>(event));
            }

        }
        disharmonyDeckTier3.push_back(disharmonyCard);
    }
}

void Setting::buildHarmonyDeck()
{
    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire";
        harmonyCard->priority=1;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind";
        harmonyCard->priority=2;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water";
        harmonyCard->priority=3;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether";
        harmonyCard->priority=4;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth";
        harmonyCard->priority=5;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire";
        harmonyCard->priority=6;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=4;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind";
        harmonyCard->priority=7;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=4;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water";
        harmonyCard->priority=8;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=4;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether";
        harmonyCard->priority=9;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=4;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth";
        harmonyCard->priority=10;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=4;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire";
        harmonyCard->priority=11;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind";
        harmonyCard->priority=12;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water";
        harmonyCard->priority=13;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether";
        harmonyCard->priority=14;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth";
        harmonyCard->priority=15;
        harmonyCard->energyCost=0;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire";
        harmonyCard->priority=16;
        harmonyCard->energyCost=1;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind";
        harmonyCard->priority=17;
        harmonyCard->energyCost=1;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water";
        harmonyCard->priority=18;
        harmonyCard->energyCost=1;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether";
        harmonyCard->priority=19;
        harmonyCard->energyCost=1;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth";
        harmonyCard->priority=20;
        harmonyCard->energyCost=1;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire x2";
        harmonyCard->priority=21;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind x2";
        harmonyCard->priority=22;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water x2";
        harmonyCard->priority=23;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether x2";
        harmonyCard->priority=24;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth x2";
        harmonyCard->priority=25;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire wind";
        harmonyCard->priority=26;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind water";
        harmonyCard->priority=27;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water aether";
        harmonyCard->priority=28;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether earth";
        harmonyCard->priority=29;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth fire";
        harmonyCard->priority=30;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=0;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire earth";
        harmonyCard->priority=31;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind fire";
        harmonyCard->priority=32;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water wind";
        harmonyCard->priority=33;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether water";
        harmonyCard->priority=34;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth aether";
        harmonyCard->priority=35;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=0;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="choose fire wind";
        harmonyCard->priority=36;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Fire;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Wind;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Wind;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Fire;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="choose wind water";
        harmonyCard->priority=37;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Water;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Wind;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Wind;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Water;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="choose water aether";
        harmonyCard->priority=38;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Water;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Aether;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Aether;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Water;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="choose aether earth";
        harmonyCard->priority=39;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Earth;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Aether;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Aether;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Earth;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="choose earth fire";
        harmonyCard->priority=40;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Earth;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Fire;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Fire;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::MovePlayerTowardsElement> subsubevent(new events::MovePlayerTowardsElement());
                        subsubevent->element=core::common::Element::Earth;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire wind water";
        harmonyCard->priority=41;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind water aether";
        harmonyCard->priority=42;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water aether earth";
        harmonyCard->priority=43;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether earth fire";
        harmonyCard->priority=44;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth fire wind";
        harmonyCard->priority=45;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="fire earth aether";
        harmonyCard->priority=46;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="wind fire earth";
        harmonyCard->priority=47;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="water wind fire";
        harmonyCard->priority=48;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Fire;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="aether water wind";
        harmonyCard->priority=49;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Wind;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="earth aether water";
        harmonyCard->priority=50;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Earth;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Aether;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
            {
                boost::shared_ptr<events::MovePlayerTowardsElement> event(new events::MovePlayerTowardsElement());
                event->element=core::common::Element::Water;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmony!";
        harmonyCard->priority=51;
        harmonyCard->energyCost=9;
        harmonyCard->beverageCost=7;
        harmonyCard->mealCost=7;
        {

        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmony!";
        harmonyCard->priority=52;
        harmonyCard->energyCost=9;
        harmonyCard->beverageCost=7;
        harmonyCard->mealCost=7;
        {

        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmony!";
        harmonyCard->priority=53;
        harmonyCard->energyCost=9;
        harmonyCard->beverageCost=7;
        harmonyCard->mealCost=7;
        {

        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Farm";
        harmonyCard->priority=54;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::AddModifierToPlayer> subevent(new events::AddModifierToPlayer());
                    subevent->modifier=core::Modifier::ProduceMoreMealPersonal;
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::AddModifierToPlayer> subsubevent(new events::AddModifierToPlayer());
                        subsubevent->modifier=core::Modifier::ProduceMoreMealShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::AddModifierToGame> subsubevent(new events::AddModifierToGame());
                        subsubevent->modifier=core::Modifier::ProduceMoreMealShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Farm";
        harmonyCard->priority=55;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::AddModifierToPlayer> subevent(new events::AddModifierToPlayer());
                    subevent->modifier=core::Modifier::ProduceMoreMealPersonal;
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::AddModifierToPlayer> subsubevent(new events::AddModifierToPlayer());
                        subsubevent->modifier=core::Modifier::ProduceMoreMealShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::AddModifierToGame> subsubevent(new events::AddModifierToGame());
                        subsubevent->modifier=core::Modifier::ProduceMoreMealShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Farm";
        harmonyCard->priority=56;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::AddModifierToPlayer> subevent(new events::AddModifierToPlayer());
                    subevent->modifier=core::Modifier::ProduceMoreMealPersonal;
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::AddModifierToPlayer> subsubevent(new events::AddModifierToPlayer());
                        subsubevent->modifier=core::Modifier::ProduceMoreMealShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::AddModifierToGame> subsubevent(new events::AddModifierToGame());
                        subsubevent->modifier=core::Modifier::ProduceMoreMealShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Breweries";
        harmonyCard->priority=57;
        harmonyCard->energyCost=4;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::AddModifierToPlayer> subevent(new events::AddModifierToPlayer());
                    subevent->modifier=core::Modifier::ProduceMoreBeveragePersonal;
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::AddModifierToPlayer> subsubevent(new events::AddModifierToPlayer());
                        subsubevent->modifier=core::Modifier::ProduceMoreBeverageShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::AddModifierToGame> subsubevent(new events::AddModifierToGame());
                        subsubevent->modifier=core::Modifier::ProduceMoreBeverageShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Breweries";
        harmonyCard->priority=58;
        harmonyCard->energyCost=4;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::AddModifierToPlayer> subevent(new events::AddModifierToPlayer());
                    subevent->modifier=core::Modifier::ProduceMoreBeveragePersonal;
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::AddModifierToPlayer> subsubevent(new events::AddModifierToPlayer());
                        subsubevent->modifier=core::Modifier::ProduceMoreBeverageShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::AddModifierToGame> subsubevent(new events::AddModifierToGame());
                        subsubevent->modifier=core::Modifier::ProduceMoreBeverageShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Breweries";
        harmonyCard->priority=59;
        harmonyCard->energyCost=4;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::ChooseBetweenEvents> event(new events::ChooseBetweenEvents());
                {
                    boost::shared_ptr<events::AddModifierToPlayer> subevent(new events::AddModifierToPlayer());
                    subevent->modifier=core::Modifier::ProduceMoreBeveragePersonal;
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                {
                    boost::shared_ptr<events::MultiplePlayerEvents> subevent(new events::MultiplePlayerEvents());
                    {
                        boost::shared_ptr<events::AddModifierToPlayer> subsubevent(new events::AddModifierToPlayer());
                        subsubevent->modifier=core::Modifier::ProduceMoreBeverageShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    {
                        boost::shared_ptr<events::AddModifierToGame> subsubevent(new events::AddModifierToGame());
                        subsubevent->modifier=core::Modifier::ProduceMoreBeverageShared;
                        subevent->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subsubevent));
                    }
                    event->playerEvents.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(subevent));
                }
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Healing brew";
        harmonyCard->priority=60;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::HealingBrew;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Healing brew";
        harmonyCard->priority=61;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::HealingBrew;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Healing brew";
        harmonyCard->priority=62;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::HealingBrew;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Healing brew";
        harmonyCard->priority=63;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::HealingBrew;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Healing brew";
        harmonyCard->priority=64;
        harmonyCard->energyCost=2;
        harmonyCard->beverageCost=2;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::HealingBrew;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmonious meal";
        harmonyCard->priority=65;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::AddHarmoniousMealAction;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmonious meal";
        harmonyCard->priority=66;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::AddHarmoniousMealAction;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmonious meal";
        harmonyCard->priority=67;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::AddHarmoniousMealAction;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmonious meal";
        harmonyCard->priority=68;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::AddHarmoniousMealAction;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Harmonious meal";
        harmonyCard->priority=69;
        harmonyCard->energyCost=3;
        harmonyCard->beverageCost=1;
        harmonyCard->mealCost=1;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::AddHarmoniousMealAction;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Feather bed";
        harmonyCard->priority=70;
        harmonyCard->energyCost=6;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::RestProduceMoreEnergyPersonal;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Feather bed";
        harmonyCard->priority=71;
        harmonyCard->energyCost=6;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::RestProduceMoreEnergyPersonal;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Feather bed";
        harmonyCard->priority=72;
        harmonyCard->energyCost=6;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=2;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::RestProduceMoreEnergyPersonal;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Kitchen";
        harmonyCard->priority=73;
        harmonyCard->energyCost=5;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::EatProduceMoreEnergyPersonal;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Kitchen";
        harmonyCard->priority=74;
        harmonyCard->energyCost=5;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::EatProduceMoreEnergyPersonal;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }

    {
        boost::shared_ptr<HarmonyCard> harmonyCard(new HarmonyCard());
        harmonyCard->name="Kitchen";
        harmonyCard->priority=75;
        harmonyCard->energyCost=5;
        harmonyCard->beverageCost=3;
        harmonyCard->mealCost=3;
        {
            {
                boost::shared_ptr<events::AddModifierToPlayer> event(new events::AddModifierToPlayer());
                event->modifier=core::Modifier::EatProduceMoreEnergyPersonal;
                harmonyCard->events.push_back(boost::static_pointer_cast<core::events::PlayerEvent>(event));
            }
        }
        harmonyDeck.push_back(harmonyCard);
    }
}
}}
