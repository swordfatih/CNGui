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

#ifndef EASING_HPP
#define EASING_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//SFML
#include <SFML/System/Clock.hpp>

//Standard
#include <cmath>

#define pi_constant     3.14159f    ///< Pi
#define bounce_constant 1.70158f    ///< Bounce
#define angle_constant  7.5625f     ///< Angle

namespace CNGui
{

/////////////////////////////////////////////////
/// \brief Some useful easing functions that you
/// can easily use to animate your objects
///
/////////////////////////////////////////////////
namespace trigonometry
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration);

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration);
} // namespace trigonometry

///////////////////////////////////////////////////////////
namespace power
{
    ///////////////////////////////////////////////////////////
    template <int factor>
    float in(float progression, float distance, float duration = 0)
    {
        return distance * std::pow(progression, factor);
    }

    ///////////////////////////////////////////////////////////
    template <int factor>
    float out(float progression, float distance, float duration = 0)
    {
        return distance * (1.f - std::pow(1.f - progression, factor));
    }

    ///////////////////////////////////////////////////////////
    template <int factor>
    float in_out(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return in<factor>(progression * 2, distance / 2);
        }

        return out<factor>(progression * 2 - 1.f, distance / 2) + distance / 2;
    }

    ///////////////////////////////////////////////////////////
    template <int factor>
    float out_in(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return out<factor>(progression * 2, distance / 2);
        }

        return in<factor>(progression * 2 - 1.f, distance / 2) + distance / 2;
    }
} // namespace power

///////////////////////////////////////////////////////////
namespace root
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration);

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration);
} // namespace root

///////////////////////////////////////////////////////////
namespace exponential
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration);

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration);
} // namespace exponential

///////////////////////////////////////////////////////////
namespace drop
{
    ///////////////////////////////////////////////////////////
    template <int percent>
    float in(float progression, float distance, float duration = 0)
    {
        float intensity = bounce_constant * percent / 10;

        return distance * (std::pow(progression, 2) * ((intensity + 1.f) * progression - intensity));
    }

    ///////////////////////////////////////////////////////////
    template <int percent>
    float out(float progression, float distance, float duration = 0)
    {
        float intensity = bounce_constant * percent / 10;
        progression = 1.f - progression;

        return distance * (1.f - std::pow(progression, 2) * ((intensity + 1.f) * progression - intensity));
    }

    ///////////////////////////////////////////////////////////
    template <int percent>
    float in_out(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return in<percent>(progression * 2, distance / 2);
        }

        return out<percent>(progression * 2 - 1.f, distance / 2) + distance / 2;
    }

    ///////////////////////////////////////////////////////////
    template <int percent>
    float out_in(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return out<percent>(progression * 2, distance / 2);
        }

        return in<percent>(progression * 2 - 1.f, distance / 2) + distance / 2;
    }
} // namespace drop

///////////////////////////////////////////////////////////
namespace elastic
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration);

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration);

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration);

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration);
} // namespace elastic

///////////////////////////////////////////////////////////
namespace bounce
{
    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration = 0);

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration);

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration);
} // namespace bounce

///////////////////////////////////////////////////////////
template <typename Function>
float ease(const Function& function, const sf::Clock& current, sf::Time duration, float distance)
{
    auto&& progression = current.getElapsedTime().asSeconds() / duration.asSeconds();

    if(current.getElapsedTime() > duration)
    {
        progression = 1;
    }

    return function(progression, distance, duration.asSeconds());
}

} // namespace CNGui

#endif // EASING_HPP
