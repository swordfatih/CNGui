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

#include "CNGui/Objects/ProgressIndicator.hpp"

namespace CNGui
{
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
float ProgressIndicator::easeInOutCirc(float t)
{
    if(t < 0.5)
    {
        return (1 - sqrt(1 - 2 * t)) * 0.5;
    }
    else
    {
        return (1 + sqrt(2 * t - 1)) * 0.5;
    }
}

////////////////////////////////////////////////////////////
void ProgressIndicator::update()
{
    //Updating the style of the button
    if(mUpdate)
    {
        mShape.setType(mStyle.shape);
        mShape.setFillColor(mStyle.fillcolor);

        mBackground.setType(mStyle.shape);
        mBackground.setFillColor(mStyle.backgroundcolor);
        mBackground.setTexture(&mStyle.texturebackground);

        if(mStyle.label)
        {
            mLabel.setFont(mStyle.font);
            mLabel.setFillColor(mStyle.labelcolor);
            mLabel.setCharacterSize(mStyle.charactersize);
            mLabel.setString(mName);

            mProgression.setFont(mStyle.font);
            mProgression.setFillColor(mStyle.labelcolor);
            mProgression.setCharacterSize(mStyle.charactersize);
            mProgression.setString(std::to_string(int(mNewProgression * 100)) + "%");
            mProgression.setPosition(mSize.x - mProgression.getGlobalBounds().width, 0);

            if(!mStyle.outline)
            {
                mBackground.setSize(sf::Vector2f(mSize.x, mSize.y - mStyle.charactersize * 1.25));
                mBackground.setPosition(0, mStyle.charactersize * 1.25);
            }
            else
            {
                mBackground.setSize(sf::Vector2f(mSize.x - mStyle.outlinethickness * 2, mSize.y - (mStyle.charactersize * 1.25 + mStyle.outlinethickness * 2)));
                mBackground.setPosition(mStyle.outlinethickness, mStyle.outlinethickness + mStyle.charactersize * 1.25);
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
                mBackground.setSize({mSize.x - mStyle.outlinethickness * 2, mSize.y - mStyle.outlinethickness * 2});
                mBackground.setPosition(mStyle.outlinethickness, mStyle.outlinethickness);
            }
        }

        if(mStyle.animated)
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
            mBackground.setOutlineColor(mStyle.outlinecolor);
            mBackground.setOutlineThickness(mStyle.outlinethickness);

            mShape.setPosition(mSize.x / 2 - (mBackground.getSize().x * 0.95 / 2), mBackground.getPosition().y + (mBackground.getSize().y / 2) - mShape.getSize().y / 2);
        }

        if(mNewProgression >= 1)
        {
            mNewProgression = 1;
            mShape.setFillColor(mStyle.clickedcolor);
            mReturn = true;
        }
        else
        {
            mReturn = false;
        }

        mUpdate = false;
    }

    if(mStyle.animated && mOldProgression != mNewProgression)
    {
        if(mOldProgression < mNewProgression)
        {
            mActualProgression = mOldProgression + easeInOutCirc(mClock.getElapsedTime().asSeconds() / mStyle.durationanimation.asSeconds());
            if(mActualProgression > mNewProgression)
            {
                mActualProgression = mNewProgression;
                mOldProgression = mNewProgression;
            }
        }
        else
        {
            mActualProgression = mOldProgression - easeInOutCirc(mClock.getElapsedTime().asSeconds() / mStyle.durationanimation.asSeconds());
            if(mActualProgression < mNewProgression)
            {
                mActualProgression = mNewProgression;
                mOldProgression = mNewProgression;
            }
        }

        mShape.setSize(sf::Vector2f(mBackground.getSize().x * 0.95 * mActualProgression, mBackground.getSize().y * 0.75));
    }
    else
    {
        mClock.restart();
    }
}

////////////////////////////////////////////////////////////
void ProgressIndicator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mShape, states);
    if(mStyle.label)
    {
        target.draw(mLabel, states);
        target.draw(mProgression, states);
    }
}

} // namespace CNGui
