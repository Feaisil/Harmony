#include "turn.hpp"

#include "events/chooseaction.hpp"
#include "events/checkforendconditions.hpp"
#include "events/DrawDisharmony.hpp"
#include "game.hpp"

namespace harmony{ namespace core{

Turn::Turn(const boost::weak_ptr<Game>& game):
    game(game)
{
}

void Turn::operator ()()
{
    boost::shared_ptr<events::Event> chooseActionEvent(new events::ChooseAction(game, *this));
    (*this) <<( chooseActionEvent);
    processEvents();

    // Todo add end turn processes
    boost::shared_ptr<events::Event> drawDisharmony(new events::DrawDisharmony(game, *this));
    (*this) << (drawDisharmony);
    processEvents();
//    boost::shared_ptr<events::Event> resplenishEnergy(new events::ResplenishEnergy(game, *this));
//    (*this) << (resplenishEnergy);
//    processEvents();

    boost::shared_ptr<events::Event> checkForEnd(new events::CheckForEndConditions(game));
    (*this) << (checkForEnd);
    processEvents();


}
void Turn::processEvents()
{
    while(not remainingEvents.empty())
    {
        remainingEvents.front()->trigger();
        executedEvents.push_back(remainingEvents.front());
        remainingEvents.pop_front();
    }
}

void Turn::operator<<(boost::shared_ptr<events::Event>& event)
{
    remainingEvents.push_back(event);
}

}} //namespaces
