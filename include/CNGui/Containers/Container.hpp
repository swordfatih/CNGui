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

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "CNGui/Objects/Object.hpp"
#include <vector>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Base class for containers
///
////////////////////////////////////////////////////////////
class Container : public sf::Drawable, public sf::Transformable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
                Container();

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual     ~Container();

    ///////////////////////////////////////////////////////////
    /// Overload of operator << to add an object to the container
    ///
    ////////////////////////////////////////////////////////////
    Container&  operator <<(Object& content);

    ///////////////////////////////////////////////////////////
    /// Overload of operator << to add a container to the container
    ///
    ////////////////////////////////////////////////////////////
    Container&  operator <<(Container& content);

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Draw the contents to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<std::pair<sf::Drawable&, sf::Transformable&>> mContents;
};

} // namespace CNGui

#endif // CONTAINER_HPP
