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

#include "ProgressIndicator.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
void ProgressIndicator::setProgression(float progression)
{
    if(mNewProgression < 1)
    {
        mNewProgression = progression;
        mUpdate = true;
    }
}

////////////////////////////////////////////////////////////
float ProgressIndicator::getProgression()
{
    return mNewProgression;
}

////////////////////////////////////////////////////////////
void ProgressIndicator::update()
{
    //Updating the style of the button
    if(mUpdate)
    {
        mLabel.setFont(mStyle.font);
        mLabel.setFillColor(mStyle.labelcolor);
        mLabel.setCharacterSize(mStyle.charactersize);
        mLabel.setString(mName);

        mBackground.setType(mStyle.shape);
        mBackground.setSize({mSize.x, mSize.y - mStyle.charactersize + mStyle.outlinethickness * 2});
        mBackground.setFillColor(mStyle.backgroundcolor);
        if(mStyle.outline)
        {
            mBackground.setOutlineColor(mStyle.outlinecolor);
            mBackground.setOutlineThickness(mStyle.outlinethickness);
        }
        mBackground.setPosition(0, mStyle.charactersize + mStyle.outlinethickness * 2);

        mShape.setType(mStyle.shape);
        mShape.setSize(sf::Vector2f(mBackground.getSize().x * 0.935 * mActualProgression, mBackground.getSize().y * 0.75));
        mShape.setFillColor(mStyle.fillcolor);
        if(mStyle.outline)
            mShape.setPosition(mStyle.outlinethickness + mBackground.getGlobalBounds().width * 0.01, mBackground.getPosition().y + mBackground.getGlobalBounds().height / 2 - mStyle.outlinethickness - mShape.getGlobalBounds().height / 2);
        else
            mShape.setPosition(mBackground.getGlobalBounds().width * 0.01, mBackground.getPosition().y + mBackground.getGlobalBounds().height / 2 - mShape.getGlobalBounds().height / 2);

        mProgression.setFont(mStyle.font);
        mProgression.setFillColor(mStyle.labelcolor);
        mProgression.setCharacterSize(mStyle.charactersize);
        mProgression.setString(std::to_string(int(mNewProgression * 100)) + "%");
        mProgression.setPosition(mBackground.getGlobalBounds().width - mProgression.getGlobalBounds().width, 0);

        if(mNewProgression >= 1)
        {
            mShape.setFillColor(mStyle.clickedcolor);
            mReturn = true;
        }

        mUpdate = false;
    }

    if(mActualProgression < mNewProgression)
    {
        mActualProgression += 0.01;
        mShape.setSize(sf::Vector2f(mBackground.getSize().x * 0.935 * mActualProgression, mBackground.getSize().y * 0.75));
        if(mStyle.outline)
            mShape.setPosition(mStyle.outlinethickness + mBackground.getGlobalBounds().width * 0.01, mBackground.getPosition().y + mBackground.getGlobalBounds().height / 2 - mStyle.outlinethickness - mShape.getGlobalBounds().height / 2);
        else
            mShape.setPosition(mBackground.getGlobalBounds().width * 0.01, mBackground.getPosition().y + mBackground.getGlobalBounds().height / 2 - mShape.getGlobalBounds().height / 2);
    }
}

////////////////////////////////////////////////////////////
void ProgressIndicator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mShape, states);
    target.draw(mLabel, states);
    target.draw(mProgression, states);
}

} // namespace CNGui
