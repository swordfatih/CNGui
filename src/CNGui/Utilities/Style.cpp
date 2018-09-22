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

#include "CNGui/Utilities/Style.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
Style::Style() :
    shape(Shape::Rectangle),
    charactersize(24),
    fillcolor(sf::Color(249, 159, 93)),
    hovercolor(sf::Color(220, 140, 82)),
    clickedcolor(sf::Color(230, 130, 60)),
    labelcolor(sf::Color(255, 255, 255)),
    labelhovercolor(sf::Color(220, 220, 220)),
    labelclickedcolor(sf::Color(200, 100, 30)),
    selectable(false),
    outline(false),
    outlinethickness(3),
    outlinecolor(sf::Color(150, 150, 150)),
    outlinehovercolor(sf::Color(50, 50, 50)),
    outlineclickedcolor(sf::Color(150, 80, 20)),
    backgroundcolor(sf::Color::Transparent),
    backgroundhovercolor(sf::Color(220, 220, 220)),
    backgroundclickedcolor(sf::Color(155, 155, 155)),
    animated(true),
    label(true)
{
    font.loadFromMemory(Font::BebasNeue::hex, Font::BebasNeue::size);
}

////////////////////////////////////////////////////////////
Style::~Style()
{
    //dtor
}

} // namespace CNGui
