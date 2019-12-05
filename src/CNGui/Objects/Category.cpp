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

#include <CNGui/Objects/Category.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
Container& Category::internal()
{
    return mContainer;
}

////////////////////////////////////////////////////////////
bool Category::state() const
{
    return mReturn;
}

////////////////////////////////////////////////////////////
void Category::initialize()
{
    mSizeClosed = mSize;

    for(const auto& updatable: mContainer.retrieve<Updatable>())
    {
        updatable->update();
    }
}

////////////////////////////////////////////////////////////
void Category::stylize()
{
    //Background
    mBackground.setType(mStyle.background_shape);
    mBackground.setFillColor(mStyle.background_color.neutral);
    mBackground.setTexture(&mStyle.background_texture);

    if(mStyle.outline)
    {
        mBackground.setSize(mSizeClosed - sf::Vector2f(mStyle.outline_thickness * 2, mStyle.outline_thickness * 2));
        mBackground.setPosition(mStyle.outline_thickness, mStyle.outline_thickness);
        mBackground.setOutlineColor(mStyle.outline_color.neutral);
        mBackground.setOutlineThickness(mStyle.outline_thickness);
    }
    else
    {
        mBackground.setSize(mSizeClosed);
        mBackground.setOutlineThickness(0);
        mBackground.setPosition(0, 0);
    }

    //Arrow
    mArrow.setPointCount(4);
    mArrow.setPoint(0, {0, 0});
    mArrow.setPoint(1, {25, 20});
    mArrow.setPoint(2, {0, 40});
    mArrow.setPoint(3, {10, 20});

    mArrow.setOrigin(mArrow.getPoint(3));
    mArrow.setFillColor(mStyle.main_color.neutral);
    mArrow.setTexture(&mStyle.main_texture);

    float factor = mBackground.getSize().y / 100;
    mArrow.setScale(factor, factor);

    if(mStyle.title)
    {
        mArrow.setPosition(mBackground.getPosition().x + mArrow.getPoint(2).y * mArrow.getScale().y / 2, mBackground.getPosition().y + mBackground.getSize().y / 2);

        //Title
        mTitle.setString(mName);
        mTitle.setCharacterSize(mStyle.title_size);
        mTitle.setFont(mStyle.title_font);
        mTitle.setFillColor(mStyle.title_color.neutral);
        mTitle.setStyle(mStyle.title_style);
        mTitle.setSize({mBackground.getSize().x - mArrow.getPoint(2).y * mArrow.getScale().y - 10, mBackground.getSize().y});
        mTitle.setPosition(mBackground.getPosition().x + mArrow.getPoint(2).y * mArrow.getScale().y - mTitle.getLocalBounds().left + 10, mBackground.getSize().y / 2 - mTitle.getGlobalBounds().height / 2 - mTitle.getLocalBounds().top + mStyle.outline_thickness);
    }
    else
    {
        mArrow.setPosition(mBackground.getPosition().x + mBackground.getSize().x / 2, mBackground.getPosition().y + mBackground.getSize().y / 2);
    }

    if(mContainer.getAlign() == Alignment::Vertical)
    {
        mContainer.setPosition(0, mSizeClosed.y);
    }
    else
    {
        mArrow.setRotation(90);
        mContainer.setPosition(mSizeClosed.x, 0);
    }

    if(mContainer.getMode() != Container::Mode::Stacked)
    {
        if(mContainer.getAlign() == Alignment::Vertical)
        {
            mContainer.setSize({mSize.x, mContainer.getSize().y});
        }
        else if(mContainer.getAlign() == Alignment::Horizontal)
        {
            mContainer.setSize({mContainer.getSize().x, mSize.y});
        }
    }

    mContainer.setInheritance(true, this, getPosition() + mInPosition);
    mContainer.update();
}

////////////////////////////////////////////////////////////
void Category::manage()
{
    //Update size
    auto update_size = [&]()
    {
        if(mReturn)
        {
            if(mContainer.getAlign() == Alignment::Vertical)
            {
                mArrow.setRotation(90);
                mSize.y = mSizeClosed.y + mContainer.getSize().y;

                if(mContainer.getMode() == Container::Mode::Stacked)
                {
                    mSize.x = mContainer.getSize().x;
                }
            }
            else if(mContainer.getAlign() == Alignment::Horizontal)
            {
                mArrow.setRotation(0);
                mSize.x = mSizeClosed.x + mContainer.getSize().x;

                if(mContainer.getMode() == Container::Mode::Stacked)
                {
                    mSize.y = mContainer.getSize().y;
                }
            }
        }
        else
        {
            if(mContainer.getAlign() == Alignment::Vertical)
            {
                mArrow.setRotation(0);
                mSize.y = mSizeClosed.y;

                if(mContainer.getMode() == Container::Mode::Stacked)
                {
                    mSize.x = mSizeClosed.x;
                }
            }
            else if(mContainer.getAlign() == Alignment::Horizontal)
            {
                mArrow.setRotation(90);
                mSize.x = mSizeClosed.x;

                if(mContainer.getMode() == Container::Mode::Stacked)
                {
                    mSize.y = mSizeClosed.y;
                }
            }
        }
    };

    //Hover
    if(sf::FloatRect(getPosition().x, getPosition().y, mBackground.getGlobalBounds().width, mBackground.getGlobalBounds().height).contains(mMouse))
    {
        mHandleEvent.push(this, "hover");

        mBackground.setFillColor(mStyle.background_color.hovered);
        mArrow.setFillColor(mStyle.main_color.hovered);
        mTitle.setFillColor(mStyle.title_color.hovered);

        //Click
        if(auto event_mouse = mHandleEvent.get_if(sf::Event::MouseButtonPressed); event_mouse && event_mouse->mouseButton.button == sf::Mouse::Left)
        {
            mHandleEvent.push(this, "click");

            mReturn = !mReturn;

            update_size();

            if(isContained())
            {
                mHandleEvent.push(mParent, "update_parent");
                mParent->update();
            }
        }
    }
    else if(mReturn)
    {
        mBackground.setFillColor(mStyle.background_color.clicked);
        mArrow.setFillColor(mStyle.main_color.clicked);
        mTitle.setFillColor(mStyle.title_color.clicked);
    }
    else
    {
        mBackground.setFillColor(mStyle.background_color.neutral);
        mArrow.setFillColor(mStyle.main_color.neutral);
        mTitle.setFillColor(mStyle.title_color.neutral);
    }

    if(mHandleEvent.active(this, "update_parent"))
    {
        update_size();
    }
}

////////////////////////////////////////////////////////////
void Category::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mArrow, states);
    target.draw(mTitle, states);

    if(mReturn)
    {
        target.draw(mContainer, states);
    }
}

} // namespace CNGui
