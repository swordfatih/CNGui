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

#ifndef KEYEDIT_HPP
#define KEYEDIT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
// CNGui
#include <CNGui/Objects/Object.hpp>
#include <CNGui/Tools/Text.hpp>
#include <CNGui/Tools/Shape.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates a graphical key edit
///
////////////////////////////////////////////////////////////
class KeyEdit : public Object
{
public:
    ////////////////////////////////////////////////////////////
    using               Object::Object;

    ////////////////////////////////////////////////////////////
    /// \brief Reset the edit with a key
    ///
    /// \param key Key to reset with
    ///
    ////////////////////////////////////////////////////////////
    void                reset(sf::Keyboard::Key key);

    ////////////////////////////////////////////////////////////
    /// \brief Get the output key
    ///
    /// \return Output key
    ///
    ////////////////////////////////////////////////////////////
    sf::Keyboard::Key   getKey();

    ////////////////////////////////////////////////////////////
    /// \brief Get the previous key
    ///
    /// \return Previous key
    ///
    ////////////////////////////////////////////////////////////
    sf::Keyboard::Key   getPrevious();

    ////////////////////////////////////////////////////////////
    /// \brief Throw a graphical error
    ///
    /// \param message Message to draw
    ///
    ////////////////////////////////////////////////////////////
    void                error(std::string message);

private:
    ////////////////////////////////////////////////////////////
    /// \brief Stylize the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void        stylize();

    ////////////////////////////////////////////////////////////
    /// \brief Manage the object
    ///
    ////////////////////////////////////////////////////////////
    virtual void        manage();

    ////////////////////////////////////////////////////////////
    /// \brief Draw the object to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    CNGui::Shape        mBackground;                    ///< Background of the edit
    CNGui::Text         mTitle;                         ///< Title of the edit
    CNGui::Text         mOutput;                        ///< Output of the edit
    sf::Keyboard::Key   mKey = sf::Keyboard::Unknown;   ///< Selected key
    sf::Keyboard::Key   mPrevious = mKey;               ///< Previously selected key
    sf::Clock           mClockAnimation;                ///< Animation clock

};

} //namespace CNGui

#endif // KEYEDIT_HPP
