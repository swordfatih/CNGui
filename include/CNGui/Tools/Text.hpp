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

#ifndef TEXT_HPP
#define TEXT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <vector>
#include <sstream>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates a graphical text
///
////////////////////////////////////////////////////////////
class Text : public sf::Text
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty text.
    ///
    ////////////////////////////////////////////////////////////
    Text();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the text from a string, font and size
    ///
    /// Note that if the used font is a bitmap font, it is not
    /// scalable, thus not all requested sizes will be available
    /// to use. This needs to be taken into consideration when
    /// setting the character size. If you need to display text
    /// of a certain size, make sure the corresponding bitmap
    /// font that supports that size is used.
    ///
    /// \param string         Text assigned to the string
    /// \param font           Font used to draw the string
    /// \param characterSize  Base size of characters, in pixels
    /// \param size           Size limit of the text
    ///
    ////////////////////////////////////////////////////////////
    Text(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30, const sf::Vector2f& size = {0, 0});

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's string
    ///
    /// The \a string argument is a sf::String, which can
    /// automatically be constructed from standard string types.
    /// So, the following calls are all valid:
    /// \code
    /// text.setString("hello");
    /// text.setString(L"hello");
    /// text.setString(std::string("hello"));
    /// text.setString(std::wstring(L"hello"));
    /// \endcode
    /// A text's string is empty by default.
    ///
    /// \param string New string
    ///
    /// \see getString
    ///
    ////////////////////////////////////////////////////////////
    void setString(const sf::String& string);

    ////////////////////////////////////////////////////////////
    /// \brief Get the string
    ///
    /// \return The string of the text
    ///
    /// \see setString
    ///
    ////////////////////////////////////////////////////////////
    sf::String getString();

    ////////////////////////////////////////////////////////////
    /// \brief Set the string's limit size
    ///
    /// A text's size is unlimited by default.
    ///
    /// \param size New size
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void setSize(const sf::Vector2f& size);

    ////////////////////////////////////////////////////////////
    /// \brief Get the string's limit size
    ///
    /// \return Limit size of the string
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f getSize();

    ////////////////////////////////////////////////////////////
    /// \brief Set the text's character size
    ///
    /// \param characterSize New character size
    ///
    /// \see getCharacterSize
    ///
    ////////////////////////////////////////////////////////////
    void setCharacterSize(const sf::Uint16& characterSize);

    ////////////////////////////////////////////////////////////
    /// \brief Split a string in a vector
    ///
    /// \param string String to split
    ///
    /// \return Vector containing tokens
    ///
    ////////////////////////////////////////////////////////////
    static std::vector<std::string> split(const sf::String& string);

    ////////////////////////////////////////////////////////////
    /// \brief Split a word relative to a size in a vector
    ///
    /// \param string Word to split
    ///
    /// \return Vector containing tokens
    ///
    ////////////////////////////////////////////////////////////
    std::vector<std::string> fit(const std::string& word);

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::String      mString;        ///< String of the text
    sf::Uint16      mCharacterSize; ///< Text's character size
    sf::Vector2f    mSize;          ///< Size of the text box

};

} // namespace CNGui

#endif // TEXT_HPP
