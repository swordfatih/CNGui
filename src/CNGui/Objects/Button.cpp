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

#include <CNGui/Objects/Button.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
bool Button::onClick()
{
    return mClicked;
}

////////////////////////////////////////////////////////////
bool Button::onRelease()
{
    return mReleased;
}

////////////////////////////////////////////////////////////
bool Button::onHover()
{
    return mHover;
}

////////////////////////////////////////////////////////////
void Button::update()
{
    //Updating the style of the button
    if(mUpdate)
    {
        mShape.setType(mStyle.main_shape);
        mShape.setFillColor(mStyle.main_color.neutral);
        mShape.setTexture(&mStyle.main_texture);

        if(!mStyle.outline)
        {
            mShape.setSize(mSize);
        }
        else
        {
            mShape.setSize(sf::Vector2f(mSize.x - mStyle.outline_thickness * 2, mSize.y - mStyle.outline_thickness * 2));
            mShape.setOutlineColor(mStyle.outline_color.neutral);
            mShape.setOutlineThickness(mStyle.outline_thickness);
            mShape.setPosition(mStyle.outline_thickness, mStyle.outline_thickness);
        }

        if(mStyle.title)
        {
            mLabel.setFont(mStyle.title_font);
            mLabel.setFillColor(mStyle.title_color.neutral);
            mLabel.setStyle(mStyle.title_style);
            mLabel.setCharacterSize(mStyle.title_size);
            mLabel.setString(mName);
            if(mStyle.main_shape == CNGui::Shape::Rectangle || mStyle.main_shape == CNGui::Shape::RoundedRectangle)
            {
                mLabel.setSize(sf::Vector2f(mShape.getSize().x - mShape.getSize().x * 0.05, mShape.getSize().y));
                mLabel.setPosition(mShape.getPosition().x - mLabel.getLocalBounds().left + mShape.getSize().x / 2 - mLabel.getGlobalBounds().width / 2, mShape.getPosition().y - mLabel.getLocalBounds().top + mShape.getSize().y / 2 - mLabel.getGlobalBounds().height / 2);
            }
            else if(mStyle.main_shape == CNGui::Shape::Triangle)
            {
                mLabel.setSize(sf::Vector2f(mShape.getSize().x / 3, mShape.getSize().y / 3));
                mLabel.setPosition(mShape.getPosition().x - mLabel.getLocalBounds().left + mShape.getSize().x / 2 - mLabel.getGlobalBounds().width / 2, mShape.getPosition().y - mLabel.getLocalBounds().top + mShape.getSize().y / 2 - mLabel.getGlobalBounds().height / 2);
            }
            else if(mStyle.main_shape == CNGui::Shape::Circle)
            {
                sf::Uint16 center;
                if(mSize.x > mSize.y)
                {
                    center = mShape.getSize().y / 2;
                }
                else
                {
                    center = mShape.getSize().x / 2;
                }
                mLabel.setSize(sf::Vector2f(center, center));
                mLabel.setPosition(center - mLabel.getGlobalBounds().width / 2.5 + mLabel.getLocalBounds().left, center - mLabel.getGlobalBounds().height / 2.5 - mLabel.getLocalBounds().top);
            }
        }

        mUpdate = false;
    }

    //If the button is hovered
    if(sf::FloatRect(getPosition().x, getPosition().y, mShape.getGlobalBounds().width, mShape.getGlobalBounds().height).contains(mMouse))
    {
        mHover = true;

        //Throwing event as button clicked
        auto event_mouse = mHandleEvent.get_if(sf::Event::MouseButtonPressed);
        if(event_mouse && event_mouse->mouseButton.button == sf::Mouse::Left)
        {
            mClicked = true;
        }
        else
        {
            mClicked = false;
        }

        //Throwing event as button released
        if(auto event = mHandleEvent.get_if(sf::Event::MouseButtonReleased); event && event->mouseButton.button == sf::Mouse::Left)
        {
            mReleased = true;
        }
        else
        {
            mReleased = false;
        }

        //Button is pressed
        if((sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mStyle.selectable) || (event_mouse && event_mouse->mouseButton.button == sf::Mouse::Left && mStyle.selectable))
        {
            mShape.setFillColor(mStyle.main_color.clicked);
            mLabel.setFillColor(mStyle.title_color.clicked);
            mShape.setOutlineColor(mStyle.outline_color.clicked);
            mReturn = true;
        }
        else if(!mStyle.selectable || (mStyle.selectable && !mReturn))
        {
            mShape.setFillColor(mStyle.main_color.hovered);
            mLabel.setFillColor(mStyle.title_color.hovered);
            mShape.setOutlineColor(mStyle.outline_color.hovered);
        }
    }
    else
    {
        mHover = false;
        mClicked = false;
        mReleased = false;

        auto event_mouse = mHandleEvent.get_if(sf::Event::MouseButtonPressed);
        if((!mStyle.selectable) || (mStyle.selectable && !mReturn) || (mStyle.selectable && mReturn && event_mouse && event_mouse->mouseButton.button == sf::Mouse::Left))
        {
            mShape.setFillColor(mStyle.main_color.neutral);
            mLabel.setFillColor(mStyle.title_color.neutral);
            mShape.setOutlineColor(mStyle.outline_color.neutral);

            if(mReturn)
            {
                mReturn = false;
            }
        }
    }
}

////////////////////////////////////////////////////////////
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mShape, states);

    if(mStyle.title)
    {
        target.draw(mLabel, states);
    }
}

} // namespace CNGui
