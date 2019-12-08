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

#ifndef STYLE_HPP_INCLUDED
#define STYLE_HPP_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <CNGui/Tools/Font.hpp>
#include <CNGui/Tools/Shape.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Color struct for interactive objects
///
////////////////////////////////////////////////////////////
struct InteractiveColor
{
    sf::Color neutral;
    sf::Color hovered;
    sf::Color clicked;

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    InteractiveColor();

    ////////////////////////////////////////////////////////////
    /// \brief Complete constructor
    ///
    /// \param color_neutral Neutral color
    /// \param color_hovered Hovered color
    /// \param color_clicked Clicked color
    ///
    ////////////////////////////////////////////////////////////
    InteractiveColor(sf::Color color_neutral, sf::Color color_hovered, sf::Color color_clicked);

    ////////////////////////////////////////////////////////////
    /// \brief Homogeneous constructor
    ///
    /// \param color Color
    ///
    ////////////////////////////////////////////////////////////
    InteractiveColor(sf::Color color);

    ////////////////////////////////////////////////////////////
    /// \brief Set the same color for all the states
    ///
    /// \param color Color
    ///
    ////////////////////////////////////////////////////////////
    void homogeneous(sf::Color color);
};

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

    //Properties
    bool                selectable;             ///< Enable selectable
    bool                title;                  ///< Enable title label
    bool                outline;                ///< Enable outline
    bool                animation;              ///< Enable animation if exists

    //Main component
    Shape::Type         main_shape;             ///< Shape type of the main component
    sf::Texture         main_texture;           ///< Texture of the main component
    InteractiveColor    main_color;             ///< Color of the main component
    sf::IntRect         main_rect;              ///< Texture rect of the main component

    //Secondary component
    Shape::Type         secondary_shape;        ///< Shape type of the secondary component
    sf::Texture         secondary_texture;      ///< Texture of the secondary component
    InteractiveColor    secondary_color;        ///< Color of the secondary component
    float               secondary_width;        ///< Width of the secondary component
    sf::IntRect         secondary_rect;         ///< Texture rect of the secondary component

    //Background if exists
    Shape::Type         background_shape;       ///< Shape type of the background
    sf::Texture         background_texture;     ///< Texture of the background
    InteractiveColor    background_color;       ///< Color of the background
    sf::IntRect         background_rect;        ///< Texture rect of the background

    //Title label if exists
    sf::Font            title_font;             ///< Font of the title label
    sf::Text::Style     title_style;            ///< Style of the title label
    sf::Uint16          title_size;             ///< Character size of the title label, resized if higher than the height of the object
    InteractiveColor    title_color;            ///< Color of the title label

    //Output label if exists
    sf::Font            output_font;            ///< Font of the output text
    sf::Text::Style     output_style;           ///< Style of the output text
    sf::Uint16          output_size;            ///< Character size of the output text of the object
    InteractiveColor    output_color;           ///< Color of the output label
    char                output_hide;            ///< Hide character of the output

    //Outline if exists
    sf::Uint16          outline_thickness;      ///< Thickness of the outline
    InteractiveColor    outline_color;          ///< Color of the outline

    //Animation if exists
    sf::Time            animation_duration;     ///< Duration of the animation

};

} // namespace CNGui

#endif // STYLE_HPP_INCLUDED
