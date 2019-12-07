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

#include <CNGui/Objects/Box.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
Container& Box::internal()
{
    return mContainer;
}

////////////////////////////////////////////////////////////
sf::Vector2f Box::crop_position(const sf::Vector2f& position)
{
    sf::Vector2f size = mShape.getSize();

    if(mVertical && mContainer.getSize().y > mShape.getSize().y)
    {
        size.x -= mVerticalScroll.getSize().x;
    }

    if(mHorizontal && mContainer.getSize().x > mShape.getSize().x)
    {
        size.y -= mHorizontalScroll.getSize().y;
    }

    if(!sf::FloatRect(getPosition() + mInPosition + mShape.getPosition(), size).contains(position))
    {
        return {mContainer.getPosition().x - 1, mContainer.getPosition().y - 1};
    }

    return position;
}

////////////////////////////////////////////////////////////
void Box::setVertical(bool state)
{
    mVertical = std::move(state);
}

////////////////////////////////////////////////////////////
void Box::setHorizontal(bool state)
{
    mHorizontal = std::move(state);
}

////////////////////////////////////////////////////////////
void Box::stylize()
{
    if(mStyle.title)
    {
        mBackgroundTitle.setType(mStyle.background_shape);
        mBackgroundTitle.setFillColor(mStyle.background_color.neutral);
        mBackgroundTitle.setTexture(&mStyle.background_texture);
        mBackgroundTitle.setSize({mSize.x, mStyle.title_size + 4});

        mTitle.setFont(mStyle.title_font);
        mTitle.setFillColor(mStyle.title_color.neutral);
        mTitle.setStyle(mStyle.title_style);
        mTitle.setCharacterSize(mStyle.title_size);
        mTitle.setString(mName);
        mTitle.setSize({mSize.x, mBackgroundTitle.getSize().y});
        mTitle.setPosition(mStyle.outline_thickness, mBackgroundTitle.getGlobalBounds().height / 2 - mTitle.getGlobalBounds().height / 2 - mTitle.getLocalBounds().top);
        mShape.setSize({mSize.x, mSize.y - mBackgroundTitle.getSize().y});
    }
    else
    {
        mShape.setSize(mSize);
    }

    mShape.setFillColor(mStyle.main_color.neutral);
    mShape.setTexture(&mStyle.main_texture);
    mShape.setType(mStyle.main_shape);

    if(mStyle.outline)
    {
        mShape.setOutlineThickness(mStyle.outline_thickness);
        mShape.setOutlineColor(mStyle.outline_color.neutral);

        if(mStyle.title)
        {
            mShape.setSize({mSize.x - mStyle.outline_thickness * 2, mSize.y - mBackgroundTitle.getSize().y - mStyle.outline_thickness * 2});
            mShape.setPosition(mStyle.outline_thickness, mBackgroundTitle.getSize().y + mStyle.outline_thickness);
        }
        else
        {
            mShape.setSize({mSize.x - mStyle.outline_thickness * 2, mSize.y - mStyle.outline_thickness * 2});
            mShape.setPosition(mStyle.outline_thickness, mStyle.outline_thickness);
        }
    }
    else
    {
        if(mStyle.title)
        {
            mShape.setPosition(0, mBackgroundTitle.getSize().y);
        }
        else
        {
            mShape.setPosition(0, 0);
        }

        mShape.setOutlineThickness(0);
    }

    mVerticalScroll.setSize({mStyle.secondary_width, mShape.getSize().y});
    mVerticalScroll.setFillColor(mStyle.secondary_color.neutral);
    mVerticalScroll.setTexture(&mStyle.secondary_texture);
    mVerticalScroll.setType(mStyle.secondary_shape);
    mVerticalScroll.setPosition(mShape.getPosition().x + mShape.getSize().x - mVerticalScroll.getSize().x, mShape.getPosition().y);

    mHorizontalScroll.setSize({mShape.getSize().x, mStyle.secondary_width});
    mHorizontalScroll.setFillColor(mStyle.secondary_color.neutral);
    mHorizontalScroll.setTexture(&mStyle.secondary_texture);
    mHorizontalScroll.setType(mStyle.secondary_shape);
    mHorizontalScroll.setPosition(mShape.getPosition().x, mShape.getPosition().y + mShape.getSize().y - mHorizontalScroll.getSize().y);

    mVerticalBackground.setSize(mVerticalScroll.getSize());
    mVerticalBackground.setFillColor(mStyle.background_color.neutral);
    mVerticalBackground.setTexture(&mStyle.background_texture);
    mVerticalBackground.setType(mStyle.background_shape);
    mVerticalBackground.setPosition(mVerticalScroll.getPosition());

    mHorizontalBackground.setSize(mHorizontalScroll.getSize());
    mHorizontalBackground.setFillColor(mStyle.background_color.neutral);
    mHorizontalBackground.setTexture(&mStyle.background_texture);
    mHorizontalBackground.setType(mStyle.background_shape);
    mHorizontalBackground.setPosition(mHorizontalScroll.getPosition());

    if(mContainer.getSize().x > mShape.getSize().x)
    {
        mHorizontalScroll.setScale(mShape.getSize().x / mContainer.getSize().x, 1);
    }

    if(mContainer.getSize().y > mShape.getSize().y)
    {
        mVerticalScroll.setScale(1, mShape.getSize().y / mContainer.getSize().y);
    }

    mContainer.setInheritance(true, this, getPosition() + mInPosition);
    mContainer.setPosition(mShape.getPosition());
}

////////////////////////////////////////////////////////////
void Box::manage()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(sf::FloatRect(getPosition() + mVerticalScroll.getPosition(), {mVerticalScroll.getGlobalBounds().width, mVerticalScroll.getGlobalBounds().height}).contains(mMouse))
        {
            if(!mScrollingVertical && !mScrollingHorizontal)
            {
                mPositionClick = mMouse.y - mVerticalScroll.getPosition().y;
                mScrollingVertical = true;
                mHandleEvent.push(this, "vertical_click");
            }
        }
        else if(sf::FloatRect(getPosition() + mHorizontalScroll.getPosition(), {mHorizontalScroll.getGlobalBounds().width, mHorizontalScroll.getGlobalBounds().height}).contains(mMouse))
        {
            if(!mScrollingHorizontal && !mScrollingVertical)
            {
                mPositionClick = mMouse.x - mHorizontalScroll.getPosition().x;
                mScrollingHorizontal = true;
                mHandleEvent.push(this, "horizontal_click");
            }
        }

        if(mScrollingVertical && mVertical && mContainer.getSize().y > mShape.getSize().y)
        {
            mHandleEvent.push(this, "vertical_scroll");
            mVerticalScroll.setPosition(mVerticalScroll.getPosition().x, mMouse.y - mPositionClick);

            if(mVerticalScroll.getPosition().y < mShape.getPosition().y)
            {
                mVerticalScroll.setPosition(mVerticalScroll.getPosition().x, mShape.getPosition().y);
            }

            if(mVerticalScroll.getPosition().y + mVerticalScroll.getGlobalBounds().height > mShape.getPosition().y + mShape.getSize().y)
            {
                mVerticalScroll.setPosition(mVerticalScroll.getPosition().x, mShape.getPosition().y + mShape.getSize().y - mVerticalScroll.getGlobalBounds().height);
            }

            mContainer.setPosition(mContainer.getPosition().x, mShape.getPosition().y - (mVerticalScroll.getPosition().y - mShape.getPosition().y) / mVerticalScroll.getScale().y);
        }
        else if(mScrollingHorizontal && mHorizontal && mContainer.getSize().x > mShape.getSize().x)
        {
            mHandleEvent.push(this, "horizontal_scroll");
            mHorizontalScroll.setPosition(mMouse.x - mPositionClick, mHorizontalScroll.getPosition().y);

            if(mHorizontalScroll.getPosition().x < mShape.getPosition().x)
            {
                mHorizontalScroll.setPosition(mShape.getPosition().x, mHorizontalScroll.getPosition().y);
            }

            if(mHorizontalScroll.getPosition().x + mHorizontalScroll.getGlobalBounds().width > mShape.getPosition().x + mShape.getSize().x)
            {
                mHorizontalScroll.setPosition(mShape.getPosition().x + mShape.getSize().x - mHorizontalScroll.getGlobalBounds().width, mHorizontalScroll.getPosition().y);
            }

            mContainer.setPosition(mShape.getPosition().x - (mHorizontalScroll.getPosition().x - mShape.getPosition().x) / mHorizontalScroll.getScale().x, mContainer.getPosition().y);
        }

        if(mContainer.getSize().x < mShape.getSize().x)
        {
            mContainer.setPosition(mShape.getPosition().x, mContainer.getPosition().y);
            mHorizontalScroll.setPosition(mShape.getPosition().x, mHorizontalScroll.getPosition().y);
        }

        if(mContainer.getSize().y < mShape.getSize().y)
        {
            mContainer.setPosition(mContainer.getPosition().x, mShape.getPosition().y);
            mVerticalScroll.setPosition(mVerticalScroll.getPosition().x, mShape.getPosition().y);
        }
    }
    else
    {
        mScrollingVertical = false;
        mScrollingHorizontal = false;
    }

    if(mScrollingVertical)
    {
        mVerticalScroll.setFillColor(mStyle.secondary_color.clicked);
    }
    else if(sf::FloatRect(getPosition() + mVerticalScroll.getPosition(), {mVerticalScroll.getGlobalBounds().width, mVerticalScroll.getGlobalBounds().height}).contains(mMouse) && !mScrollingHorizontal)
    {
        mVerticalScroll.setFillColor(mStyle.secondary_color.hovered);
    }
    else
    {
        mVerticalScroll.setFillColor(mStyle.secondary_color.neutral);
    }

    if(mScrollingHorizontal)
    {
        mHorizontalScroll.setFillColor(mStyle.secondary_color.clicked);
    }
    else if(sf::FloatRect(getPosition() + mHorizontalScroll.getPosition(), {mHorizontalScroll.getGlobalBounds().width, mHorizontalScroll.getGlobalBounds().height}).contains(mMouse) && !mScrollingVertical)
    {
        mHorizontalScroll.setFillColor(mStyle.secondary_color.hovered);
    }
    else
    {
        mHorizontalScroll.setFillColor(mStyle.secondary_color.neutral);
    }

    if(mHandleEvent.active(this, "update_parent"))
    {
        if(mContainer.getSize().x > mShape.getSize().x)
        {
            mHorizontalScroll.setScale(mShape.getSize().x / mContainer.getSize().x, 1);
        }

        if(mContainer.getSize().y > mShape.getSize().y)
        {
            mVerticalScroll.setScale(1, mShape.getSize().y / mContainer.getSize().y);
        }
    }
}

////////////////////////////////////////////////////////////
void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mShape, states);

    auto scissorStart = target.mapCoordsToPixel({getPosition().x + mShape.getPosition().x, getPosition().y + mShape.getPosition().y + mShape.getSize().y});
    auto scissorSize = target.mapCoordsToPixel({mShape.getSize().x, mShape.getSize().y});

    {
        CNGui::Scissors scissors({scissorStart.x + mInPosition.x, target.getSize().y - scissorStart.y - mInPosition.y, scissorSize.x, scissorSize.y});
        target.draw(mContainer, states);
    }

    if(mVertical && mContainer.getSize().y > mShape.getSize().y)
    {
        target.draw(mVerticalBackground, states);
        target.draw(mVerticalScroll, states);
    }

    if(mHorizontal && mContainer.getSize().x > mShape.getSize().x)
    {
        target.draw(mHorizontalBackground, states);
        target.draw(mHorizontalScroll, states);
    }

    if(mStyle.title)
    {
        target.draw(mBackgroundTitle, states);
        target.draw(mTitle, states);
    }
}

} // namespace CNGui
