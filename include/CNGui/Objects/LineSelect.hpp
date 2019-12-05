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

#ifndef LINESELECT_HPP
#define LINESELECT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Objects/Object.hpp>
#include <CNGui/Tools/Shape.hpp>
#include <CNGui/Tools/Text.hpp>

//SFML
#include <SFML/Graphics/ConvexShape.hpp>

//Standard
#include <vector>
#include <string>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates an interactive graphical slider
///
////////////////////////////////////////////////////////////
class LineSelect : public Object
{
public:
    ////////////////////////////////////////////////////////////
    using           Object::Object;

    /////////////////////////////////////////////////
    /// \brief Set lines with new ones, this function
    /// overwrites existing lines
    ///
    /// \param lines New vector containing lines
    ///
    /// \see addLines
    /////////////////////////////////////////////////
    void            setLines(std::vector<std::string> lines);

    /////////////////////////////////////////////////
    /// \brief Insert new lines at the end of the
    /// existing container
    ///
    /// \param line Vector containing new lines
    ///
    /// \see setLines
    /////////////////////////////////////////////////
    void            addLines(std::vector<std::string> lines);

    /////////////////////////////////////////////////
    /// \brief Change the selected value, does nothing
    /// if value is out of range
    ///
    /// \param value New value
    ///
    /// \see getValue
    /////////////////////////////////////////////////
    void            setValue(size_t value);

    /////////////////////////////////////////////////
    /// \brief Get the selected value
    ///
    /// \return Selected value
    ///
    /// \see getValue
    /////////////////////////////////////////////////
    size_t          getValue() const;

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
    Shape                       mBackground;    ///< Background
    sf::ConvexShape             mArrowLeft;     ///< Left arrow
    sf::ConvexShape             mArrowRight;    ///< Right arrow
    Text                        mTitle;         ///< Title label
    Text                        mOutput;        ///< Output label
    std::vector<std::string>    mLines;         ///< Value range
    size_t                      mValue = 0;     ///< Selected value
};

} // namespace CNGui

#endif // LINESELECT_HPP
