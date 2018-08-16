#include "CNGui/Utilities/Shape.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
Shape::Shape(Type type, sf::Vector3f size) : mType(type), mSize(size)
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
void Shape::setSize(sf::Vector3f size)
{
    mSize = size;
    update();
}

////////////////////////////////////////////////////////////
sf::Vector3f Shape::getSize()
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
        case RoundedRectangle: return mSize.z * 4;
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
            float x = std::cos(angle) * mSize.z;
            float y = std::sin(angle) * mSize.z;

            return sf::Vector2f(mSize.z + x, mSize.z + y);
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
            float deltaAngle = 90.0f/(mSize.z-1);
            sf::Vector2f center;
            unsigned int centerIndex = index/mSize.z;
            static const float pi = 3.141592654f;

            switch(centerIndex)
            {
                case 0: center.x = mSize.x - mSize.z; center.y = mSize.z; break;
                case 1: center.x = mSize.z; center.y = mSize.z; break;
                case 2: center.x = mSize.z; center.y = mSize.y - mSize.z; break;
                case 3: center.x = mSize.x - mSize.z; center.y = mSize.y - mSize.z; break;
            }

            return sf::Vector2f(mSize.z*cos(deltaAngle*(index-centerIndex)*pi/180)+center.x,-mSize.z*sin(deltaAngle*(index-centerIndex)*pi/180)+center.y);
        }
        case Circle:
        {
            static const float pi = 3.141592654f;

            float angle = index * 2 * pi / 30 - pi / 2;
            float x = std::cos(angle) * mSize.z;
            float y = std::sin(angle) * mSize.z;

            return sf::Vector2f(mSize.z + x, mSize.z + y);
        }
    }
}

} // namespace CNGui
