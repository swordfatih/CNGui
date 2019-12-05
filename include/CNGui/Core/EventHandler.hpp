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
class Updatable;

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
    /// \brief Returns the event if the event associated to the
    /// given EventType is active
    ///
    /// \param type The EventType associated with the event
    ///
    /// \return nullptr if the event isn't active
    ///
    ////////////////////////////////////////////////////////////
    sf::Event*  get_if(const sf::Event::EventType& type);

    ////////////////////////////////////////////////////////////
    /// \brief Check if the given event associated to the given
    /// updatable instance is active
    ///
    /// \param updatable Pointer to the updatable
    /// \param event The event to check
    ///
    /// \return bool Returns true if given event is active
    ///
    ////////////////////////////////////////////////////////////
    bool        active(Updatable* updatable, std::string event);

    ////////////////////////////////////////////////////////////
    /// \brief Insert an SFML event
    ///
    /// \param event The event to push
    ///
    ////////////////////////////////////////////////////////////
    void        push(sf::Event event);

    ////////////////////////////////////////////////////////////
    /// \brief Insert an event associated to an updatable instance
    ///
    /// \param updatable Pointer to the updatable
    /// \param event The event to push
    ///
    ////////////////////////////////////////////////////////////
    void        push(Updatable* updatable, std::string event);

    ////////////////////////////////////////////////////////////
    /// \brief Translate (copy) events associated to an updatable
    /// instance to another one
    ///
    /// \param listener Listener instance
    /// \param translator Translator instance
    ///
    ////////////////////////////////////////////////////////////
    void        translate(Updatable* listener, Updatable* translator);

    ////////////////////////////////////////////////////////////
    /// \brief Clear an event associated to an updatable instance
    ///
    ////////////////////////////////////////////////////////////
    void        clear(Updatable* updatable, std::string event);

    ////////////////////////////////////////////////////////////
    /// \brief Clear the events
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
    std::map<sf::Event::EventType, sf::Event>       mEventSf;   ///< Map that holds every events associated to a EventType
    std::map<Updatable*, std::vector<std::string>>  mEventUp;   ///< Map that holds every events associated to an updatable instance
};

} // namespace CNGui

#endif // EVENTHANDLER_HPP
