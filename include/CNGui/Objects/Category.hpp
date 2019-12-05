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

#ifndef CATEGORY_HPP
#define CATEGORY_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Objects/Object.hpp>
#include <CNGui/Tools/Shape.hpp>
#include <CNGui/Tools/Text.hpp>

//SFML
#include <SFML/Graphics/ConvexShape.hpp>

namespace CNGui
{

////////////////////////////////////////////////////////////
/// \brief Class that creates a graphical category that can
/// hold a container
///
////////////////////////////////////////////////////////////
class Category : public Object
{
public:
    ////////////////////////////////////////////////////////////
    using           Object::Object;

    /////////////////////////////////////////////////
    /// \brief Get the internal container
    ///
    /// \return A reference to the internal container
    ///
    /////////////////////////////////////////////////
    Container&      internal();

    /////////////////////////////////////////////////
    /// \brief Get the state of the category
    ///
    /// \return State of the category
    ///
    /////////////////////////////////////////////////
    bool            state() const;

private:
    ////////////////////////////////////////////////////////////
    /// \brief Initialize the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void initialize();

    ////////////////////////////////////////////////////////////
    /// \brief Stylize the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void stylize();

    ////////////////////////////////////////////////////////////
    /// \brief Manage the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void manage();

    ////////////////////////////////////////////////////////////
    /// \brief Draw the object to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Shape           mBackground;        ///< Background shape
    sf::ConvexShape mArrow;             ///< Arrow shape
    Text            mTitle;             ///< Title text
    sf::Vector2f    mSizeClosed;        ///< Size of the category when closed
    Container       mContainer;         ///< Internal container

};

} // namespace CNGui

#endif // CATEGORY_HPP
