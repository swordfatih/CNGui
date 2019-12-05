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

#include <CNGui/Objects/ProgressIndicator.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
void ProgressIndicator::add(float progression)
{
    if(mNewProgression + progression <= 1 && mNewProgression + progression >= 0)
    {
        mNewProgression += progression;
    }
    else if(mNewProgression + progression < 0)
    {
        mNewProgression = 0;
    }
    else if(mNewProgression + progression > 1)
    {
        mNewProgression = 1;
    }

    mUpdate = true;
}

////////////////////////////////////////////////////////////
void ProgressIndicator::setProgression(float progression)
{
    if(progression <= 1 && progression >= 0)
    {
        mNewProgression = progression;
    }
    else if(progression < 0)
    {
        mNewProgression = 0;
    }
    else if(progression > 1)
    {
        mNewProgression = 1;
    }

    mUpdate = true;
}

////////////////////////////////////////////////////////////
float ProgressIndicator::getProgression()
{
    return mNewProgression;
}

////////////////////////////////////////////////////////////
void ProgressIndicator::stylize()
{
    mShape.setType(mStyle.main_shape);
    mShape.setFillColor(mStyle.main_color.neutral);
    mShape.setTexture(&mStyle.main_texture);

    mBackground.setType(mStyle.background_shape);
    mBackground.setFillColor(mStyle.background_color.neutral);
    mBackground.setTexture(&mStyle.background_texture);

    if(mStyle.title)
    {
        mLabel.setFont(mStyle.title_font);
        mLabel.setFillColor(mStyle.title_color.neutral);
        mLabel.setCharacterSize(mStyle.title_size);
        mLabel.setString(mName);
        mLabel.setPosition(-mLabel.getLocalBounds().left, -mLabel.getLocalBounds().top);

        mProgression.setFont(mStyle.title_font);
        mProgression.setFillColor(mStyle.title_color.neutral);
        mProgression.setCharacterSize(mStyle.title_size);
        mProgression.setString(std::to_string(int(mNewProgression * 100)) + "%");
        mProgression.setPosition(mSize.x - mProgression.getGlobalBounds().width - mProgression.getLocalBounds().left, -mProgression.getLocalBounds().top);

        mLabel.setSize(sf::Vector2f(mSize.x - mProgression.getGlobalBounds().width * 1.3, mStyle.title_size * 1.25));

        if(!mStyle.outline)
        {
            mBackground.setSize(sf::Vector2f(mSize.x, mSize.y - mLabel.getGlobalBounds().height * 1.2));
            mBackground.setPosition(0, mLabel.getGlobalBounds().height * 1.2);
        }
        else
        {
            mBackground.setSize(sf::Vector2f(mSize.x - mStyle.outline_thickness * 2, mSize.y - mStyle.outline_thickness * 2 - mLabel.getGlobalBounds().height * 1.2));
            mBackground.setPosition(mStyle.outline_thickness, mStyle.outline_thickness + mLabel.getGlobalBounds().height * 1.2);
        }
    }
    else
    {
        if(!mStyle.outline)
        {
            mBackground.setSize({mSize.x, mSize.y});
            mBackground.setPosition(0, 0);
        }
        else
        {
            mBackground.setSize({mSize.x - mStyle.outline_thickness * 2, mSize.y - mStyle.outline_thickness * 2});
            mBackground.setPosition(mStyle.outline_thickness, mStyle.outline_thickness);
        }
    }

    if(mStyle.animation)
    {
        mShape.setSize(sf::Vector2f(mBackground.getSize().x * 0.95 * mActualProgression, mBackground.getSize().y * 0.75));
    }
    else
    {
        mShape.setSize(sf::Vector2f(mBackground.getSize().x * 0.95 * mNewProgression, mBackground.getSize().y * 0.75));
    }

    if(!mStyle.outline)
    {
        mShape.setPosition(mBackground.getSize().x / 2 - (mBackground.getSize().x * 0.95 / 2), mBackground.getPosition().y + (mBackground.getSize().y / 2) - mShape.getSize().y / 2);
    }
    else
    {
        mBackground.setOutlineColor(mStyle.outline_color.neutral);
        mBackground.setOutlineThickness(mStyle.outline_thickness);

        mShape.setPosition(mSize.x / 2 - (mBackground.getSize().x * 0.95 / 2), mBackground.getPosition().y + (mBackground.getSize().y / 2) - mShape.getSize().y / 2);
    }

    if(mNewProgression >= 1)
    {
        mNewProgression = 1;
        mShape.setFillColor(mStyle.main_color.neutral);
        mReturn = true;
    }
    else
    {
        mReturn = false;
    }
}

////////////////////////////////////////////////////////////
void ProgressIndicator::manage()
{
    if(mStyle.animation)
    {
        auto&& value_easing = ease(power::in_out<2>, mClock, mStyle.animation_duration + sf::seconds(mNewProgression - mOldProgression), mNewProgression - mOldProgression);

        mShape.setSize(sf::Vector2f(mBackground.getSize().x * 0.95 * (mOldProgression + value_easing), mBackground.getSize().y * 0.75));
        mProgression.setString(std::to_string(int((mOldProgression + value_easing) * 100)) + "%");
        mProgression.setPosition(mSize.x - mProgression.getGlobalBounds().width - mProgression.getLocalBounds().left, -mProgression.getLocalBounds().top);
        mProgression.setSize({mSize.x - mLabel.getPosition().x - mLabel.getGlobalBounds().width, mProgression.getGlobalBounds().height});

        if(value_easing == mNewProgression - mOldProgression)
        {
            mOldProgression = mNewProgression;
            mClock.restart();
        }
    }
}

////////////////////////////////////////////////////////////
void ProgressIndicator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mShape, states);
    if(mStyle.title)
    {
        target.draw(mLabel, states);
        target.draw(mProgression, states);
    }
}

} // namespace CNGui
