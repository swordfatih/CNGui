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
    outlineclickedcolor(sf::Color(150, 80, 20))
{
    font.loadFromMemory(Font::BebasNeue::hex, Font::BebasNeue::size);
}

////////////////////////////////////////////////////////////
Style::~Style()
{
    //dtor
}

} // namespace CNGui
