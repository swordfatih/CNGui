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
    mName = name;
    mUpdate = true;
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
