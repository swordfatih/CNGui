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
    sf::Color   labelclickedcolor;      ///< Color of the label when clicked
    bool        selectable;             ///< The object is selectable
    bool        outline;                ///< The object has an outline
    sf::Uint16  outlinethickness;       ///< Thickness of the outline
    sf::Color   outlinecolor;           ///< Color of the outline
    sf::Color   outlinehovercolor;      ///< Color of the outline when hovering
    sf::Color   outlineclickedcolor;    ///< Color of the outline when clicked
};

} // namespace CNGui

#endif // STYLE_HPP_INCLUDED
