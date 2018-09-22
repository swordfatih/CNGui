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

#ifndef STYLE_HPP_INCLUDED
#define STYLE_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Font.hpp>
#include "CNGui/Utilities/Font.hpp"
#include "CNGui/Utilities/Shape.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Utility struct for manipulating object styles
///
////////////////////////////////////////////////////////////
struct Style
{
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructs an empty style
    ///
    ////////////////////////////////////////////////////////////
            Style();

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Style();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Shape::Type shape;                  ///< Shape of the object
    sf::Uint16  charactersize;          ///< Character size of the label, resized if higher than the height of the object
    sf::Font    font;                   ///< Font of the label
    sf::Color   fillcolor;              ///< Color of the object
    sf::Color   hovercolor;             ///< Color of the object when hovering
    sf::Color   clickedcolor;           ///< Color of the object on click
    sf::Color   labelcolor;             ///< Color of the label
    sf::Color   labelhovercolor;        ///< Color of the label when hovering
    sf::Color   labelclickedcolor;      ///< Color of the label on click
    bool        selectable;             ///< The object is selectable
    bool        outline;                ///< The object has an outline
    sf::Uint16  outlinethickness;       ///< Thickness of the outline
    sf::Color   outlinecolor;           ///< Color of the outline
    sf::Color   outlinehovercolor;      ///< Color of the outline when hovering
    sf::Color   outlineclickedcolor;    ///< Color of the outline on click
    sf::Color   backgroundcolor;        ///< Color of the background of the object
    sf::Color   backgroundhovercolor;   ///< Color of the background of the object when hovering
    sf::Color   backgroundclickedcolor; ///< Color of the background of the object on click
    bool        animated;               ///< The object is animated if it is possible
    bool        label;                  ///< The label of the object is shown
};

} // namespace CNGui

#endif // STYLE_HPP_INCLUDED
