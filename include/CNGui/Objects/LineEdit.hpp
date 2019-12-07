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

#ifndef LINEEDIT_HPP
#define LINEEDIT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// CNGui
#include <CNGui/Objects/Object.hpp>
#include <CNGui/Tools/Text.hpp>
#include <CNGui/Tools/Scissors.hpp>

//SFML
#include <SFML/Window/Clipboard.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates a graphical line edit
///
////////////////////////////////////////////////////////////
class LineEdit : public Object
{
public:
    ////////////////////////////////////////////////////////////
    using           Object::Object;

    ////////////////////////////////////////////////////////////
    /// \brief Return key pressed event
    ///
    /// \return Returns true on return key pressed
    ///
    ////////////////////////////////////////////////////////////
    bool            onReturn();

    ////////////////////////////////////////////////////////////
    /// \brief Clear the output string
    ///
    ////////////////////////////////////////////////////////////
    void            clear();

    ////////////////////////////////////////////////////////////
    /// \brief Get the output string
    ///
    /// \return Output string
    ///
    ////////////////////////////////////////////////////////////
    std::string     getString();

    ////////////////////////////////////////////////////////////
    /// \brief Set the default shown string of the text
    ///
    /// \param string Default string
    ///
    ////////////////////////////////////////////////////////////
    void            setDefaultString(const std::string& string);

    ////////////////////////////////////////////////////////////
    /// Overload of operator >> to read object's output
    ///
    ////////////////////////////////////////////////////////////
    LineEdit&       operator >>(std::string& output);

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
    Shape       mShape;                 ///< Underline shape
    Shape       mBackground;            ///< Background shape
    Shape       mCursor;                ///< Cursor shape
    sf::Uint16  mPositionCursor = 0;    ///< Cursor position
    Text        mTitle;                 ///< Title text
    sf::Text    mOutput;                ///< Output text
    std::string mString;                ///< Output string
    std::string mDefault;               ///< Default string
    sf::Clock   mAnimation;             ///< Cursor animation
    bool        mOnReturn = false;      ///< On return key pressed
    bool        mFirst = true;          ///< Not clicked yet

};

} // namespace CNGui

#endif // LINEEDIT_HPP
