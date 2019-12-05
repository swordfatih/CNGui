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

#include <CNGui/Objects/Slider.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
inline float round(float number, float round)
{
    return std::floor(number / round) * round;
}

////////////////////////////////////////////////////////////
void Slider::setRange(const sf::Vector2f& range)
{
    mRange = std::move(range);
    mValue = mRange.x;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
void Slider::setValue(float value)
{
    if(value >= mRange.x && value <= mRange.y)
    {
        mValue = std::move(value);
        mUpdate = true;
    }
}

////////////////////////////////////////////////////////////
float Slider::getValue() const
{
    return mValue;
}

////////////////////////////////////////////////////////////
void Slider::setStep(float step)
{
    mStep = std::move(step);
}

////////////////////////////////////////////////////////////
float Slider::getStep() const
{
    return mStep;
}

////////////////////////////////////////////////////////////
void Slider::stylize()
{
    mShape.setType(mStyle.main_shape);
    mShape.setFillColor(mStyle.main_color.neutral);
    mShape.setTexture(&mStyle.main_texture);

    mProgression.setType(mStyle.secondary_shape);
    mProgression.setFillColor(mStyle.secondary_color.neutral);
    mProgression.setTexture(&mStyle.secondary_texture);

    mBackground.setType(mStyle.background_shape);
    mBackground.setFillColor(mStyle.background_color.neutral);
    mBackground.setTexture(&mStyle.background_texture);

    mOutput.setFont(mStyle.output_font);
    mOutput.setFillColor(mStyle.output_color.neutral);
    mOutput.setStyle(mStyle.output_style);
    mOutput.setCharacterSize(mStyle.output_size);

    float delta_title = 0;
    float delta_outline = 0;

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
    }

    if(mStyle.outline)
    {
        delta_outline = mStyle.outline_thickness;

        mBackground.setOutlineColor(mStyle.outline_color.neutral);
        mBackground.setOutlineThickness(mStyle.outline_thickness);
    }

    mShape.setSize({mSize.y - delta_outline * 2, mSize.y - delta_outline * 2});
    mBackground.setPosition(delta_title + delta_outline + mShape.getSize().x / 2, delta_outline);

    if(mStyle.title)
    {
        mBackground.setSize({mSize.x / 2 - mShape.getSize().x - delta_outline * 2, mStyle.secondary_width - delta_outline * 2});
    }
    else
    {
        mBackground.setSize({mSize.x - mShape.getSize().x - delta_outline * 2, mStyle.secondary_width - delta_outline * 2});
    }

    mShape.setPosition(delta_title + delta_outline + mBackground.getSize().x * ((mValue + std::abs(mRange.x)) / (mRange.y + std::abs(mRange.x))), delta_outline);
    mProgression.setPosition(delta_title + delta_outline + mShape.getSize().x / 2, mSize.y / 2 - mBackground.getSize().y / 2 + delta_outline / 2);
    mProgression.setSize({mShape.getPosition().x - mProgression.getPosition().x + mShape.getSize().x / 2, mBackground.getSize().y});
    mOutput.setSize({mBackground.getSize()});
    mOutput.setPosition(mBackground.getPosition().x - mOutput.getLocalBounds().left + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2, mBackground.getPosition().y - mOutput.getLocalBounds().top + mBackground.getSize().y / 2 - mOutput.getGlobalBounds().height / 2);
}

////////////////////////////////////////////////////////////
void Slider::manage()
{
    //If the shape is hovered
    if(sf::FloatRect(getPosition().x + mShape.getPosition().x, getPosition().y + mShape.getPosition().y, mShape.getSize().x, mShape.getSize().y).contains(mMouse))
    {
        mHandleEvent.push(this, "hover");
        mShape.setFillColor(mStyle.main_color.hovered);
        mOutput.setFillColor(mStyle.output_color.hovered);
        mTitle.setFillColor(mStyle.title_color.hovered);
    }

    //Button is pressed
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto event_mouse = mHandleEvent.get_if(sf::Event::MouseButtonPressed);
        if(event_mouse && event_mouse->mouseButton.button == sf::Mouse::Left && mHandleEvent.active(this, "hover"))
        {
            mHandleEvent.push(this, "click");

            mReturn = true;
            mPositionClick = mMouse.x - getPosition().x - mShape.getPosition().x;
        }

        if(mReturn)
        {
            mHandleEvent.push(this, "slide");

            mShape.setFillColor(mStyle.main_color.clicked);
            mOutput.setFillColor(mStyle.output_color.clicked);
            mTitle.setFillColor(mStyle.title_color.clicked);

            mShape.setPosition(round(mMouse.x - getPosition().x - mPositionClick, (mBackground.getSize().x + mShape.getSize().x / 2) / (mRange.y + std::abs(mRange.x)) * mStep), mShape.getPosition().y);

            if(mShape.getPosition().x < mBackground.getPosition().x - mShape.getSize().x / 2)
            {
                mShape.setPosition(mBackground.getPosition().x - mShape.getSize().x / 2, mShape.getPosition().y);
            }

            if(mShape.getPosition().x > mBackground.getPosition().x + mBackground.getSize().x - mShape.getSize().x / 2)
            {
                mShape.setPosition(mBackground.getPosition().x + mBackground.getSize().x - mShape.getSize().x / 2, mShape.getPosition().y);
            }

            mProgression.setSize({mShape.getPosition().x - mProgression.getPosition().x + mShape.getSize().x / 2, mProgression.getSize().y});

            mValue = round(mRange.x + (mProgression.getSize().x / mBackground.getSize().x) * (mRange.y + std::abs(mRange.x)), mStep);

            if(mProgression.getSize().x / mBackground.getSize().x == 1)
            {
                mValue = mRange.y;
            }
        }
    }
    else
    {
        mReturn = false;
    }

    auto value = std::to_string(mValue);
    value.erase(value.begin() + value.find_first_of('.') + 2, value.end());

    mOutput.setString(value);
    mOutput.setPosition(mBackground.getPosition().x - mOutput.getLocalBounds().left + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2, mBackground.getPosition().y - mOutput.getLocalBounds().top + mBackground.getSize().y / 2 - mOutput.getGlobalBounds().height / 2);

    if(!mHandleEvent.active(this, "hover") && !mReturn)
    {
        mShape.setFillColor(mStyle.main_color.neutral);
        mOutput.setFillColor(mStyle.output_color.neutral);
        mTitle.setFillColor(mStyle.title_color.neutral);
    }
}

////////////////////////////////////////////////////////////
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mProgression, states);
    target.draw(mOutput, states);
    target.draw(mShape, states);
    target.draw(mTitle, states);
}

} // namespace CNGui
