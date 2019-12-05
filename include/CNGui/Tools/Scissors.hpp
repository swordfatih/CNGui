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

#ifndef SCISSORS_HPP
#define SCISSORS_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/OpenGL.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that clip an area on the window using
/// GL_SCISSOR_TEST
///
////////////////////////////////////////////////////////////
class Scissors
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param area Area to clip
    ///
    ////////////////////////////////////////////////////////////
                    Scissors(sf::FloatRect area);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
                    ~Scissors();

    ////////////////////////////////////////////////////////////
    /// \brief Get the area to clip
    ///
    /// \return Clip area
    ///
    ////////////////////////////////////////////////////////////
    sf::FloatRect   area();

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool            mBusy = false;
    sf::FloatRect   mAreaExisting = {0, 0, 0, 0};
    sf::FloatRect   mAreaClip = {0, 0, 0, 0};

};

} // namespace CNGui

#endif // SCISSORS_HPP
