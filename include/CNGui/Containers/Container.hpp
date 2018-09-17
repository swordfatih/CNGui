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

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "CNGui/Objects/Object.hpp"
#include <vector>
#include <memory>

namespace CNGui
{
////////////////////////////////////////////////////////////
/// \brief Enumeration of the different container types
///
////////////////////////////////////////////////////////////
enum ContainerType
{
    Free,
    Vertical,
    Horizontal
};

////////////////////////////////////////////////////////////
/// \brief Container class
///
////////////////////////////////////////////////////////////
template <class Content>
class Container : public sf::Drawable, public sf::Transformable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
                    Container(const sf::Vector2f& size = sf::Vector2f(400, 400), ContainerType type = ContainerType::Free) : mSize(size), mType(type), mSpacing(10), mContainer(new sf::Vector2f(0, 0)), mDeep(0, 0)
    {
        static_assert(std::is_base_of<sf::Drawable, Content>::value && std::is_base_of<sf::Transformable, Content>::value, "Invalid type, must be Drawable and Transformable");
    }

    ////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual         ~Container()
    {
        //dtor
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the position of the container
    ///
    /// \param position New position
    ///
    /// \see getPosition
    ///
    ////////////////////////////////////////////////////////////
    void            setPosition(const sf::Vector2f& position)
    {
        mPosition = position;
        Transformable::setPosition(position);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the position of the container
    ///
    /// \param x X coordinate of the new position
    /// \param y Y coordinate of the new position
    ///
    /// \see getPosition
    ///
    ////////////////////////////////////////////////////////////
    void            setPosition(float x, float y)
    {
        mPosition = sf::Vector2f{x, y};
        Transformable::setPosition(x, y);
        update();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the container
    ///
    /// \param size New size
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void            setSize(const sf::Vector2f& size)
    {
        mSize = size;
        update();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the container
    ///
    /// \return Size of the new size
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f    getSize()
    {
        return mSize;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the main container of the container
    ///
    /// \param position Position of the container
    ///
    ////////////////////////////////////////////////////////////
    void            setContainer(sf::Vector2f& position)
    {
        mContainer = &position;
        update();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the space between the contents
    ///
    /// \param spacing Space between the contents
    ///
    /// \see getSpacing
    ///
    ////////////////////////////////////////////////////////////
    void            setSpacing(const sf::Uint16& spacing)
    {
        mSpacing = spacing;
        update();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the space between the contents
    ///
    /// \return The space between the contents
    ///
    /// \see setSpacing
    ///
    ////////////////////////////////////////////////////////////
    sf::Uint16      getSpacing()
    {
        return mSpacing;
    }

    ///////////////////////////////////////////////////////////
    /// Overload of operator << to add a content to the container
    ///
    ////////////////////////////////////////////////////////////
    Container&      operator <<(Content& content)
    {
        content.setContainer(mPosition);
        mContents.push_back(content);
        update();
        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Clear contents
    ///
    ////////////////////////////////////////////////////////////
    void            clear()
    {
        mContents.clear();
    }

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Draw the contents to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    void            draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for(auto&& it: mContents)
            target.draw(it, states);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Update the contents
    ///
    ////////////////////////////////////////////////////////////
    virtual void    update()
    {
        mDeep = *mContainer + mPosition;

        for(auto&& it: mContents)
        {
            int i = &it - &mContents[0];

            mContents[i].get().setContainer(mDeep);

            if(mType == ContainerType::Horizontal)
            {
                if(std::is_base_of<CNGui::Object, Content>::value)
                {
                    mContents[i].get().setSize(sf::Vector3f(mSize.x / mContents.size(), mSize.y, mContents[i].get().getSize().z));
                }
                else
                {
                    mContents[i].get().setSize(sf::Vector2f(mSize.x / mContents.size(), mSize.y));
                }

                mContents[i].get().setPosition(i * (mContents[i].get().getSize().x + mSpacing), 0);
            }
            else if(mType == ContainerType::Vertical)
            {
                if(std::is_base_of<CNGui::Object, Content>::value)
                {
                    mContents[i].get().setSize(sf::Vector3f(mSize.x, mSize.y / mContents.size(), mContents[i].get().getSize().z));
                }
                else
                {
                    mContents[i].get().setSize(sf::Vector2f(mSize.x, mSize.y / mContents.size()));
                }
                mContents[i].get().setPosition(0, i * (mContents[i].get().getSize().y + mSpacing));
            }
        }
    }

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<std::reference_wrapper<Content>>    mContents;  ///< All the contents
    sf::Vector2f                                    mSize;      ///< Size of the container
    sf::Vector2f                                    mPosition;  ///< Position of the container
    ContainerType                                   mType;      ///< Type of the container
    sf::Uint16                                      mSpacing;   ///< Space between the contents
    sf::Vector2f*                                   mContainer; ///< Position of the container that contains it
    sf::Vector2f                                    mDeep;      ///< Position after containers stacking
};

} // namespace CNGui

#endif // CONTAINER_HPP
