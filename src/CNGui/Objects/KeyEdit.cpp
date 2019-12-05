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

#include <CNGui/Objects/KeyEdit.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
inline std::string key_to_string(const sf::Keyboard::Key& key)
{
    switch(key)
    {
    case sf::Keyboard::Unknown:
        return "Unknown";
    case sf::Keyboard::A:
        return "A";
    case sf::Keyboard::B:
        return "B";
    case sf::Keyboard::C:
        return "C";
    case sf::Keyboard::D:
        return "D";
    case sf::Keyboard::E:
        return "E";
    case sf::Keyboard::F:
        return "F";
    case sf::Keyboard::G:
        return "G";
    case sf::Keyboard::H:
        return "H";
    case sf::Keyboard::I:
        return "I";
    case sf::Keyboard::J:
        return "J";
    case sf::Keyboard::K:
        return "K";
    case sf::Keyboard::L:
        return "L";
    case sf::Keyboard::M:
        return "M";
    case sf::Keyboard::N:
        return "N";
    case sf::Keyboard::O:
        return "O";
    case sf::Keyboard::P:
        return "P";
    case sf::Keyboard::Q:
        return "Q";
    case sf::Keyboard::R:
        return "R";
    case sf::Keyboard::S:
        return "S";
    case sf::Keyboard::T:
        return "T";
    case sf::Keyboard::U:
        return "U";
    case sf::Keyboard::V:
        return "V";
    case sf::Keyboard::W:
        return "W";
    case sf::Keyboard::X:
        return "X";
    case sf::Keyboard::Y:
        return "Y";
    case sf::Keyboard::Z:
        return "Z";
    case sf::Keyboard::Num0:
        return "Num0";
    case sf::Keyboard::Num1:
        return "Num1";
    case sf::Keyboard::Num2:
        return "Num2";
    case sf::Keyboard::Num3:
        return "Num3";
    case sf::Keyboard::Num4:
        return "Num4";
    case sf::Keyboard::Num5:
        return "Num5";
    case sf::Keyboard::Num6:
        return "Num6";
    case sf::Keyboard::Num7:
        return "Num7";
    case sf::Keyboard::Num8:
        return "Num8";
    case sf::Keyboard::Num9:
        return "Num9";
    case sf::Keyboard::Escape:
        return "Escape";
    case sf::Keyboard::LControl:
        return "LControl";
    case sf::Keyboard::LShift:
        return "LShift";
    case sf::Keyboard::LAlt:
        return "LAlt";
    case sf::Keyboard::LSystem:
        return "LSystem";
    case sf::Keyboard::RControl:
        return "RControl";
    case sf::Keyboard::RShift:
        return "RShift";
    case sf::Keyboard::RAlt:
        return "RAlt";
    case sf::Keyboard::RSystem:
        return "RSystem";
    case sf::Keyboard::Menu:
        return "Menu";
    case sf::Keyboard::LBracket:
        return "LBracket";
    case sf::Keyboard::RBracket:
        return "RBracket";
    case sf::Keyboard::Semicolon:
        return "Semicolon";
    case sf::Keyboard::Comma:
        return "Comma";
    case sf::Keyboard::Period:
        return "Period";
    case sf::Keyboard::Quote:
        return "Quote";
    case sf::Keyboard::Slash:
        return "Slash";
    case sf::Keyboard::Backslash:
        return "Backslash";
    case sf::Keyboard::Tilde:
        return "Tilde";
    case sf::Keyboard::Equal:
        return "Equal";
    case sf::Keyboard::Hyphen:
        return "Hyphen";
    case sf::Keyboard::Space:
        return "Space";
    case sf::Keyboard::Enter:
        return "Enter";
    case sf::Keyboard::Backspace:
        return "Backspace";
    case sf::Keyboard::Tab:
        return "Tab";
    case sf::Keyboard::PageUp:
        return "PageUp";
    case sf::Keyboard::PageDown:
        return "PageDown";
    case sf::Keyboard::End:
        return "End";
    case sf::Keyboard::Home:
        return "Home";
    case sf::Keyboard::Insert:
        return "Insert";
    case sf::Keyboard::Delete:
        return "Delete";
    case sf::Keyboard::Add:
        return "Add";
    case sf::Keyboard::Subtract:
        return "Subtract";
    case sf::Keyboard::Multiply:
        return "Multiply";
    case sf::Keyboard::Divide:
        return "Divide";
    case sf::Keyboard::Left:
        return "Left";
    case sf::Keyboard::Right:
        return "Right";
    case sf::Keyboard::Up:
        return "Up";
    case sf::Keyboard::Down:
        return "Down";
    case sf::Keyboard::Numpad0:
        return "Numpad0";
    case sf::Keyboard::Numpad1:
        return "Numpad1";
    case sf::Keyboard::Numpad2:
        return "Numpad2";
    case sf::Keyboard::Numpad3:
        return "Numpad3";
    case sf::Keyboard::Numpad4:
        return "Numpad4";
    case sf::Keyboard::Numpad5:
        return "Numpad5";
    case sf::Keyboard::Numpad6:
        return "Numpad6";
    case sf::Keyboard::Numpad7:
        return "Numpad7";
    case sf::Keyboard::Numpad8:
        return "Numpad8";
    case sf::Keyboard::Numpad9:
        return "Numpad9";
    case sf::Keyboard::F1:
        return "F1";
    case sf::Keyboard::F2:
        return "F2";
    case sf::Keyboard::F3:
        return "F3";
    case sf::Keyboard::F4:
        return "F4";
    case sf::Keyboard::F5:
        return "F5";
    case sf::Keyboard::F6:
        return "F6";
    case sf::Keyboard::F7:
        return "F7";
    case sf::Keyboard::F8:
        return "F8";
    case sf::Keyboard::F9:
        return "F9";
    case sf::Keyboard::F10:
        return "F10";
    case sf::Keyboard::F11:
        return "F11";
    case sf::Keyboard::F12:
        return "F12";
    case sf::Keyboard::F13:
        return "F13";
    case sf::Keyboard::F14:
        return "F14";
    case sf::Keyboard::F15:
        return "F15";
    case sf::Keyboard::Pause:
        return "Pause";
    case sf::Keyboard::KeyCount:
        return "KeyCount";
    default:
        return "Unknown";
    }

    return "Unknown";
}

////////////////////////////////////////////////////////////
void KeyEdit::reset(sf::Keyboard::Key key)
{
    mOutput.setString(key_to_string(static_cast<sf::Keyboard::Key>(mKey = std::move(key))));
}

////////////////////////////////////////////////////////////
sf::Keyboard::Key KeyEdit::getKey()
{
    return mKey;
}

////////////////////////////////////////////////////////////
sf::Keyboard::Key KeyEdit::getPrevious()
{
    return mPrevious;
}

////////////////////////////////////////////////////////////
void KeyEdit::error(std::string message)
{
    mOutput.setString(std::move(message));
    mOutput.setPosition(mBackground.getPosition().x + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2 - mOutput.getLocalBounds().left, mSize.y / 2 - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
}

////////////////////////////////////////////////////////////
void KeyEdit::stylize()
{
    mBackground.setFillColor(mStyle.main_color.neutral);
    mBackground.setType(mStyle.main_shape);
    mBackground.setTexture(&mStyle.main_texture);

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
        mBackground.setSize({mSize.x / 2 - delta_outline * 2, mSize.y - delta_outline * 2});
    }
    else
    {
        mBackground.setSize({mSize.x - delta_outline * 2, mSize.y - delta_outline * 2});
    }

    mBackground.setPosition(delta_title + delta_outline, delta_outline);

    mOutput.setSize(mBackground.getSize());
    mOutput.setString(key_to_string(static_cast<sf::Keyboard::Key>(mKey)));
    mOutput.setPosition(mBackground.getPosition().x + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2 - mOutput.getLocalBounds().left, mSize.y / 2 - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
}

////////////////////////////////////////////////////////////
void KeyEdit::manage()
{
    if(!mReturn)
    {
        if(sf::FloatRect(getPosition().x + mBackground.getPosition().x, getPosition().y + mBackground.getPosition().y, mBackground.getSize().x, mBackground.getSize().y).contains(mMouse))
        {
            mBackground.setFillColor(mStyle.main_color.hovered);
            mOutput.setFillColor(mStyle.output_color.hovered);
            mTitle.setFillColor(mStyle.title_color.hovered);

            if(mStyle.outline)
            {
                mBackground.setOutlineColor(mStyle.outline_color.hovered);
            }

            mHandleEvent.push(this, "hover");
        }
        else
        {
            mBackground.setFillColor(mStyle.main_color.neutral);
            mOutput.setFillColor(mStyle.output_color.neutral);
            mTitle.setFillColor(mStyle.title_color.neutral);

            if(mStyle.outline)
            {
                mBackground.setOutlineColor(mStyle.outline_color.neutral);
            }
        }
    }

    if(auto event = mHandleEvent.get_if(sf::Event::MouseButtonPressed); event && event->mouseButton.button == sf::Mouse::Left)
    {
        if(mHandleEvent.active(this, "hover"))
        {
            mHandleEvent.push(this, "click");

            mReturn = true;
            mOutput.setString("");

            mBackground.setFillColor(mStyle.main_color.clicked);
            mOutput.setFillColor(mStyle.output_color.clicked);
            mTitle.setFillColor(mStyle.title_color.clicked);

            if(mStyle.outline)
            {
                mBackground.setOutlineColor(mStyle.outline_color.clicked);
            }
        }
        else
        {
            mReturn = false;
            mOutput.setString(key_to_string(static_cast<sf::Keyboard::Key>(mKey)));
        }

        mOutput.setPosition(mBackground.getPosition().x + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2 - mOutput.getLocalBounds().left, mSize.y / 2 - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
    }

    if(mReturn)
    {
        mHandleEvent.push(this, "reading");

        if(mClockAnimation.getElapsedTime() > mStyle.animation_duration && mStyle.animation)
        {
            mOutput.setString(mOutput.getString() + '.');

            if(mOutput.getString().getSize() > 4)
            {
                mOutput.setString("");
            }

            mOutput.setPosition(mBackground.getPosition().x + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2 - mOutput.getLocalBounds().left, mSize.y / 2 - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);

            mClockAnimation.restart();
        }

        if(auto event = mHandleEvent.get_if(sf::Event::KeyPressed))
        {
            mPrevious = mKey;
            mBackground.setFillColor(mStyle.main_color.neutral);
            mOutput.setFillColor(mStyle.output_color.neutral);
            mTitle.setFillColor(mStyle.title_color.neutral);

            if(mStyle.outline)
            {
                mBackground.setOutlineColor(mStyle.outline_color.neutral);
            }

            mOutput.setString(key_to_string(static_cast<sf::Keyboard::Key>(mKey = event->key.code)));
            mOutput.setPosition(mBackground.getPosition().x + mBackground.getSize().x / 2 - mOutput.getGlobalBounds().width / 2 - mOutput.getLocalBounds().left, mSize.y / 2 - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
            mReturn = false;
        }
    }
}

////////////////////////////////////////////////////////////
void KeyEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mTitle, states);
    target.draw(mOutput, states);
}

} // namespace CNGui
