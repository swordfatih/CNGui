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

#include "CNGui/Utilities/Text.hpp"

namespace CNGui
{
////////////////////////////////////////////////////////////
Text::Text() : sf::Text::Text()
{

}

////////////////////////////////////////////////////////////
Text::Text(const sf::String& string, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& size) : sf::Text::Text(string, font, characterSize), mString(string), mCharacterSize(characterSize), mSize(size)
{
    setString(string);
}

////////////////////////////////////////////////////////////
void Text::setString(const sf::String& string)
{
    mString = string;

    if(getCharacterSize() != mCharacterSize)
        setCharacterSize(mCharacterSize);

    //If limit size is defined
    if(mSize.x > 0)
    {
        do
        {
            std::string text;
            for(auto it: CNGui::Text::split(string))
            {
                sf::Text::setString(it);

                if(getGlobalBounds().width > mSize.x)
                {
                    for(auto token: fit(it))
                    {
                        if(!text.empty())
                            text += '\n';
                        text += token;
                    }

                    text += ' ';
                }
                else
                {
                    sf::Text::setString(text + it);

                    if(getGlobalBounds().width > mSize.x)
                    {
                        text += '\n' + it + ' ';
                    }
                    else
                    {
                        text += it + ' ';
                    }
                }
            }

            sf::Text::setString(text);
        }
        while([&]()
        {
            if(mSize.y > 0)
            {
                if(getGlobalBounds().height > mSize.y)
                {
                    setCharacterSize(getCharacterSize() - 2);
                }

                return getGlobalBounds().height > mSize.y;
            }

            return false;
        }());

        return;
    }

    sf::Text::setString(string);
}

////////////////////////////////////////////////////////////
sf::String Text::getString()
{
    return mString;
}

////////////////////////////////////////////////////////////
void Text::setSize(const sf::Vector2f& size)
{
    mSize = size;
    setString(getString());
}

////////////////////////////////////////////////////////////
sf::Vector2f Text::getSize()
{
    return mSize;
}

////////////////////////////////////////////////////////////
std::vector<std::string> Text::split(const sf::String& string)
{
    std::vector<std::string> tokens;
    std::istringstream stream(string);
    for(std::string token; std::getline(stream, token, ' ');)
    {
        tokens.push_back(token);
    }

   return tokens;
}

////////////////////////////////////////////////////////////
std::vector<std::string> Text::fit(const std::string& word)
{
    std::vector<std::string> tokens;

    for(sf::Uint16 pos = 0; pos < word.size(); ++pos)
    {
        sf::Text::setString(word.substr(0, word.size() - 1 - pos));

        if(getGlobalBounds().width < mSize.x)
        {
            tokens.push_back(word.substr(0, word.size() - 1 - pos));

            sf::Text::setString(word.substr(word.size() - 1 - pos));
            if(getGlobalBounds().width > mSize.x)
            {
                std::vector<std::string> deep = fit(word.substr(word.size() - 1 - pos));
                tokens.insert(tokens.end(), deep.begin(), deep.end());
            }
            else
            {
                tokens.push_back(word.substr(word.size() - 1 - pos));
            }

            break;
        }
    }

    return tokens;
}

} // namespace CNGui
