/////////////////////////////////////////////////////////////////////////////////
//
// CNGui 1.1 - Chats Noirs Graphical User Interface
// Copyright (c) 2019 Fatih (accfldekur@gmail.com)
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#include <CNGui/Core/EventHandler.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
EventHandler::EventHandler() : Registrable::Registrable(typeid(EventHandler))
{
    //ctor
}

////////////////////////////////////////////////////////////
EventHandler::~EventHandler()
{
    //dtor
}

////////////////////////////////////////////////////////////
sf::Event* EventHandler::get_if(const sf::Event::EventType& type)
{
    if(mEventSf.find(type) != mEventSf.end())
    {
        return &mEventSf[type];
    }

    return nullptr;
}

////////////////////////////////////////////////////////////
bool EventHandler::active(Updatable* updatable, std::string event)
{
    auto&& events = mEventUp[std::move(updatable)];

    return std::find(events.begin(), events.end(), std::move(event)) != events.end();
}

////////////////////////////////////////////////////////////
void EventHandler::push(sf::Event event)
{
    mEventSf[event.type] = std::move(event);
}

////////////////////////////////////////////////////////////
void EventHandler::push(Updatable* updatable, std::string event)
{
    mEventUp[std::move(updatable)].push_back(std::move(event));
}

////////////////////////////////////////////////////////////
void EventHandler::translate(Updatable* listener, Updatable* translator)
{
    auto&& listener_events = mEventUp[std::move(listener)];
    auto&& translator_events = mEventUp[std::move(translator)];

    listener_events.insert(listener_events.end(), translator_events.begin(), translator_events.end());
}

////////////////////////////////////////////////////////////
void EventHandler::clear(Updatable* updatable, std::string event)
{
    auto&& events = mEventUp[std::move(updatable)];
    events.erase(std::find(events.begin(), events.end(), std::move(event)));
}

////////////////////////////////////////////////////////////
void EventHandler::clear()
{
    mEventSf.clear();
    mEventUp.clear();
}

////////////////////////////////////////////////////////////
void EventHandler::process(sf::Window& window)
{
    clear();

    sf::Event event;
    while(window.pollEvent(event))
    {
        push(event);
    }
}


} // namespace CNGui
