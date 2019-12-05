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

#include <CNGui/Core/Style.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
InteractiveColor::InteractiveColor()
{

}

////////////////////////////////////////////////////////////
InteractiveColor::InteractiveColor(sf::Color color_neutral, sf::Color color_hovered, sf::Color color_clicked)
{
    neutral = std::move(color_neutral);
    hovered = std::move(color_hovered);
    clicked = std::move(color_clicked);
}

////////////////////////////////////////////////////////////
InteractiveColor::InteractiveColor(sf::Color color)
{
    homogeneous(std::move(color));
}

////////////////////////////////////////////////////////////
void InteractiveColor::homogeneous(sf::Color color)
{
    neutral = std::move(color);
    hovered = clicked = neutral;
}

////////////////////////////////////////////////////////////
Style::Style() :
    selectable(false),
    title(true),
    outline(false),
    animation(true),

    main_shape(Shape::Rectangle),
    main_color({200, 200, 200}, {100, 100, 100}, {230, 130, 60}),

    secondary_shape(Shape::Rectangle),
    secondary_color({200, 200, 200}, {100, 100, 100}, {230, 130, 60}),
    secondary_width(8),

    background_shape(Shape::Rectangle),
    background_color(sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent),

    title_style(sf::Text::Regular),
    title_size(24),
    title_color({255, 255, 255}, {220, 220, 220}, {200, 100, 30}),

    output_style(sf::Text::Regular),
    output_size(16),
    output_color({255, 255, 255}, {220, 220, 220}, {200, 100, 30}),
    output_hide(' '),

    outline_thickness(3),
    outline_color({150, 150, 150}, {50, 50, 50}, {150, 80, 20}),

    animation_duration(sf::seconds(2))
{
    title_font.loadFromMemory(Font::BebasNeue::hex, Font::BebasNeue::size);
    output_font.loadFromMemory(Font::BebasNeue::hex, Font::BebasNeue::size);
}

////////////////////////////////////////////////////////////
Style::~Style()
{
    //dtor
}

} // namespace CNGui
