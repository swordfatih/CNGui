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

#include <CNGui/Objects/LineSelect.hpp>

namespace CNGui
{
/////////////////////////////////////////////////
void LineSelect::setLines(std::vector<std::string> lines)
{
    mLines = std::move(lines);
    mUpdate = true;
}

/////////////////////////////////////////////////
void LineSelect::addLines(std::vector<std::string> lines)
{
    mLines.insert(mLines.end(), lines.begin(), lines.end());
    mUpdate = true;
}

/////////////////////////////////////////////////
void LineSelect::setValue(size_t value)
{
    if(value < mLines.size())
    {
        mValue = std::move(value);
        mUpdate = true;
    }
}

/////////////////////////////////////////////////
size_t LineSelect::getValue() const
{
    return mValue;
}

////////////////////////////////////////////////////////////
void LineSelect::stylize()
{
    mArrowLeft.setPointCount(4);
    mArrowLeft.setPoint(0, {0, 0});
    mArrowLeft.setPoint(1, {25, 20});
    mArrowLeft.setPoint(2, {0, 40});
    mArrowLeft.setPoint(3, {10, 20});

    mArrowLeft.setOrigin(mArrowLeft.getPoint(3));

    mArrowRight = mArrowLeft;

    mArrowRight.setFillColor(mStyle.main_color.neutral);
    mArrowRight.setTexture(&mStyle.main_texture);

    mArrowLeft.setFillColor(mStyle.main_color.neutral);
    mArrowLeft.setTexture(&mStyle.main_texture);

    mBackground.setType(mStyle.background_shape);
    mBackground.setFillColor(mStyle.background_color.neutral);
    mBackground.setTexture(&mStyle.background_texture);

    mOutput.setFont(mStyle.output_font);
    mOutput.setFillColor(mStyle.output_color.neutral);
    mOutput.setStyle(mStyle.output_style);
    mOutput.setCharacterSize(mStyle.output_size);

    float delta_title = 0;
    float delta_outline = 0;

    if(mStyle.outline)
    {
        delta_outline = mStyle.outline_thickness;

        mBackground.setOutlineColor(mStyle.outline_color.neutral);
        mBackground.setOutlineThickness(mStyle.outline_thickness);
    }

    if(mStyle.title)
    {
        delta_title = mSize.x / 2;

        mTitle.setString(mName);
        mTitle.setFont(mStyle.title_font);
        mTitle.setFillColor(mStyle.title_color.neutral);
        mTitle.setStyle(mStyle.title_style);
        mTitle.setCharacterSize(mStyle.title_size);
        mTitle.setSize({mSize.x / 2, mSize.y});
        mTitle.setPosition(-mTitle.getLocalBounds().left, -mTitle.getLocalBounds().top + mSize.y / 2 - mTitle.getGlobalBounds().height / 2);
        mBackground.setSize({mSize.x / 2 - delta_outline * 2, mStyle.secondary_width - delta_outline * 2});
    }
    else
    {
        mBackground.setSize({mSize.x - delta_outline * 2, mStyle.secondary_width - delta_outline * 2});
    }

    mBackground.setPosition(delta_title + delta_outline, delta_outline);

    //Arrow
    float factor = mBackground.getSize().y / 50;
    mArrowRight.setScale(factor, factor);
    mArrowLeft.setScale(-factor, factor);

    mArrowLeft.setPosition(delta_title + delta_outline + mArrowLeft.getOrigin().x * mArrowLeft.getScale().x + mArrowLeft.getGlobalBounds().width, delta_outline + mBackground.getSize().y / 2 - mArrowLeft.getGlobalBounds().height / 2 + mArrowLeft.getOrigin().y * mArrowLeft.getScale().y);
    mArrowRight.setPosition(delta_title + delta_outline + mBackground.getSize().x - mArrowRight.getGlobalBounds().width + mArrowRight.getOrigin().x * mArrowRight.getScale().x, delta_outline + mBackground.getSize().y / 2 - mArrowRight.getGlobalBounds().height / 2 + mArrowRight.getOrigin().y * mArrowRight.getScale().y);
    mOutput.setSize({mBackground.getSize().x - mArrowLeft.getGlobalBounds().width * 2 - delta_outline, mBackground.getSize().y - delta_outline});
    mOutput.setPosition(mBackground.getPosition().x - mOutput.getLocalBounds().left + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2, mBackground.getPosition().y - mOutput.getLocalBounds().top + mBackground.getSize().y / 2 - mOutput.getGlobalBounds().height / 2);
}

////////////////////////////////////////////////////////////
void LineSelect::manage()
{
    //If the shape is hovered
    if(sf::FloatRect(getPosition().x + mArrowLeft.getPosition().x - mArrowLeft.getOrigin().x, getPosition().y + mArrowLeft.getPosition().y - mArrowLeft.getOrigin().y / 2, mArrowLeft.getGlobalBounds().width, mArrowLeft.getGlobalBounds().height).contains(mMouse))
    {
        mHandleEvent.push(this, "hover_left");
        mArrowLeft.setFillColor(mStyle.main_color.hovered);
    }
    else if(sf::FloatRect(getPosition().x + mArrowRight.getPosition().x - mArrowRight.getOrigin().x / 2, getPosition().y + mArrowRight.getPosition().y - mArrowRight.getOrigin().y / 2, mArrowRight.getGlobalBounds().width, mArrowRight.getGlobalBounds().height).contains(mMouse))
    {
        mHandleEvent.push(this, "hover_right");
        mArrowRight.setFillColor(mStyle.main_color.hovered);
    }

    if(mHandleEvent.active(this, "hover_left") || mHandleEvent.active(this, "hover_right"))
    {
        mHandleEvent.push(this, "hover");
        mOutput.setFillColor(mStyle.output_color.hovered);
        mTitle.setFillColor(mStyle.title_color.hovered);
    }
    else if(!mReturn)
    {
        mArrowLeft.setFillColor(mStyle.main_color.neutral);
        mArrowRight.setFillColor(mStyle.main_color.neutral);
        mOutput.setFillColor(mStyle.output_color.neutral);
        mTitle.setFillColor(mStyle.title_color.neutral);
    }

    //Button is pressed
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto event_mouse = mHandleEvent.get_if(sf::Event::MouseButtonPressed);
        if(event_mouse && event_mouse->mouseButton.button == sf::Mouse::Left)
        {
            mHandleEvent.push(this, "click");
            mReturn = true;

            if(mHandleEvent.active(this, "hover_left"))
            {
                if(mValue == 0)
                {
                    mValue = mLines.size() - 1;
                }
                else
                {
                    mValue -= 1;
                }
            }
            else if(mHandleEvent.active(this, "hover_right"))
            {
                if(mValue == mLines.size() - 1)
                {
                    mValue = 0;
                }
                else
                {
                    mValue += 1;
                }
            }
        }

        if(mReturn)
        {
            if(mHandleEvent.active(this, "hover_left"))
            {
                mArrowLeft.setFillColor(mStyle.main_color.clicked);
            }
            else if(mHandleEvent.active(this, "hover_right"))
            {
                mArrowRight.setFillColor(mStyle.main_color.clicked);
            }
        }
    }
    else
    {
        mReturn = false;
    }

    mOutput.setCharacterSize(mStyle.output_size);
    mOutput.setString(mLines[mValue]);
    mOutput.setPosition(mBackground.getPosition().x - mOutput.getLocalBounds().left + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2, mBackground.getPosition().y - mOutput.getLocalBounds().top + mBackground.getSize().y / 2 - mOutput.getGlobalBounds().height / 2);
}

////////////////////////////////////////////////////////////
void LineSelect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mOutput, states);
    target.draw(mArrowLeft, states);
    target.draw(mArrowRight, states);
    target.draw(mTitle, states);
}

} // namespace CNGui

