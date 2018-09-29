/////////////////////////////////////////////////////////////////////////////////
//
// CNGui - Chats Noirs Graphical User Interface
// Copyright (c) 2018 Fatih (accfldekur@gmail.com)
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

#include <CNGui/Utilities/EventHandler.hpp>

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
