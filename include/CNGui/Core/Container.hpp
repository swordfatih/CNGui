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
/// \brief Enumeration for the different alignments
///
////////////////////////////////////////////////////////////
enum Alignment
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
    /// \brief Enumeration for the different modes
    ///
    ////////////////////////////////////////////////////////////
    enum Mode
    {
        Stacked,
        Static,
        Dynamic
    };

    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ////////////////////////////////////////////////////////////
                    Container(Alignment align = Alignment::Free, const sf::Vector2f& size = sf::Vector2f(400, 400), Mode mode = Mode::Static) : Updatable(), Registrable::Registrable(typeid(Container)), mSize(size), mAlign(std::move(align)), mMode(std::move(mode)), mSpacing(5)
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
    void      setSize(const sf::Vector2f& size)
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
    sf::Vector2f    getSize() const
    {
        return mSize;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the align of the container
    ///
    /// \param align Align of the container
    ///
    /// \return Returns a reference to *this, so that calls can be chained
    ///
    /// \see getAlign
    ///
    ////////////////////////////////////////////////////////////
    Container&      setAlign(Alignment align)
    {
        mAlign = std::move(align);
        update();

        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the align of the container
    ///
    /// \return The align of the container
    ///
    /// \see setAlign
    ///
    ////////////////////////////////////////////////////////////
    Alignment       getAlign() const
    {
        return mAlign;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the mode of the container
    ///
    /// \param mode Mode of the container
    ///
    /// \return Returns a reference to *this, so that calls can be chained
    ///
    /// \see getMode
    ///
    ////////////////////////////////////////////////////////////
    Container&      setMode(Mode mode)
    {
        mMode = std::move(mode);
        update();

        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the mode of the container
    ///
    /// \return The mode of the container
    ///
    /// \see setMode
    ///
    ////////////////////////////////////////////////////////////
    Mode            getMode() const
    {
        return mMode;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the space between the contents
    ///
    /// \param spacing Space between the contents
    ///
    /// \return Returns a reference to *this, so that calls can be chained
    ///
    /// \see getSpacing
    ///
    ////////////////////////////////////////////////////////////
    Container&      setSpacing(const uint32_t& spacing)
    {
        mSpacing = spacing;
        update();

        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the space between the contents
    ///
    /// \return The space between the contents
    ///
    /// \see setSpacing
    ///
    ////////////////////////////////////////////////////////////
    uint32_t        getSpacing() const
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
            if(size.x != 0 && size.y != 0)
            {
                content.setSize(std::move(size));
            }

            return content.getSize();
        });

        return *this;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Add to the container
    ///
    /// \param content Pointer to the content to add
    /// \param function_size Size setter of the content
    ///
    /// \return Returns a reference to *this, so that calls can be chained
    ///
    ////////////////////////////////////////////////////////////
    Container&      add(sf::Transformable* content, std::function<sf::Vector2f(sf::Vector2f)> function_size)
    {
        mContents.push_back(std::make_pair(content, function_size));
        update();

        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Clear contents
    ///
    ////////////////////////////////////////////////////////////
    void            clear()
    {
        for(auto& content: mContents)
        {
            if(auto updatable = dynamic_cast<Updatable*>(content.first))
            {
                updatable->setInheritance(false);
            }
        }

        mContents.clear();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Update the contents
    ///
    ////////////////////////////////////////////////////////////
    virtual void    update()
    {
        size_t size_accumulated = 0;
        size_t biggest_content = 0;

        for(auto& content: mContents)
        {
            size_t index = &content - &mContents[0];

            if(auto updatable = dynamic_cast<Updatable*>(content.first))
            {
                updatable->setInheritance(true, this, mPosition + mInPosition);

                if(auto container = dynamic_cast<Container*>(updatable))
                {
                    container->update();
                }
            }

            auto size_object = content.second({0, 0});
            sf::Vector2f position_object = {0, 0};

            if(mAlign == Alignment::Horizontal)
            {
                if(mMode != Mode::Stacked)
                {
                    size_object.y = mSize.y;
                }

                if(mMode == Mode::Static)
                {
                    size_object.x = (mSize.x - mSpacing * (mContents.size() - 1)) / mContents.size();
                    position_object.x = index * (size_object.x + mSpacing);
                }
                else
                {
                    position_object.x = size_accumulated + index * mSpacing;
                    size_accumulated += size_object.x;
                }

                if(size_object.y > biggest_content)
                {
                    biggest_content = size_object.y;
                }
            }
            else if(mAlign == Alignment::Vertical)
            {
                if(mMode != Mode::Stacked)
                {
                    size_object.x = mSize.x;
                }

                if(mMode == Mode::Static)
                {
                    size_object.y = (mSize.y - mSpacing * (mContents.size() - 1)) / mContents.size();
                    position_object.y = index * (size_object.y + mSpacing);
                }
                else
                {
                    position_object.y = size_accumulated + index * mSpacing;
                    size_accumulated += size_object.y;
                }

                if(size_object.x > biggest_content)
                {
                    biggest_content = size_object.x;
                }
            }

            if(auto container = dynamic_cast<Container*>(content.first))
            {
                container->setPosition(position_object);
            }
            else
            {
                content.first->setPosition(position_object);
            }

            if(mMode != Mode::Stacked)
            {
                content.second(size_object);
            }
        }

        if(mMode != Mode::Static)
        {
            if(mAlign == Alignment::Horizontal)
            {
                mSize.x = size_accumulated + (mContents.size() - 1) * mSpacing;

                if(mMode == Mode::Stacked)
                {
                    mSize.y = biggest_content;
                }
            }
            else if(mAlign == Alignment::Vertical)
            {
                mSize.y = size_accumulated + (mContents.size() - 1) * mSpacing;

                if(mMode == Mode::Stacked)
                {
                    mSize.x = biggest_content;
                }
            }
        }

        if(mParent && mHandleEvent.active(this, "update_parent"))
        {
            mHandleEvent.clear(this, "update_parent");
            mHandleEvent.push(mParent, "update_parent");
            mParent->update();
        }
    }

    /////////////////////////////////////////////////
    /// \brief Retrieve all the contents
    ///
    /// \return A table of pointers to the contents
    ///
    /////////////////////////////////////////////////
    template <typename Type>
    std::vector<Type*> retrieve() const
    {
        std::vector<Type*> pointers;
        pointers.reserve(mContents.size());

        for(auto content: mContents)
        {
            if(auto same_type = dynamic_cast<Type*>(content.first))
            {
                pointers.push_back(same_type);
            }
        }

        return pointers;
    }

protected:
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
    std::vector<std::pair<sf::Transformable*, std::function<sf::Vector2f(sf::Vector2f)>>>   mContents;  ///< All the contents
    sf::Vector2f                                                                            mSize;      ///< Size of the container
    sf::Vector2f                                                                            mPosition;  ///< Position of the container
    Alignment                                                                               mAlign;     ///< Alignment of the container
    Mode                                                                                    mMode;      ///< Mode of the container
    uint32_t                                                                                mSpacing;   ///< Space between the contents

};

} // namespace CNGui

#endif // CONTAINER_HPP
