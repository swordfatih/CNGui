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
float Poster::easeInOutCirc(float t)
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
void Poster::update()
{
    //Updating the style of the button
    if(mUpdate)
    {
        mShape.setTexture(&mStyle.texturebackground);
        mShape.setSize(mSize);

        mBackground.setFillColor(mStyle.backgroundcolor);
        mBackground.setSize(mShape.getSize());

        mTitle.setFont(mStyle.font);
        mTitle.setCharacterSize(mStyle.charactersize);
        mTitle.setFillColor(mStyle.fillcolor);
        mTitle.setString(mName);
        mTitle.setSize(sf::Vector2f(mShape.getSize().x - mStyle.outlinethickness * 2, mTitle.getCharacterSize()));

        mDate.setFont(mStyle.font);
        mDate.setCharacterSize(mStyle.charactersize - 12);
        mDate.setFillColor(mStyle.labelcolor);
        mDate.setSize(sf::Vector2f(mTitle.getSize().x, mDate.getCharacterSize()));

        mLine.setFillColor(mStyle.outlinecolor);
        mLine.setSize(sf::Vector2f(mShape.getSize().x, mStyle.outlinethickness));

        mDescription.setFont(mStyle.outputfont);
        mDescription.setCharacterSize(mStyle.outputcharactersize);
        mDescription.setFillColor(mStyle.labelcolor);
        mDescription.setStyle(mStyle.labelstyle);
        mDescription.setSize({mTitle.getSize().x, mShape.getSize().y});

        mTitle.setPosition(mStyle.outlinethickness - mTitle.getLocalBounds().left, mShape.getPosition().y + mShape.getSize().y - mTitle.getGlobalBounds().height * 1.25 - mDate.getGlobalBounds().height - mDate.getLocalBounds().top - mTitle.getLocalBounds().top);
        mBackground.setPosition(0, mTitle.getPosition().y);
        mDate.setPosition(mStyle.outlinethickness - mDate.getLocalBounds().left, mTitle.getPosition().y + mTitle.getLocalBounds().top + mTitle.getGlobalBounds().height * 1.25 - mDate.getLocalBounds().top);
        mLine.setPosition(0, mDate.getPosition().y + mDate.getLocalBounds().top + mDate.getGlobalBounds().height + mLine.getSize().y * 2);
        mDescription.setPosition(mStyle.outlinethickness - mBackground.getLocalBounds().left, mLine.getPosition().y + mLine.getSize().y * 2 - mBackground.getLocalBounds().top);

        mUpdate = false;
    }

    //If the button is hovered
    if(sf::FloatRect(getPosition().x, getPosition().y, mShape.getSize().x, mShape.getSize().y).contains(mMouse))
    {
        mHover = true;
        mReturn = true;

        if(mTitle.getPosition().y - mTitle.getLocalBounds().top > 0)
        {
            mAnimation = mAnimation + easeInOutCirc(mClock.getElapsedTime().asSeconds() * sf::seconds(50).asSeconds());
            mTitle.setPosition(mTitle.getPosition().x, mShape.getPosition().y + mShape.getSize().y - mTitle.getGlobalBounds().height * 1.25 - mDate.getGlobalBounds().height - mDate.getLocalBounds().top - mTitle.getLocalBounds().top - mAnimation);
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
            mTitle.setPosition(mTitle.getPosition().x, mShape.getPosition().y + mShape.getSize().y - mTitle.getGlobalBounds().height * 1.25 - mDate.getGlobalBounds().height - mDate.getLocalBounds().top - mTitle.getLocalBounds().top);
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

    target.draw(mShape, states);

    glEnable(GL_SCISSOR_TEST);

    auto scissorStart = target.mapCoordsToPixel({getPosition().x, getPosition().y + mSize.y});
    auto scissorSize = target.mapCoordsToPixel({mSize.x, mSize.y});

    glScissor(scissorStart.x + mContainer->x, target.getSize().y - scissorStart.y - mContainer->y, scissorSize.x, scissorSize.y);
    target.draw(mBackground, states);
    target.draw(mLine, states);
    target.draw(mDescription, states);

    glDisable(GL_SCISSOR_TEST);

    target.draw(mTitle, states);
    target.draw(mDate, states);
}

} // namespace CNGui
