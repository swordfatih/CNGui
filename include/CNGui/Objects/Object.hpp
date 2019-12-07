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

#ifndef OBJECT_HPP
#define OBJECT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Core/Updatable.hpp>
#include <CNGui/Core/Style.hpp>
#include <CNGui/Core/Container.hpp>
#include <CNGui/Tools/FunctionWrapper.hpp>

//SFML
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

//Standard
#include <assert.h>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Base class for objects
///
////////////////////////////////////////////////////////////
class Object : public Updatable, public sf::Drawable, public Core::Registrable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
                    Object(const std::string& name = "Object", const Style& style = {}, const sf::Vector2f& size = sf::Vector2f(100, 50));

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual         ~Object();

    ////////////////////////////////////////////////////////////
    /// \brief Set the style of the object
    ///
    /// \param style Style of the object
    ///
    /// \see getStyle
    ///
    ////////////////////////////////////////////////////////////
    void            setStyle(const Style& style);

    ////////////////////////////////////////////////////////////
    /// \brief Get the style of the object
    ///
    /// \return The style of the object
    ///
    /// \see setStyle
    ///
    ////////////////////////////////////////////////////////////
    Style&          getStyle();

    ////////////////////////////////////////////////////////////
    /// \brief Set the name of the object
    ///
    /// \param name Name of the object
    ///
    /// \see getName
    ///
    ////////////////////////////////////////////////////////////
    void            setName(const std::string& name);

    ////////////////////////////////////////////////////////////
    /// \brief Get the name of the object
    ///
    /// \return The name of the object
    ///
    /// \see setName
    ///
    ////////////////////////////////////////////////////////////
    std::string     getName();

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the object
    ///
    /// \param size Size of the object
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void            setSize(const sf::Vector2f& size);

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the object
    ///
    /// \return The size of the object
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f    getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the global bounding rectangle of the object
    ///
    /// \return Bounding rectangle of the object
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect   getGlobalBounds() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the local bounding rectangle of the object
    /// Without the inherited position
    ///
    /// \return Bounding rectangle of the object
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect   getLocalBounds() const;

    ///////////////////////////////////////////////////////////
    /// Overload of operator << to change the name of the object
    ///
    ////////////////////////////////////////////////////////////
    Object&         operator <<(const std::string& name);

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool            operator()();

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the mouse position
    /// and to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool            operator()(const sf::Vector2f& mouse);

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the mouse position
    /// and to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool            operator()(const sf::RenderWindow& window);

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the mouse position
    /// and to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool            operator()(const sf::RenderWindow& window, const sf::View& view);

    ///////////////////////////////////////////////////////////
    /// Overload of operator () to get the mouse position
    /// and to get the object's return value
    ///
    ////////////////////////////////////////////////////////////
    bool            operator()(const sf::Vector2i& mouse);

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Overload this function to initialize the object
    /// It's thought to be called only once
    ///
    ////////////////////////////////////////////////////////////
    virtual void initialize();

    ////////////////////////////////////////////////////////////
    /// \brief Overload this function to update the style of the
    /// object
    ///
    ////////////////////////////////////////////////////////////
    virtual void stylize();

    ////////////////////////////////////////////////////////////
    /// \brief Overload this function to update the logic of the
    /// object
    ///
    ////////////////////////////////////////////////////////////
    virtual void manage();

    ////////////////////////////////////////////////////////////
    /// \brief Update the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void update() final;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::string     mName;          ///< Name of the object
    sf::Vector2f    mSize;          ///< Size of the object
    Style           mStyle;         ///< Style of the object
    bool            mUpdate;        ///< Needs update?
    bool            mReturn;        ///< Bool conversion value
    bool            mInitialized;   ///< If initialized
    sf::Vector2f    mMouse;         ///< Mouse position
};

namespace Core
{

////////////////////////////////////////////////////////////
void draw(sf::RenderTarget& target);

} // namespace Core

} // namespace CNGui

#endif // OBJECT_HPP
