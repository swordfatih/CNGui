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

#ifndef BUTTON_HPP
#define BUTTON_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "CNGui/Objects/Object.hpp"
#include "CNGui/Utilities/Shape.hpp"
#include <SFML/Graphics/Text.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates a graphical button
///
////////////////////////////////////////////////////////////
class Button : public Object
{
public:
    using Object::Object;

    ////////////////////////////////////////////////////////////
    /// \brief Click event
    ///
    /// \return Returns true on button click
    ///
    ////////////////////////////////////////////////////////////
    bool onClick();

    ////////////////////////////////////////////////////////////
    /// \brief Hover event
    ///
    /// \return Returns true when button hovered
    ///
    ////////////////////////////////////////////////////////////
    bool onHover();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Updates the object
    ///
    ////////////////////////////////////////////////////////////
    void update();

    ////////////////////////////////////////////////////////////
    /// \brief Draw the button to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Shape           mShape;             ///< Shape of the button
    sf::Text        mLabel;             ///< Label of the button
    bool            mClicked = false;   ///< Button clicked
    bool            mHover = false;     ///< Hovering the button
};

}

#endif // BUTTON_HPP
