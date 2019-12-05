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

#ifndef POSTER_HPP
#define POSTER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Objects/Object.hpp>
#include <CNGui/Tools/Shape.hpp>
#include <CNGui/Tools/Text.hpp>
#include <CNGui/Tools/Easing.hpp>
#include <CNGui/Tools/Scissors.hpp>

//SFML
#include <SFML/Graphics/Sprite.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates a poster
///
////////////////////////////////////////////////////////////
class Poster : public Object
{
public:
    ////////////////////////////////////////////////////////////
    using           Object::Object;

    ////////////////////////////////////////////////////////////
    /// \brief Hover event
    ///
    /// \return Returns true when poster hovered
    ///
    ////////////////////////////////////////////////////////////
    bool            onHover();

    ////////////////////////////////////////////////////////////
    /// \brief Set the description of the poster
    ///
    /// \param description Description of the poster
    ///
    /// \see getDescription
    ///
    ////////////////////////////////////////////////////////////
    void            setDescription(const std::string& description);

    ////////////////////////////////////////////////////////////
    /// \brief Get the description of the poster
    ///
    /// \return Description of the poster
    ///
    /// \see setDescription
    ///
    ////////////////////////////////////////////////////////////
    std::string     getDescription();

    ////////////////////////////////////////////////////////////
    /// \brief Set the date of the poster
    ///
    /// \param date Date of the poster
    ///
    /// \see getDate
    ///
    ////////////////////////////////////////////////////////////
    void            setDate(const std::string& date);

    ////////////////////////////////////////////////////////////
    /// \brief Get the date of the poster
    ///
    /// \return Description of the poster
    ///
    /// \see setDate
    ///
    ////////////////////////////////////////////////////////////
    std::string     getDate();

private:
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
    sf::Sprite      mSprite;        ///< Sprite of the poster
    Shape           mBackground;    ///< Background of the poster
    Shape           mLine;          ///< Separation line
    Text            mTitle;         ///< Title of the poster
    Text            mDate;          ///< Date of the poster
    Text            mDescription;   ///< Description of the poster
    bool            mHover = false; ///< Hovering the poster
    float           mAnimation = 0; ///< Hovering animation
    sf::Clock       mClock;         ///< Animation clock
};

} // namespace CNGui

#endif // BUTTON_HPP
