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

#include <CNGui/Tools/Easing.hpp>

namespace CNGui
{
///////////////////////////////////////////////////////////
namespace trigonometry
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration)
    {
        return distance * std::cos(progression * (pi_constant / 2.f) - pi_constant) + distance;
    }

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration)
    {
        return distance * std::sin(progression * (pi_constant / 2.f));
    }

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return in(progression * 2, distance / 2);
        }

        return out(progression * 2 - 1.f, distance / 2) + distance / 2;
    }

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return out(progression * 2, distance / 2);
        }

        return in(progression * 2 - 1.f, distance / 2) + distance / 2;
    }
} // namespace trigonometry

///////////////////////////////////////////////////////////
namespace root
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration)
    {
        return distance * (1.f - std::sqrt(1.f - progression));
    }

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration)
    {
        return distance * std::sqrt(progression);
    }

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return in(progression * 2, distance / 2);
        }

        return out(progression * 2 - 1.f, distance / 2) + distance / 2;
    }

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return out(progression * 2, distance / 2);
        }

        return in(progression * 2 - 1.f, distance / 2) + distance / 2;
    }
} // namespace root

///////////////////////////////////////////////////////////
namespace exponential
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration)
    {
        return distance * std::pow(2, 10 * (progression - 1.f));
    }

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration)
    {
        return distance * (1.f - std::pow(2, 10 * (1.f - progression - 1.f)));
    }

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return in(progression * 2, distance / 2);
        }

        return out(progression * 2 - 1.f, distance / 2) + distance / 2;
    }

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return out(progression * 2, distance / 2);
        }

        return in(progression * 2 - 1.f, distance / 2) + distance / 2;
    }
} // namespace exponential

///////////////////////////////////////////////////////////
namespace elastic
{
    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration)
    {
        return distance * (1.f - std::pow(2, -10 * (1.f - progression)) * std::sin(((1.f - progression) * duration - (duration * 0.3 / 4)) * (2 * pi_constant) / (duration * 0.3f))) - distance;
    }

    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration)
    {
        return distance * std::pow(2, -10 * progression) * std::sin((progression * duration - (duration * 0.3 / 4)) * (2 * pi_constant) / (duration * 0.3f)) + distance;
    }

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return in(progression * 2, distance / 2, duration);
        }

        return out(progression * 2 - 1.f, distance / 2, duration) + distance / 2;
    }

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return out(progression * 2, distance / 2, duration);
        }

        return in(progression * 2 - 1.f, distance / 2, duration) + distance / 2;
    }
} // namespace elastic

///////////////////////////////////////////////////////////
namespace bounce
{
    ///////////////////////////////////////////////////////////
    float out(float progression, float distance, float duration)
    {
        if(progression < 1.f / 2.75f)
        {
            return distance * (angle_constant * std::pow(progression, 2));
        }
        else if(progression < 2.f / 2.75f)
        {
            return distance * (angle_constant * std::pow(progression - (1.5f / 2.75f), 2) - 0.25f) + distance;
        }
        else if(progression < 2.5f / 2.75f)
        {
            return distance * (angle_constant * std::pow(progression - (2.25f / 2.75f), 2) - 0.07f) + distance;
        }
        else
        {
            return distance * (angle_constant * std::pow(progression - (2.625f / 2.75f), 2) - 0.03f) + distance;
        }
    }

    ///////////////////////////////////////////////////////////
    float in(float progression, float distance, float duration)
    {
        return distance - out(1.f - progression, distance);
    }

    ///////////////////////////////////////////////////////////
    float in_out(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return in(progression * 2, distance / 2);
        }

        return out(progression * 2 - 1.f, distance / 2) + distance / 2;
    }

    ///////////////////////////////////////////////////////////
    float out_in(float progression, float distance, float duration)
    {
        if(progression < 0.5)
        {
            return out(progression * 2, distance / 2);
        }

        return in(progression * 2 - 1.f, distance / 2) + distance / 2;
    }
} // namespace bounce

} // namespace CNGui
