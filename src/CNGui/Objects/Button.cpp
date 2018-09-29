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

#include <CNGui/Objects/Button.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
bool Button::onClick()
{
    return mClicked;
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
        mShape.setType(mStyle.shape);
        mShape.setFillColor(mStyle.fillcolor);
        mShape.setTexture(&mStyle.texturebackground);

        if(!mStyle.outline)
        {
            mShape.setSize(mSize);
        }
        else
        {
            mShape.setSize(sf::Vector2f(mSize.x - mStyle.outlinethickness * 2, mSize.y - mStyle.outlinethickness * 2));
            mShape.setOutlineColor(mStyle.outlinecolor);
            mShape.setOutlineThickness(mStyle.outlinethickness);
            mShape.setPosition(mStyle.outlinethickness, mStyle.outlinethickness);
        }

        if(mStyle.label)
        {
            mLabel.setFont(mStyle.font);
            mLabel.setFillColor(mStyle.labelcolor);
            mLabel.setCharacterSize(mStyle.charactersize);
            mLabel.setString(mName);
            if(mStyle.shape == CNGui::Shape::Rectangle || mStyle.shape == CNGui::Shape::RoundedRectangle)
            {
                mLabel.setSize(sf::Vector2f(mShape.getSize().x - mShape.getSize().x * 0.05, mShape.getSize().y));
                mLabel.setPosition(mShape.getPosition().x - mLabel.getLocalBounds().left + mShape.getSize().x / 2 - mLabel.getGlobalBounds().width / 2, mShape.getPosition().y - mLabel.getLocalBounds().top + mShape.getSize().y / 2 - mLabel.getGlobalBounds().height / 2);
            }
            else if(mStyle.shape == CNGui::Shape::Triangle)
            {
                mLabel.setSize(sf::Vector2f(mShape.getSize().x / 3, mShape.getSize().y / 3));
                mLabel.setPosition(mShape.getPosition().x - mLabel.getLocalBounds().left + mShape.getSize().x / 2 - mLabel.getGlobalBounds().width / 2, mShape.getPosition().y - mLabel.getLocalBounds().top + mShape.getSize().y / 2 - mLabel.getGlobalBounds().height / 2);
            }
            else if(mStyle.shape == CNGui::Shape::Circle)
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
        if(mHandleEvent.isActive(sf::Event::MouseButtonPressed) && mHandleEvent[sf::Event::MouseButtonPressed].mouseButton.button == sf::Mouse::Left)
            mClicked = true;
        else
            mClicked = false;

        //Button is pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mShape.setFillColor(mStyle.clickedcolor);
            mLabel.setFillColor(mStyle.labelclickedcolor);
            mShape.setOutlineColor(mStyle.outlineclickedcolor);
            mReturn = true;
        }
        else if(!mStyle.selectable || (mStyle.selectable && !mReturn))
        {
            mShape.setFillColor(mStyle.hovercolor);
            mLabel.setFillColor(mStyle.labelhovercolor);
            mShape.setOutlineColor(mStyle.outlinehovercolor);
        }
    }
    else
    {
        mHover = false;

        if((!mStyle.selectable) || (mStyle.selectable && !mReturn) || (mStyle.selectable && mReturn && mHandleEvent.isActive(sf::Event::MouseButtonPressed) && mHandleEvent[sf::Event::MouseButtonPressed].mouseButton.button == sf::Mouse::Left))
        {
            mShape.setFillColor(mStyle.fillcolor);
            mLabel.setFillColor(mStyle.labelcolor);
            mShape.setOutlineColor(mStyle.outlinecolor);
            if(mReturn)
                mReturn = false;
        }
    }
}

////////////////////////////////////////////////////////////
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mShape, states);
    if(mStyle.label)
        target.draw(mLabel, states);
}

} // namespace CNGui
