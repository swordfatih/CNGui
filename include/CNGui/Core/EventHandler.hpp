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

#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Core/Registration.hpp>

//SFML
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

//Standard
#include <map>

namespace CNGui
{

////////////////////////////////////////////////////////////
/// \brief Class that holds SFML events that can be useless
/// further in the code
///
////////////////////////////////////////////////////////////
class EventHandler : public Core::Registrable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
                EventHandler();

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual     ~EventHandler();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the event if the event associated to the given
    /// EventType is active
    ///
    /// \param type The EventType associated with the event
    ///
    /// \return nullptr if the event isn't active
    ///
    ////////////////////////////////////////////////////////////
    sf::Event*  get_if(const sf::Event::EventType& type);

    ////////////////////////////////////////////////////////////
    /// \brief Insert an event to the map
    ///
    /// \param event The event to push
    ///
    ////////////////////////////////////////////////////////////
    void        push(sf::Event event);

    ////////////////////////////////////////////////////////////
    /// \brief Clear the event map
    ///
    ////////////////////////////////////////////////////////////
    void        clear();

    ////////////////////////////////////////////////////////////
    /// \brief Process all events
    ///
    /// \param window Window used to poll events
    ///
    ////////////////////////////////////////////////////////////
    void        process(sf::Window& window);

protected:

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::map<sf::Event::EventType, sf::Event>   mEventMap;  ///< Map that holds every events

};

} // namespace CNGui

#endif // EVENTHANDLER_HPP
