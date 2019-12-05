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

#ifndef UPDATABLE_HPP_INCLUDED
#define UPDATABLE_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Core/EventHandler.hpp>
#include <CNGui/Core/Registration.hpp>

//SFML
#include <SFML/Graphics/Transformable.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Base class for updatable classes, keeping in
/// memory the position of the parent container if is
/// contained by any
///
////////////////////////////////////////////////////////////
class Updatable : public sf::Transformable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ////////////////////////////////////////////////////////////
                    Updatable();

    ////////////////////////////////////////////////////////////
    /// \brief Default virtual destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual         ~Updatable();

    ////////////////////////////////////////////////////////////
    /// \brief Set the inheritance of the class
    ///
    /// \param contained If it is contained
    /// \param position Inherited position
    /// \param parent Pointer to the parent instance
    ///
    /// \see isContained
    ///
    ////////////////////////////////////////////////////////////
    void            setInheritance(bool contained, Updatable* parent = nullptr, const sf::Vector2f& position = {0, 0});

    ////////////////////////////////////////////////////////////
    /// \brief If the class is contained by another
    ///
    /// \see setInheritance
    ///
    ////////////////////////////////////////////////////////////
    bool            isContained() const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload this function to update internally your
    /// class
    ///
    ////////////////////////////////////////////////////////////
    virtual void    update();

protected:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Updatable*      mParent = nullptr;              ///< Parent container
    bool            mContained = false;             ///< Contained
    sf::Vector2f    mInPosition = {0, 0};           ///< Inherited position
    EventHandler&   mHandleEvent;                   ///< Event handler
    sf::FloatRect   mDisplayArea = {0, 0, 0, 0};    ///< Display area

};

} // namespace CNGui


#endif // UPDATABLE_HPP_INCLUDED
