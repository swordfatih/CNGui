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

#include <CNGui/Objects/LineEdit.hpp>

namespace CNGui
{
////////////////////////////////////////////////////////////
bool LineEdit::onReturn()
{
    return mOnReturn;
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
        mShape.setSize(sf::Vector2f(mBackground.getSize().x, mBackground.getSize().y * 0.02));

        if(!mStyle.outline)
        {
            mShape.setPosition(0, mBackground.getSize().y - mShape.getSize().y);
        }
        else
        {
            mShape.setPosition(mStyle.outlinethickness, mStyle.outlinethickness + mBackground.getSize().y - mShape.getSize().y);
        }

        //Texts
        mOutput.setFont(mStyle.font);
        mOutput.setFillColor(mStyle.fillcolor);
        mOutput.setStyle(CNGui::Text::Italic);
        mOutput.setString("pb");

        if(mStyle.label)
        {
            mLabel.setFont(mStyle.font);
            mLabel.setFillColor(mStyle.labelcolor);
            mLabel.setCharacterSize(mStyle.charactersize);
            mLabel.setString(mName);
            mLabel.setSize(sf::Vector2f(mBackground.getSize().x, mStyle.charactersize * 1.25));
            mOutput.setCharacterSize(mSize.y - mStyle.charactersize - 3);

            if(!mStyle.outline)
            {
                mLabel.setPosition(-mLabel.getLocalBounds().left, -mLabel.getLocalBounds().top);
                mOutput.setPosition(-mOutput.getLocalBounds().left, mSize.y / 2 + mLabel.getGlobalBounds().height / 2 - mShape.getSize().y - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
            }
            else
            {
                mLabel.setPosition(mStyle.outlinethickness - mLabel.getLocalBounds().left, mStyle.outlinethickness - mLabel.getLocalBounds().top);
                mOutput.setPosition(-mOutput.getLocalBounds().left + mStyle.outlinethickness, mSize.y / 2 + mLabel.getGlobalBounds().height / 2 - mShape.getSize().y - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
            }
        }
        else
        {
            mOutput.setCharacterSize(mSize.y - 3);
            if(!mStyle.outline)
            {
                mOutput.setPosition(-mOutput.getLocalBounds().left, mSize.y / 2 - mShape.getSize().y - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
            }
            else
            {
                mOutput.setPosition(-mOutput.getLocalBounds().left + mStyle.outlinethickness, mSize.y / 2 - mShape.getSize().y - mOutput.getGlobalBounds().height / 2 - mOutput.getLocalBounds().top);
            }
        }

        mOutput.setString(mDefault);

        //Cursor
        mCursor.setType(CNGui::Shape::Rectangle);
        mCursor.setFillColor(sf::Color::Transparent);
        mCursor.setSize(sf::Vector2f(2, mOutput.getGlobalBounds().height));
        mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x * 2, mOutput.getPosition().y + mOutput.getLocalBounds().top);

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
            mCursor.setFillColor(sf::Color::White);
            mShape.setSize(sf::Vector2f(mBackground.getSize().x, mBackground.getSize().y * 0.05));

            if(mOutput.getString() == mDefault)
            {
                mOutput.setString(mString);
                mOutput.setStyle(CNGui::Text::Regular);
                mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mCursor.getPosition().y);
            }
            else
            {
                mOutput.setString(mString.substr(0, mString.size() - mPositionCursor));
                mCursor.setPosition(mOutput.getPosition().x + mOutput.getGlobalBounds().width + mCursor.getSize().x, mCursor.getPosition().y);
                mOutput.setString(mString);
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
            mShape.setSize(sf::Vector2f(mBackground.getSize().x, mBackground.getSize().y * 0.02));

            mReturn = false;
        }
    }

    //If object is selected
    if(mReturn)
    {
        mOnReturn = false;
        bool updatePosition = false;

        if(mHandleEvent.isActive(sf::Event::KeyPressed))
        {

            if(mHandleEvent[sf::Event::KeyPressed].key.code == sf::Keyboard::Left && mPositionCursor < mString.size())
            {
                mPositionCursor += 1;
                updatePosition = true;
            }
            else if(mHandleEvent[sf::Event::KeyPressed].key.code == sf::Keyboard::Right && mPositionCursor > 0)
            {
                mPositionCursor -= 1;
                updatePosition = true;
            }
            else if(mHandleEvent[sf::Event::KeyPressed].key.code == sf::Keyboard::Delete && mPositionCursor > 0)
            {
                mString.erase(mString.end() - mPositionCursor);
                mPositionCursor -= 1;
                updatePosition = true;
            }
            else if(mHandleEvent[sf::Event::KeyPressed].key.control && mHandleEvent[sf::Event::KeyPressed].key.code == sf::Keyboard::C)
            {
                sf::Clipboard::setString(mString);
            }
            else if(mHandleEvent[sf::Event::KeyPressed].key.control && mHandleEvent[sf::Event::KeyPressed].key.code == sf::Keyboard::V)
            {
                mString.insert(mString.size() - mPositionCursor, sf::Clipboard::getString());
                mOutput.setString(mString);
            }
        }

        if(mHandleEvent.isActive(sf::Event::TextEntered))
        {
            //Handle input
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {
                if(mPositionCursor < mString.size())
                {
                    mString.pop_back();
                }
            }
            else
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    mOnReturn = true;
                }
                else if(!mHandleEvent[sf::Event::KeyPressed].key.control)
                {
                    mString.insert(mString.size() - mPositionCursor, 1, static_cast<char>(mHandleEvent[sf::Event::TextEntered].text.unicode));
                }
            }

            mOutput.setString(mString);

            updatePosition = true;
        }
        else
        {
            //Animation
            if(mStyle.animated)
            {
                if(mAnimation.getElapsedTime().asMilliseconds() > 500)
                {
                    if(mCursor.getFillColor() == sf::Color::White)
                    {
                        mCursor.setFillColor(sf::Color::Transparent);
                    }
                    else
                    {
                        mCursor.setFillColor(sf::Color::White);
                    }

                    mAnimation.restart();
                }
            }
        }

        if(updatePosition)
        {
            //Update position
            mOutput.setString(mString.substr(0, mString.size() - mPositionCursor));

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
            mOutput.setString(mString);
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

    glScissor(scissorStart.x + mContainer->x, target.getSize().y - scissorStart.y - mContainer->y, scissorSize.x, scissorSize.y);
    target.draw(mOutput, states);

    glDisable(GL_SCISSOR_TEST);

    target.draw(mCursor, states);
    target.draw(mShape, states);
}

} // namespace CNGui
