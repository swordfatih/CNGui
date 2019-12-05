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

#ifndef BOX_HPP
#define BOX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Objects/Object.hpp>
#include <CNGui/Tools/Shape.hpp>
#include <CNGui/Tools/Text.hpp>
#include <CNGui/Tools/Scissors.hpp>

namespace CNGui
{
/////////////////////////////////////////////////////////////////////////////////
class Box : public Object
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
    /// \brief Returns a point outside the internal
    /// container if the box's bounds don't contain
    /// the given position, else doesn't do anything
    ///
    /// \param position Position to crop
    ///
    /// \return Cropped position
    ///
    /////////////////////////////////////////////////
    sf::Vector2f    crop_position(const sf::Vector2f& position);

    /////////////////////////////////////////////////
    /// \brief Set the state of the vertical scroll
    ///
    /// \param state State of the vertical scroll
    ///
    /////////////////////////////////////////////////
    void            setVertical(bool state);

    /////////////////////////////////////////////////
    /// \brief Set the state of the horizontal scroll
    ///
    /// \param state State of the horizontal scroll
    ///
    /////////////////////////////////////////////////
    void            setHorizontal(bool state);

private:
    ////////////////////////////////////////////////////////////
    /// \brief Stylize the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void    stylize();

    ////////////////////////////////////////////////////////////
    /// \brief Manage the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void    manage();

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
    Text            mTitle;                         ///< Title of the box
    Shape           mBackgroundTitle;               ///< Background of the title
    Shape           mShape;                         ///< Box main shape
    Shape           mVerticalScroll;                ///< Vertical scroll
    Shape           mVerticalBackground;            ///< Vertical scroll's background
    Shape           mHorizontalScroll;              ///< Horizontal scroll
    Shape           mHorizontalBackground;          ///< Horizontal scroll's background
    Container       mContainer;                     ///< Internal container
    float           mPositionClick;                 ///< First click position
    bool            mVertical = true;               ///< Vertical scrolling
    bool            mHorizontal = true;             ///< Horizontal scrolling
    bool            mScrollingVertical = false;     ///< Scrolling vertical state
    bool            mScrollingHorizontal = false;   ///< Scrolling horizontal state
};

} // namespace CNGui

#endif // BOX_HPP
