#include "CNGui/Utilities/EventHandler.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
EventHandler::EventHandler()
{
    //ctor
}

////////////////////////////////////////////////////////////
EventHandler::~EventHandler()
{
    //dtor
}

////////////////////////////////////////////////////////////
sf::Event& EventHandler::operator[] (const sf::Event::EventType& type)
{
	return mEventMap[type];
}

////////////////////////////////////////////////////////////
bool EventHandler::isActive(const sf::Event::EventType& type)
{
    return mEventMap.find(type) != mEventMap.end();
}

////////////////////////////////////////////////////////////
void EventHandler::push(const sf::Event& event)
{
    mEventMap[event.type] = event;
}

////////////////////////////////////////////////////////////
void EventHandler::clear()
{
    mEventMap.clear();
}

} // namespace CNGui
