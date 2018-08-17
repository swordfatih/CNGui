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

#include "CNGUI/Objects/Object.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
Object::Object(const std::string& id, const sf::Vector3f& size, EventHandler& handleEvent, Style& style) : mSize(size), mHandleEvent(handleEvent), mStyle(style), mUpdate(true),  mReturn(false)
{
    parse(id, mIndex, mName);
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
bool Object::operator()(const sf::Vector2f& mouse)
{
    mMouse = mouse;
    update();
    return mReturn;
}

////////////////////////////////////////////////////////////
bool Object::operator()(const sf::Vector2i& mouse)
{
    mMouse = sf::Vector2f(mouse);
    update();
    return mReturn;
}

////////////////////////////////////////////////////////////
void Object::setStyle(Style& style)
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
void Object::setId(const std::string& id)
{
    parse(id, mIndex, mName);
    mUpdate = true;
}

////////////////////////////////////////////////////////////
std::string Object::getId()
{
    return mName + "#" + std::to_string(mIndex);
}

////////////////////////////////////////////////////////////
void Object::setSize(const sf::Vector3f& size)
{
    mSize = size;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
sf::Vector3f Object::getSize()
{
    return mSize;
}

////////////////////////////////////////////////////////////
void Object::setEventHandler(EventHandler& handleEvent)
{
    mHandleEvent = handleEvent;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
EventHandler& Object::getEventHandler()
{
    return mHandleEvent;
}

////////////////////////////////////////////////////////////
void Object::parse(const std::string& id, sf::Uint16& index, std::string& name)
{
    std::size_t pos(0);
    do
    {
        pos = id.find('#', pos);
        name = id.substr(0, id.size() - 4);

        std::string temp = id.substr(pos + 1);

        for(unsigned i = 0; i < temp.size(); ++i)
            assert(!isalpha(temp.at(i))); // Invalid index

        index = std::stoi(temp);
    }while(id.at(pos - 1) == '\\');
}

////////////////////////////////////////////////////////////
void Object::update()
{

}

} // namespace CNGui
