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
    float delta_outline = 0;
    float delta_title = 0;

    if(mStyle.outline)
    {
        delta_outline = mStyle.outline_thickness;

        mBackground.setOutlineColor(mStyle.outline_color.neutral);
        mBackground.setOutlineThickness(mStyle.outline_thickness);
    }

    mBackground.setType(mStyle.background_shape);
    mBackground.setFillColor(mStyle.background_color.neutral);
    mBackground.setTexture(&mStyle.background_texture);
    mBackground.setSize({mSize.x - delta_outline * 2, mSize.y - delta_outline * 2});
    mBackground.setPosition(delta_outline, delta_outline);

    if(mStyle.title)
    {
        mTitle.setFont(mStyle.title_font);
        mTitle.setFillColor(mStyle.title_color.neutral);
        mTitle.setStyle(mStyle.title_style);
        mTitle.setCharacterSize(mStyle.title_size);
        mTitle.setString(mName);
        mTitle.setSize(sf::Vector2f(mBackground.getSize().x, mStyle.title_size * 1.25));
        mTitle.setPosition(delta_outline - mTitle.getLocalBounds().left, delta_outline - mTitle.getLocalBounds().top);

        delta_title = mTitle.getGlobalBounds().height;
    }

    mShape.setType(CNGui::Shape::Rectangle);
    mShape.setFillColor(mStyle.main_color.neutral);
    mShape.setSize({mBackground.getSize().x, 2});
    mShape.setPosition(delta_outline, mBackground.getPosition().y + mBackground.getSize().y - mShape.getSize().y);

    mFirst ? mOutput.setStyle(CNGui::Text::Italic) : mOutput.setStyle(CNGui::Text::Regular);
    mOutput.setFont(mStyle.output_font);
    mOutput.setFillColor(mStyle.output_color.neutral);
    mOutput.setCharacterSize(mStyle.output_size);
    mOutput.setString("pb");
    mOutput.setPosition(-mOutput.getLocalBounds().left + delta_outline, mShape.getPosition().y - mShape.getGlobalBounds().height - mOutput.getGlobalBounds().height - mOutput.getLocalBounds().top);

    //Cursor
    mCursor.setType(CNGui::Shape::Rectangle);
    mCursor.setFillColor(sf::Color::Transparent);
    mCursor.setSize(sf::Vector2f(1, mOutput.getGlobalBounds().height));

    if(mFirst)
    {
        mOutput.setString(mDefault);
    }
    else
    {
        mStyle.output_hide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.output_hide));
    }

    sf::Vector2f position = {-mOutput.getLocalBounds().left + delta_outline, mOutput.getPosition().y};

    if(mOutput.getGlobalBounds().width > mBackground.getSize().x)
    {
        position.x -= mOutput.getGlobalBounds().width - mBackground.getSize().x + mCursor.getSize().x * 2;
    }

    mOutput.setPosition(position);
    mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mShape.getPosition().y - mCursor.getSize().y * 1.25);
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
            mTitle.setFillColor(mStyle.title_color.clicked);
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
            mTitle.setFillColor(mStyle.title_color.neutral);
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

            sf::Vector2f position = {-mOutput.getLocalBounds().left, mOutput.getPosition().y};

            if(mStyle.outline)
            {
                position.x += mStyle.outline_thickness;
            }

            if(mOutput.getGlobalBounds().width > mBackground.getSize().x)
            {
                position.x -= mOutput.getGlobalBounds().width - mBackground.getSize().x + mCursor.getSize().x * 2;
            }

            mCursor.setFillColor(sf::Color::White);
            mOutput.setPosition(position);
            mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mShape.getPosition().y - mCursor.getSize().y * 1.25);
            mStyle.output_hide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.output_hide));
        }
    }
}

////////////////////////////////////////////////////////////
void LineEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mTitle, states);

    auto scissorStart = target.mapCoordsToPixel({getPosition().x + mBackground.getPosition().x, getPosition().y + mBackground.getPosition().y + mBackground.getSize().y});
    auto scissorSize = target.mapCoordsToPixel({mBackground.getSize()});

    {
        CNGui::Scissors scissors({scissorStart.x + mInPosition.x, target.getSize().y - scissorStart.y - mInPosition.y, scissorSize.x, scissorSize.y});
        target.draw(mOutput, states);
    }

    target.draw(mCursor, states);
    target.draw(mShape, states);
}

} // namespace CNGui
