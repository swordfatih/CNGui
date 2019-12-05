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

#ifndef SHAPE_HPP
#define SHAPE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Shape.hpp>
#include <cmath>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Class that creates a custom shape
///
////////////////////////////////////////////////////////////
class Shape : public sf::Shape
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the different shape types
    ///
    ////////////////////////////////////////////////////////////
    enum                    Type
    {
        Triangle,
        Rectangle,
        RoundedRectangle,
        Circle
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
                            Shape(Type type = Type::Rectangle, sf::Vector2f size = sf::Vector2f(100, 50));

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual                 ~Shape();

    ////////////////////////////////////////////////////////////
    /// \brief Set the type of the shape
    ///
    /// \param type Type of the shape
    ///
    /// \see getType
    ///
    ////////////////////////////////////////////////////////////
    void                    setType(Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Get the type of the shape
    ///
    /// \return The type of the shape
    ///
    /// \see setType
    ///
    ////////////////////////////////////////////////////////////
    Type                    getType();

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the shape
    ///
    /// \param size Size of the shape
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void                    setSize(sf::Vector2f size);

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the shape
    ///
    /// \return The size of the shape
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f            getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the number of points defining the shape
    ///
    /// \return Number of points of the shape
    ///
    ////////////////////////////////////////////////////////////
    virtual std::size_t     getPointCount() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get a point of the rectangle
    ///
    /// The returned point is in local coordinates, that is,
    /// the shape's transforms (position, rotation, scale) are
    /// not taken into account.
    /// The result is undefined if \a index is out of the valid range.
    ///
    /// \param index Index of the point to get
    ///
    /// \return index-th point of the shape
    ///
    ////////////////////////////////////////////////////////////
    virtual sf::Vector2f    getPoint(std::size_t index) const;

protected:

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Type            mType;  ///< Type of the shape
    sf::Vector2f    mSize;  ///< Size of the shape
};

} // namespace CNGui

#endif // SHAPE_HPP
