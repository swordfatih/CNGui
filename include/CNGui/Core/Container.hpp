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

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//CNGui
#include <CNGui/Core/Updatable.hpp>
#include <CNGui/Core/Registration.hpp>

//SFML
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//Standard
#include <vector>
#include <functional>

namespace CNGui
{

namespace Core
{

////////////////////////////////////////////////////////////
/// \brief Class to check if a given class has a member
/// function signed setSize()
///
////////////////////////////////////////////////////////////
template<typename, typename T>
class has_size_setter;

////////////////////////////////////////////////////////////
/// \brief Specialization of has_size_setter
///
////////////////////////////////////////////////////////////
template<typename C, typename Ret, typename... Args>
class has_size_setter<C, Ret(Args...)>
{
    template<typename T>
    static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().setSize(std::declval<Args>()...)), Ret>::type;

    template<typename>
    static constexpr std::false_type check(...);

    typedef decltype(check<C>(0)) type;

public:
    static constexpr bool value = type::value;
};

} // namespace Core

////////////////////////////////////////////////////////////
/// \brief Enumeration of the different container types
///
////////////////////////////////////////////////////////////
enum Align
{
    Free,
    Vertical,
    Horizontal
};

////////////////////////////////////////////////////////////
/// \brief Container class
///
////////////////////////////////////////////////////////////
class Container : public Updatable, public sf::Drawable, public Core::Registrable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ////////////////////////////////////////////////////////////
                    Container(Align align = Align::Free, const sf::Vector2f& size = sf::Vector2f(400, 400)) : Registrable::Registrable(typeid(Container)), mSize(size), mAlign(align), mSpacing(5)
    {
        //ctor
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
        update();
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
        mPosition = {x, y};
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
    /// \brief Set the align of the container
    ///
    /// \param align Align of the container
    ///
    /// \see getAlign
    ///
    ////////////////////////////////////////////////////////////
    void            setAlign(const Align& align)
    {
        mAlign = align;
        update();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the align of the container
    ///
    /// \return The align of the container
    ///
    /// \see setAlign
    ///
    ////////////////////////////////////////////////////////////
    Align           getAlign() const
    {
        return mAlign;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the space between the contents
    ///
    /// \param spacing Space between the contents
    ///
    /// \see getSpacing
    ///
    ////////////////////////////////////////////////////////////
    void            setSpacing(const uint32_t& spacing)
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
    uint32_t        getSpacing()
    {
        return mSpacing;
    }

    ///////////////////////////////////////////////////////////
    /// Overload of operator << to add to the container
    ///
    ////////////////////////////////////////////////////////////
    template <typename Content>
    Container&      operator <<(Content& content)
    {
        static_assert(Core::has_size_setter<Content, void(sf::Vector2f)>::value, "Invalid type, must have a size setter.");

        add(&content, [&content](sf::Vector2f size)
        {
            content.setSize(std::move(size));
        });

        return *this;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Add to the container
    ///
    /// \param content Pointer to the content to add
    /// \param function_size Size setter of the content
    ///
    ////////////////////////////////////////////////////////////
    void            add(sf::Transformable* content, std::function<void(const sf::Vector2f&)> function_size)
    {
        mContents.push_back(std::make_pair(content, function_size));
        update();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Clear contents
    ///
    ////////////////////////////////////////////////////////////
    void            clear()
    {
        mContents.clear();
        update();
    }

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Update the contents
    ///
    ////////////////////////////////////////////////////////////
    virtual void    update()
    {
        for(auto& content: mContents)
        {
            int i = &content - &mContents[0];

            if(auto updatable = dynamic_cast<Updatable*>(content.first))
            {
                updatable->setInheritance(mPosition + mInPosition);
            }

            auto size = mSize;

            if(mAlign == Align::Horizontal)
            {
                size.x = (mSize.x - mSpacing * (mContents.size() - 1)) / mContents.size();

                if(auto container = dynamic_cast<Container*>(content.first))
                {
                    container->setPosition(i * (size.x + mSpacing), 0);
                }
                else
                {
                    content.first->setPosition(i * (size.x + mSpacing), 0);
                }
            }
            else if(mAlign == Align::Vertical)
            {
                size.y = (mSize.y - mSpacing * (mContents.size() - 1)) / mContents.size();

                if(auto container = dynamic_cast<Container*>(content.first))
                {
                    container->setPosition(0, i * (size.y + mSpacing));
                }
                else
                {
                    content.first->setPosition(0, i * (size.y + mSpacing));
                }
            }

            content.second(size);
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief Draw the container to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for(const auto& [content, setter] : mContents)
        {
            target.draw(*dynamic_cast<sf::Drawable*>(content), states);
        }
    }

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<std::pair<sf::Transformable*, std::function<void(sf::Vector2f)>>>   mContents;  ///< All the contents
    sf::Vector2f                                                                    mSize;      ///< Size of the container
    sf::Vector2f                                                                    mPosition;  ///< Position of the container
    Align                                                                           mAlign;     ///< Align of the container
    uint32_t                                                                        mSpacing;   ///< Space between the contents

};

} // namespace CNGui

#endif // CONTAINER_HPP
