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
void LineEdit::update()
{
    //Updating the style of the button
    if(mUpdate)
    {
        //Background
        mBackground.setType(mStyle.shape);
        mBackground.setFillColor(mStyle.backgroundcolor);
        mBackground.setTexture(&mStyle.texturebackground);

        if(!mStyle.outline)
        {
            mBackground.setSize(mSize);
        }
        else
        {
            mBackground.setSize({mSize.x - mStyle.outlinethickness * 2, mSize.y - mStyle.outlinethickness * 2});
            mBackground.setPosition(mStyle.outlinethickness, mStyle.outlinethickness);
            mBackground.setOutlineColor(mStyle.outlinecolor);
            mBackground.setOutlineThickness(mStyle.outlinethickness);
        }

        //Shape
        mShape.setType(CNGui::Shape::Rectangle);
        mShape.setFillColor(mStyle.fillcolor);
        mShape.setSize(sf::Vector2f(mBackground.getSize().x, 2));

        if(!mStyle.outline)
        {
            mShape.setPosition(0, mBackground.getSize().y - mShape.getSize().y);
        }
        else
        {
            mShape.setPosition(mStyle.outlinethickness, mStyle.outlinethickness + mBackground.getSize().y - mShape.getSize().y);
        }

        //Texts
        mOutput.setFont(mStyle.outputfont);
        mOutput.setFillColor(mStyle.fillcolor);
        if(mFirst)
        {
            mOutput.setStyle(CNGui::Text::Italic);
        }
        else
        {
            mOutput.setStyle(CNGui::Text::Regular);
        }
        mOutput.setString("pb");
        mOutput.setCharacterSize(mStyle.outputcharactersize);
        mOutput.setPosition(-mOutput.getLocalBounds().left, mShape.getPosition().y - mShape.getGlobalBounds().height - mOutput.getGlobalBounds().height - mOutput.getLocalBounds().top);

        if(mStyle.label)
        {
            mLabel.setFont(mStyle.font);
            mLabel.setFillColor(mStyle.labelcolor);
            mLabel.setStyle(mStyle.labelstyle);
            mLabel.setCharacterSize(mStyle.charactersize);
            mLabel.setString(mName);
            mLabel.setSize(sf::Vector2f(mBackground.getSize().x, mStyle.charactersize * 1.25));

            if(!mStyle.outline)
            {
                mLabel.setPosition(-mLabel.getLocalBounds().left, -mLabel.getLocalBounds().top);
            }
            else
            {
                mLabel.setPosition(mStyle.outlinethickness - mLabel.getLocalBounds().left, mStyle.outlinethickness - mLabel.getLocalBounds().top);
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
            mStyle.outputhide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.outputhide));
        }

        mUpdate = false;
    }

    //If the line edit is hovered
    if(sf::FloatRect(getPosition().x, getPosition().y, mBackground.getGlobalBounds().width, mBackground.getGlobalBounds().height).contains(mMouse))
    {
        //Object is pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mShape.setFillColor(mStyle.clickedcolor);
            mBackground.setFillColor(mStyle.backgroundclickedcolor);
            mBackground.setOutlineColor(mStyle.outlineclickedcolor);
            mLabel.setFillColor(mStyle.labelclickedcolor);
            mOutput.setFillColor(mStyle.clickedcolor);
            mOutput.setStyle(mStyle.outputstyle);
            mCursor.setFillColor(sf::Color::White);
            mShape.setSize(sf::Vector2f(mBackground.getSize().x, 3));

            mStyle.outputhide == ' ' ? mOutput.setString(mString.substr(0, mString.size() - mPositionCursor)) : mOutput.setString(std::string(mString.size() - mPositionCursor, mStyle.outputhide));
            mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mCursor.getPosition().y);
            mStyle.outputhide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.outputhide));

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
            mShape.setFillColor(mStyle.fillcolor);
            mBackground.setFillColor(mStyle.backgroundcolor);
            mBackground.setOutlineColor(mStyle.outlinecolor);
            mLabel.setFillColor(mStyle.labelcolor);
            mOutput.setFillColor(mStyle.fillcolor);
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
                mStyle.outputhide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.outputhide));
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

            mStyle.outputhide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.outputhide));

            updatePosition = true;
        }
        else
        {
            //Animation
            if(mStyle.animated && mAnimation.getElapsedTime().asMilliseconds() > 500)
            {
                mCursor.getFillColor() == sf::Color::White ? mCursor.setFillColor(sf::Color::Transparent) : mCursor.setFillColor(sf::Color::White);
                mAnimation.restart();
            }
        }

        if(updatePosition)
        {
            mStyle.outputhide == ' ' ? mOutput.setString(mString.substr(0, mString.size() - mPositionCursor)) : mOutput.setString(std::string(mString.size() - mPositionCursor, mStyle.outputhide));

            sf::Vector2f position = {0, mOutput.getPosition().y};

            if(!mStyle.outline)
            {
                position.x = -mOutput.getLocalBounds().left;
            }
            else
            {
                position.x = -mOutput.getLocalBounds().left + mStyle.outlinethickness;
            }

            if(mOutput.getGlobalBounds().width > mSize.x)
            {
                position.x -= mOutput.getGlobalBounds().width - mSize.x + mSize.x * 0.02;
            }

            mCursor.setFillColor(sf::Color::White);
            mOutput.setPosition(position);
            mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mCursor.getPosition().y);

            mStyle.outputhide == ' ' ? mOutput.setString(mString) : mOutput.setString(std::string(mString.size(), mStyle.outputhide));
        }
    }
}

////////////////////////////////////////////////////////////
void LineEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(mBackground, states);
    target.draw(mLabel, states);

    glEnable(GL_SCISSOR_TEST);

    auto scissorStart = target.mapCoordsToPixel({getPosition().x, getPosition().y + mSize.y});
    auto scissorSize = target.mapCoordsToPixel({mSize.x, mSize.y});

    if(mContained)
    {
        glScissor(scissorStart.x + mInPosition.x, target.getSize().y - scissorStart.y - mInPosition.y, scissorSize.x, scissorSize.y);
    }
    else
    {
        glScissor(scissorStart.x, target.getSize().y - scissorStart.y, scissorSize.x, scissorSize.y);
    }

    target.draw(mOutput, states);

    glDisable(GL_SCISSOR_TEST);

    target.draw(mCursor, states);
    target.draw(mShape, states);
}

} // namespace CNGui
