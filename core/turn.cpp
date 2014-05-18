#include "turn.hpp"

#include "events/chooseaction.hpp"
#include "game.hpp"

namespace harmony{ namespace core{

Turn::Turn(Game& game)
{
    boost::shared_ptr<events::Event> chooseActionEvent(new events::ChooseAction(game, *this));
    (*this) <<( chooseActionEvent);
}

void Turn::operator ()()
{
    while(not remainingEvents.empty())
    {
        remainingEvents.front()->trigger();
        executedEvents.push_back(remainingEvents.front());
        remainingEvents.pop_front();
    }
    // Todo disharmony
}
void Turn::operator<<(boost::shared_ptr<events::Event>& event)
{
    remainingEvents.push_back(event);
}

}} //namespaces
