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

#ifndef SLIDER_HPP
#define SLIDER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Objects/Object.hpp>
#include <CNGui/Tools/Shape.hpp>
#include <CNGui/Tools/Text.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates an interactive graphical slider
///
////////////////////////////////////////////////////////////
class Slider : public Object
{
public:
    ////////////////////////////////////////////////////////////
    using           Object::Object;

    /////////////////////////////////////////////////
    /// \brief Change the value range
    ///
    /// \param range New value range
    ///
    /////////////////////////////////////////////////
    void            setRange(const sf::Vector2f& range);

    /////////////////////////////////////////////////
    /// \brief Change the selected value, does nothing
    /// if value is out of range
    ///
    /// \param value New value
    ///
    /// \see getValue
    /////////////////////////////////////////////////
    void            setValue(float value);

    /////////////////////////////////////////////////
    /// \brief Get the selected value
    ///
    /// \return Selected value
    ///
    /// \see getValue
    /////////////////////////////////////////////////
    float           getValue() const;

    /////////////////////////////////////////////////
    /// \brief Get the slide step
    ///
    /// \return Slide step
    ///
    /// \see setStep
    /////////////////////////////////////////////////
    void            setStep(float step);

    /////////////////////////////////////////////////
    /// \brief Set the slide step
    ///
    /// \param step Slide step
    ///
    /// \see getStep
    /////////////////////////////////////////////////
    float           getStep() const;

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
    Shape           mProgression;       ///< Progression of the slider
    Shape           mBackground;        ///< Background of the slider
    Shape           mShape;             ///< Shape of the slider
    Text            mTitle;             ///< Title label
    Text            mOutput;            ///< Output label
    sf::Vector2f    mRange = {0, 100};  ///< Value range
    float           mValue = 0;         ///< Selected value
    float           mPositionClick = 0; ///< Click position
    float           mStep = 1;          ///< Slide step
};

} // namespace CNGui

#endif // SLIDER_HPP
