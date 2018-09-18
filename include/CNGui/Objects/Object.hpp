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

#ifndef OBJECT_HPP
#define OBJECT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "CNGui/Utilities/Style.hpp"
#include "CNGui/Utilities/EventHandler.hpp"
#include <assert.h>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Base class for objects
///
////////////////////////////////////////////////////////////
class Object : public sf::Drawable, public sf::Transformable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
                Object(const std::string& id, EventHandler& handleEvent, Style& style, const sf::Vector2f& size = sf::Vector2f(0, 0));

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual     ~Object();

    ////////////////////////////////////////////////////////////
    /// \brief Set the style of the shape
    ///
    /// \param style Style of the shape
    ///
    /// \see getStyle
    ///
    ////////////////////////////////////////////////////////////
    void            setStyle(Style& style);

    ////////////////////////////////////////////////////////////
    /// \brief Get the style of the shape
    ///
    /// \return The style of the shape
    ///
    /// \see setStyle
    ///
    ////////////////////////////////////////////////////////////
    Style&          getStyle();

    ////////////////////////////////////////////////////////////
    /// \brief Set the id of the shape
    ///
    /// \param id Id of the shape
    ///
    /// \see getId
    ///
    ////////////////////////////////////////////////////////////
    void            setId(const std::string& id);

    ////////////////////////////////////////////////////////////
    /// \brief Get the id of the shape
    ///
    /// \return The id of the shape
    ///
    /// \see setId
    ///
    ////////////////////////////////////////////////////////////
    std::string     getId();

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the shape
    ///
    /// \param size Size of the shape
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void            setSize(const sf::Vector2f& size);

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the shape
    ///
    /// \return The size of the shape
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f    getSize();

    ////////////////////////////////////////////////////////////
    /// \brief Set the container of the object
    ///
    /// \param position Position of the container
    ///
    ////////////////////////////////////////////////////////////
    void            setContainer(sf::Vector2f& position);

    ///////////////////////////////////////////////////////////
    /// Overload of operator << to change the name of the object
    ///
    ////////////////////////////////////////////////////////////
    Object&     operator <<(const std::string& name);

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool        operator()();

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the mouse position
    /// and to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool        operator()(const sf::Vector2f& mouse);

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the mouse position
    /// and to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool        operator()(const sf::RenderWindow& window);

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the mouse position
    /// and to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool        operator()(const sf::Vector2i& mouse);

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Set the event handler of the shape
    ///
    /// \param handleEvent Event handler of the shape
    ///
    /// \see getEventHandler
    ///
    ////////////////////////////////////////////////////////////
    void            setEventHandler(EventHandler& handleEvent);

    ////////////////////////////////////////////////////////////
    /// \brief Get the event handler of the shape
    ///
    /// \return The event handler of the shape
    ///
    /// \see setEventHandler
    ///
    ////////////////////////////////////////////////////////////
    EventHandler&   getEventHandler();

    ////////////////////////////////////////////////////////////
    /// \brief Parse an id to an index and name
    ///
    /// \param id Id to parse
    /// \param index Index of the id to update
    /// \param name Name of the id to update
    ///
    ////////////////////////////////////////////////////////////
    void            parse(const std::string& id, sf::Uint16& index, std::string& name);

    ////////////////////////////////////////////////////////////
    /// \brief Draw the object to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    /// \brief Updates the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void    update();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Uint16      mIndex;         ///< Index of the object
    std::string     mName;          ///< Name of the object
    sf::Vector2f    mSize;          ///< Size of the object
    EventHandler&   mHandleEvent;   ///< Event handler
    Style&          mStyle;         ///< Style of the object
    bool            mUpdate;        ///< Needs update?
    bool            mReturn;        ///< Bool conversion value
    sf::Vector2f    mMouse;         ///< Mouse position
    sf::Vector2f*   mContainer;     ///< Position of the container that contains it
};

} // namespace CNGui

#endif // OBJECT_HPP
