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

#include <CNGui/Objects/LineEdit.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
bool LineEdit::onReturn()
{
    return mOnReturn;
}

////////////////////////////////////////////////////////////
void LineEdit::clear()
{
    mString.clear();
    mPositionCursor = 0;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
std::string LineEdit::getString()
{
    return mString;
}

////////////////////////////////////////////////////////////
void LineEdit::setDefaultString(const std::string& string)
{
    mDefault = string;
    mUpdate = true;
}

////////////////////////////////////////////////////////////
LineEdit& LineEdit::operator >>(std::string& output)
{
    output = mString;
    return *this;
}

////////////////////////////////////////////////////////////
void LineEdit::stylize()
{
    //Background
    mBackground.setType(mStyle.background_shape);
    mBackground.setFillColor(mStyle.background_color.neutral);
    mBackground.setTexture(&mStyle.background_texture);

    if(!mStyle.outline)
    {
        mBackground.setSize(mSize);
    }
    else
    {
        mBackground.setSize({mSize.x - mStyle.outline_thickness * 2, mSize.y - mStyle.outline_thickness * 2});
        mBackground.setPosition(mStyle.outline_thickness, mStyle.outline_thickness);
        mBackground.setOutlineColor(mStyle.outline_color.neutral);
        mBackground.setOutlineThickness(mStyle.outline_thickness);
    }

    //Shape
    mShape.setType(CNGui::Shape::Rectangle);
    mShape.setFillColor(mStyle.main_color.neutral);
    mShape.setSize(sf::Vector2f(mBackground.getSize().x, 2));

    if(!mStyle.outline)
    {
        mShape.setPosition(0, mBackground.getSize().y - mShape.getSize().y);
    }
    else
    {
        mShape.setPosition(mStyle.outline_thickness, mStyle.outline_thickness + mBackground.getSize().y - mShape.getSize().y);
    }

    //Texts
    mOutput.setFont(mStyle.output_font);
    mOutput.setFillColor(mStyle.output_color.neutral);

    if(mFirst)
    {
        mOutput.setStyle(CNGui::Text::Italic);
    }
    else
    {
        mOutput.setStyle(CNGui::Text::Regular);
    }

    mOutput.setString("pb");
    mOutput.setCharacterSize(mStyle.output_size);
    mOutput.setPosition(-mOutput.getLocalBounds().left, mShape.getPosition().y - mShape.getGlobalBounds().height - mOutput.getGlobalBounds().height - mOutput.getLocalBounds().top);

    if(mStyle.title)
    {
        mLabel.setFont(mStyle.title_font);
        mLabel.setFillColor(mStyle.title_color.neutral);
        mLabel.setStyle(mStyle.title_style);
        mLabel.setCharacterSize(mStyle.title_size);
        mLabel.setString(mName);
        mLabel.setSize(sf::Vector2f(mBackground.getSize().x, mStyle.title_size * 1.25));

        if(!mStyle.outline)
        {
            mLabel.setPosition(-mLabel.getLocalBounds().left, -mLabel.getLocalBounds().top);
        }
        else
        {
            mLabel.setPosition(mStyle.outline_thickness - mLabel.getLocalBounds().left, mStyle.outline_thickness - mLabel.getLocalBounds().top);
        }
    }

    //Cursor
    mCursor.setType(CNGui::Shape::Rectangle);
    mCursor.setFillColor(sf::Color::Transparent);
    mCursor.setSize(sf::Vector2f(1, mOutput.getGlobalBounds().height));
    mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mOutput.getPosition().y + mCursor.getSize().y / 4);

    if(mFirst)
    {
        mOutput.setString(mDefault);
    }
    else
    {
        mStyle.output_hide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.output_hide));
    }
}

////////////////////////////////////////////////////////////
void LineEdit::manage()
{
    //If the line edit is hovered
    if(sf::FloatRect(getPosition().x, getPosition().y, mBackground.getGlobalBounds().width, mBackground.getGlobalBounds().height).contains(mMouse))
    {
        //Object is pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mShape.setFillColor(mStyle.main_color.clicked);
            mBackground.setFillColor(mStyle.background_color.clicked);
            mBackground.setOutlineColor(mStyle.outline_color.clicked);
            mLabel.setFillColor(mStyle.title_color.clicked);
            mOutput.setFillColor(mStyle.output_color.clicked);
            mOutput.setStyle(mStyle.output_style);
            mCursor.setFillColor(sf::Color::White);
            mShape.setSize(sf::Vector2f(mBackground.getSize().x, 3));

            mStyle.output_hide == ' ' ? mOutput.setString(mString.substr(0, mString.size() - mPositionCursor)) : mOutput.setString(std::string(mString.size() - mPositionCursor, mStyle.output_hide));
            mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mCursor.getPosition().y);
            mStyle.output_hide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.output_hide));

            if(mFirst)
            {
                mFirst = false;
            }

            mReturn = true;
        }
    }
    else
    {
        //Button is pressed out of the object
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mReturn)
        {
            mShape.setFillColor(mStyle.main_color.neutral);
            mBackground.setFillColor(mStyle.background_color.neutral);
            mBackground.setOutlineColor(mStyle.outline_color.neutral);
            mLabel.setFillColor(mStyle.title_color.neutral);
            mOutput.setFillColor(mStyle.output_color.neutral);
            mCursor.setFillColor(sf::Color::Transparent);
            mShape.setSize(sf::Vector2f(mBackground.getSize().x, 2));

            mReturn = false;
        }
    }

    //If object is selected
    if(mReturn)
    {
        mOnReturn = false;
        bool updatePosition = false;

        if(auto event = mHandleEvent.get_if(sf::Event::KeyPressed))
        {
            if(event->key.code == sf::Keyboard::Left && mPositionCursor < mString.size())
            {
                mPositionCursor += 1;
                updatePosition = true;
            }
            else if(event->key.code == sf::Keyboard::Right && mPositionCursor > 0)
            {
                mPositionCursor -= 1;
                updatePosition = true;
            }
            else if(event->key.code == sf::Keyboard::Delete && mPositionCursor > 0)
            {
                mString.erase(mString.end() - mPositionCursor);
                mPositionCursor -= 1;
                updatePosition = true;
            }
            else if(event->key.control && event->key.code == sf::Keyboard::C)
            {
                sf::Clipboard::setString(mString);
            }
            else if(event->key.control && event->key.code == sf::Keyboard::V)
            {
                mString.insert(mString.size() - mPositionCursor, sf::Clipboard::getString());
                mStyle.output_hide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.output_hide));
            }
        }

        if(auto event = mHandleEvent.get_if(sf::Event::TextEntered))
        {
            //Handle input
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {
                if(mPositionCursor < mString.size())
                {
                    mString.erase(mString.size() - mPositionCursor - 1, 1);
                }
            }
            else
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    mOnReturn = true;
                }
                else if(auto event_key = mHandleEvent.get_if(sf::Event::KeyPressed); !(event_key->key.control && (event_key->key.code == sf::Keyboard::C || event_key->key.code == sf::Keyboard::V)))
                {
                    mString.insert(mString.size() - mPositionCursor, 1, static_cast<char>(event->text.unicode));
                }
            }

            mStyle.output_hide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.output_hide));

            updatePosition = true;
        }
        else
        {
            //Animation
            if(mStyle.animation && mAnimation.getElapsedTime().asMilliseconds() > 500)
            {
                mCursor.getFillColor() == sf::Color::White ? mCursor.setFillColor(sf::Color::Transparent) : mCursor.setFillColor(sf::Color::White);
                mAnimation.restart();
            }
        }

        if(updatePosition)
        {
            mStyle.output_hide == ' ' ? mOutput.setString(mString.substr(0, mString.size() - mPositionCursor)) : mOutput.setString(std::string(mString.size() - mPositionCursor, mStyle.output_hide));

            sf::Vector2f position = {0, mOutput.getPosition().y};

            if(!mStyle.outline)
            {
                position.x = -mOutput.getLocalBounds().left;
            }
            else
            {
                position.x = -mOutput.getLocalBounds().left + mStyle.outline_thickness;
            }

            if(mOutput.getGlobalBounds().width > mSize.x)
            {
                position.x -= mOutput.getGlobalBounds().width - mSize.x + mSize.x * 0.02;
            }

            mCursor.setFillColor(sf::Color::White);
            mOutput.setPosition(position);
            mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mCursor.getPosition().y);

            mStyle.output_hide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.output_hide));
        }
    }
}

////////////////////////////////////////////////////////////
void LineEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mLabel, states);

    auto scissorStart = target.mapCoordsToPixel({getPosition().x, getPosition().y + mSize.y});
    auto scissorSize = target.mapCoordsToPixel({mSize.x, mSize.y});

    {
        CNGui::Scissors scissors({scissorStart.x + mInPosition.x, target.getSize().y - scissorStart.y - mInPosition.y, scissorSize.x, scissorSize.y});
        target.draw(mOutput, states);
    }

    target.draw(mCursor, states);
    target.draw(mShape, states);
}

} // namespace CNGui
