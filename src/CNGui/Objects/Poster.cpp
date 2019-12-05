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
#include <CNGui/Objects/Poster.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
bool Poster::onHover()
{
    return mHover;
}

////////////////////////////////////////////////////////////
void Poster::setDescription(const std::string& description)
{
    mDescription.setString(description);
    mUpdate = true;
}

////////////////////////////////////////////////////////////
std::string Poster::getDescription()
{
    return mDescription.getString();
}

////////////////////////////////////////////////////////////
void Poster::setDate(const std::string& date)
{
    mDate.setString(date);
    mUpdate = true;
}

////////////////////////////////////////////////////////////
std::string Poster::getDate()
{
    return mDate.getString();
}

////////////////////////////////////////////////////////////
void Poster::stylize()
{
    mSprite.setTexture(mStyle.background_texture);
    mSprite.setScale(mSize.x / mSprite.getLocalBounds().width, mSize.y / mSprite.getLocalBounds().height);

    mBackground.setFillColor(mStyle.background_color.neutral);
    mBackground.setSize({mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height});

    mTitle.setFont(mStyle.title_font);
    mTitle.setCharacterSize(mStyle.title_size);
    mTitle.setFillColor(mStyle.main_color.neutral);
    mTitle.setString(mName);
    mTitle.setSize(sf::Vector2f(mSprite.getGlobalBounds().width - mStyle.outline_thickness * 2, mTitle.getCharacterSize()));

    mDate.setFont(mStyle.title_font);
    mDate.setCharacterSize(mStyle.title_size - 12);
    mDate.setFillColor(mStyle.title_color.neutral);
    mDate.setSize(sf::Vector2f(mTitle.getSize().x, mDate.getCharacterSize()));

    mLine.setFillColor(mStyle.outline_color.neutral);
    mLine.setSize(sf::Vector2f(mSprite.getGlobalBounds().width, mStyle.outline_thickness));

    mDescription.setFont(mStyle.output_font);
    mDescription.setCharacterSize(mStyle.output_size);
    mDescription.setFillColor(mStyle.output_color.neutral);
    mDescription.setStyle(mStyle.output_style);
    mDescription.setSize({mTitle.getSize().x, mSprite.getGlobalBounds().height});

    mTitle.setPosition(mStyle.outline_thickness - mTitle.getLocalBounds().left, mSprite.getPosition().y + mSprite.getGlobalBounds().height - mTitle.getGlobalBounds().height * 1.25 - mDate.getGlobalBounds().height - mDate.getLocalBounds().top - mTitle.getLocalBounds().top);
    mBackground.setPosition(0, mTitle.getPosition().y);
    mDate.setPosition(mStyle.outline_thickness - mDate.getLocalBounds().left, mTitle.getPosition().y + mTitle.getLocalBounds().top + mTitle.getGlobalBounds().height * 1.25 - mDate.getLocalBounds().top);
    mLine.setPosition(0, mDate.getPosition().y + mDate.getLocalBounds().top + mDate.getGlobalBounds().height + mLine.getSize().y * 2);
    mDescription.setPosition(mStyle.outline_thickness - mBackground.getLocalBounds().left, mLine.getPosition().y + mLine.getSize().y * 2 - mBackground.getLocalBounds().top);
}

////////////////////////////////////////////////////////////
void Poster::manage()
{
    //If the button is hovered
    if(sf::FloatRect(getPosition().x, getPosition().y, mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height).contains(mMouse))
    {
        mHover = true;
        mReturn = true;

        if(mTitle.getPosition().y - mTitle.getLocalBounds().top > 0)
        {
            mAnimation = ease(root::in_out, mClock, mStyle.animation_duration, mSprite.getGlobalBounds().height - mTitle.getGlobalBounds().height * 1.25);
            mTitle.setPosition(mTitle.getPosition().x, mSprite.getPosition().y + mSprite.getGlobalBounds().height - mTitle.getGlobalBounds().height * 1.25 - mDate.getGlobalBounds().height - mDate.getLocalBounds().top - mTitle.getLocalBounds().top - mAnimation);
        }
        else
        {
            mTitle.setPosition(mTitle.getPosition().x, 0);
        }

        mBackground.setPosition(mBackground.getPosition().x, mTitle.getPosition().y);
        mDate.setPosition(mDate.getPosition().x, mTitle.getPosition().y + mTitle.getLocalBounds().top + mTitle.getGlobalBounds().height * 1.25 - mDate.getLocalBounds().top);
        mLine.setPosition(mLine.getPosition().x, mDate.getPosition().y + mDate.getLocalBounds().top + mDate.getGlobalBounds().height + mLine.getSize().y * 2);
        mDescription.setPosition(mDescription.getPosition().x, mLine.getPosition().y + mLine.getSize().y * 2 - mBackground.getLocalBounds().top);
    }
    else
    {
        mHover = false;
        mClock.restart();

        if(mAnimation != 0)
        {
            mAnimation = 0;
            mTitle.setPosition(mTitle.getPosition().x, mSprite.getPosition().y + mSprite.getGlobalBounds().height - mTitle.getGlobalBounds().height * 1.25 - mDate.getGlobalBounds().height - mDate.getLocalBounds().top - mTitle.getLocalBounds().top);
            mBackground.setPosition(mBackground.getPosition().x, mTitle.getPosition().y);
            mDate.setPosition(mDate.getPosition().x, mTitle.getPosition().y + mTitle.getLocalBounds().top + mTitle.getGlobalBounds().height * 1.25 - mDate.getLocalBounds().top);
            mLine.setPosition(mLine.getPosition().x, mDate.getPosition().y + mDate.getLocalBounds().top + mDate.getGlobalBounds().height + mLine.getSize().y * 2);
            mDescription.setPosition(mDescription.getPosition().x, mLine.getPosition().y + mLine.getSize().y * 2 - mBackground.getLocalBounds().top);
        }
    }
}

////////////////////////////////////////////////////////////
void Poster::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    auto scissorStart = target.mapCoordsToPixel({getPosition().x, getPosition().y + mSize.y});
    auto scissorSize = target.mapCoordsToPixel({mSize.x, mSize.y});

    CNGui::Scissors scissors({scissorStart.x + mInPosition.x, target.getSize().y - scissorStart.y - mInPosition.y, scissorSize.x, scissorSize.y});

    target.draw(mSprite, states);
    target.draw(mBackground, states);
    target.draw(mLine, states);
    target.draw(mDescription, states);
    target.draw(mTitle, states);
    target.draw(mDate, states);
}

} // namespace CNGui
