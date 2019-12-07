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

#include <CNGui/Objects/Object.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
Object::Object(const std::string& name, const Style& style, const sf::Vector2f& size) : Registrable::Registrable(typeid(Object)), mName(name), mSize(size), mStyle(style), mUpdate(true), mReturn(false), mInitialized(false)
{

}

////////////////////////////////////////////////////////////
Object::~Object()
{
    //dtor
}

////////////////////////////////////////////////////////////
Object& Object::operator <<(const std::string& name)
{
    if(mName != name)
    {
        mName = name;
        mUpdate = true;
    }

    return *this;
}

////////////////////////////////////////////////////////////
bool Object::operator()()
{
    update();
    return mReturn;
}

////////////////////////////////////////////////////////////
bool Object::operator()(const sf::Vector2f& mouse)
{
    mMouse = mouse - mInPosition;

    update();
    return mReturn;
}

////////////////////////////////////////////////////////////
bool Object::operator()(const sf::RenderWindow& window)
{
    mMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()) - mInPosition;

    update();
    return mReturn;
}

////////////////////////////////////////////////////////////
bool Object::operator()(const sf::RenderWindow& window, const sf::View& view)
{
    mMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window), view) - mInPosition;

    update();
    return mReturn;
}

////////////////////////////////////////////////////////////
bool Object::operator()(const sf::Vector2i& mouse)
{
    mMouse = sf::Vector2f(mouse) - mInPosition;

    update();
    return mReturn;
}

////////////////////////////////////////////////////////////
void Object::setStyle(const Style& style)
{
    mStyle = style;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
Style& Object::getStyle()
{
    return mStyle;
}

////////////////////////////////////////////////////////////
void Object::setName(const std::string& name)
{
    mName = name;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
std::string Object::getName()
{
    return mName;
}

////////////////////////////////////////////////////////////
void Object::setSize(const sf::Vector2f& size)
{
    mSize = size;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
sf::Vector2f Object::getSize() const
{
    return mSize;
}

////////////////////////////////////////////////////////////
sf::FloatRect Object::getGlobalBounds() const
{
    if(isContained())
    {
        return sf::FloatRect(getPosition() + mInPosition, mSize);
    }

    return {getPosition(), mSize};
}

////////////////////////////////////////////////////////////
sf::FloatRect Object::getLocalBounds() const
{
    return {getPosition(), mSize};
}

////////////////////////////////////////////////////////////
void Object::initialize()
{

}

////////////////////////////////////////////////////////////
void Object::stylize()
{

}

////////////////////////////////////////////////////////////
void Object::manage()
{

}

////////////////////////////////////////////////////////////
void Object::update()
{
    if(!mInitialized)
    {
        initialize();
        mInitialized = true;
    }

    if(mUpdate)
    {
        stylize();
        mUpdate = false;
    }

    manage();

    if(mHandleEvent.active(this, "update_parent") && mParent)
    {
        mHandleEvent.clear(this, "update_parent");
        mHandleEvent.push(mParent, "update_parent");
        mParent->update();
    }
}

namespace Core
{

////////////////////////////////////////////////////////////
void draw(sf::RenderTarget& target)
{
    for(const auto& object_instance: Registrable::getRegisteredInstances<Object>())
    {
        if(!object_instance->isContained())
        {
           target.draw(*object_instance);
        }
    }

    for(const auto& container_instance: Registrable::getRegisteredInstances<Container>())
    {
        if(!container_instance->isContained())
        {
           target.draw(*container_instance);
        }
    }

    for(const auto& drawable_instance: Registrable::getRegisteredInstances<sf::Drawable>())
    {
        target.draw(*drawable_instance);
    }
}

} // namespace Core

} // namespace CNGui
