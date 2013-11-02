#include "turn.hpp"

#include "events/chooseaction.hpp"
#include "game.hpp"

namespace harmony{ namespace core{

Turn::Turn(Game & game, unsigned int id):
    id(id),
    game(game)
{
    std::shared_ptr<events::Event> chooseActionEvent(new events::ChooseAction(game, *this));
    (*this) <<  chooseActionEvent;
}

void Turn::operator ()()
{
    while(not remainingEvents.empty())
    {
        remainingEvents.front()->trigger();
        executedEvents.push_back(remainingEvents.front());
        remainingEvents.pop();
    }
    // Todo disharmony
}
void Turn::operator<<(std::shared_ptr<events::Event>& event)
{
    remainingEvents.push(event);
}

//std::ostream& operator<< (std::ostream& stream, const ::harmony::core::Turn & turn)
//{
//    stream << "{ /*remainingEvents : "
//           << turn.remainingEvents
//           << " | executedEvents : "
//           << turn.executedEvents
//           << " }*/";

//    return stream;
//}

}} //namespaces
