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

#include <CNGui/Tools/Shape.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
Shape::Shape(Type type, sf::Vector2f size) : mType(type), mSize(size)
{
    update();
}

////////////////////////////////////////////////////////////
Shape::~Shape()
{
    //dtor
}

////////////////////////////////////////////////////////////
void Shape::setType(Type type)
{
    mType = type;
    update();
}

////////////////////////////////////////////////////////////
Shape::Type Shape::getType()
{
    return mType;
}

////////////////////////////////////////////////////////////
void Shape::setSize(sf::Vector2f size)
{
    mSize = size;
    update();
}

////////////////////////////////////////////////////////////
sf::Vector2f Shape::getSize() const
{
    return mSize;
}

////////////////////////////////////////////////////////////
std::size_t Shape::getPointCount() const
{
    switch(mType)
    {
        default:
        case Triangle: return 3;
        case Rectangle: return 4;
        case RoundedRectangle:
        {
            float radius = 0;
            if(mSize.x < mSize.y)
                radius = mSize.x / 5;
            else
                radius = mSize.y / 5;

            return radius * 4;
        }
        case Circle: return 30;
    }
}

////////////////////////////////////////////////////////////
sf::Vector2f Shape::getPoint(std::size_t index) const
{
    switch(mType)
    {
        default:
        case Triangle:
        {
            static const float pi = 3.141592654f;

            float angle = index * 2 * pi / 3 - pi / 2;
            float x = std::cos(angle) * mSize.x / 2;
            float y = std::sin(angle) * mSize.y / 2;

            return sf::Vector2f(mSize.x / 2 + x, mSize.y / 2 + y);
        }
        case Rectangle:
        {
            switch(index)
            {
                default:
                case 0: return sf::Vector2f(0, 0);
                case 1: return sf::Vector2f(mSize.x, 0);
                case 2: return sf::Vector2f(mSize.x, mSize.y);
                case 3: return sf::Vector2f(0, mSize.y);
            }
        }
        case RoundedRectangle:
        {
            float radius = 0;
            if(mSize.x < mSize.y)
                radius = mSize.x / 5;
            else
                radius = mSize.y / 5;

            float deltaAngle = 90.0f/ (radius - 1);
            sf::Vector2f center;
            unsigned int centerIndex = index / radius;
            static const float pi = 3.141592654f;

            switch(centerIndex)
            {
                case 0:
                    center.x = mSize.x - radius;
                    center.y = radius;
                    break;
                case 1:
                    center.x = radius;
                    center.y = radius;
                    break;
                case 2:
                    center.x = radius;
                    center.y = mSize.y - radius;
                    break;
                case 3:
                    center.x = mSize.x - radius;
                    center.y = mSize.y - radius;
                    break;
            }

            return sf::Vector2f(radius * std::cos(deltaAngle * (index-centerIndex)  * pi / 180) + center.x, -radius * std::sin(deltaAngle * (index-centerIndex) * pi / 180) + center.y);
        }
        case Circle:
        {
            static const float pi = 3.141592654f;

            float radius = 0;

            if(mSize.x < mSize.y)
                radius = mSize.x / 2;
            else
                radius = mSize.y / 2;

            float angle = index * 2 * pi / 30 - pi / 2;
            float x = std::cos(angle) * radius;
            float y = std::sin(angle) * radius;

            return sf::Vector2f(radius + x, radius + y);
        }
    }
}

} // namespace CNGui
