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

#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
//SFML
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

//Standard
#include <cstdint>
#include <unordered_map>
#include <typeindex>
#include <vector>

namespace CNGui
{

namespace Core
{

////////////////////////////////////////////////////////////
/// \brief Base class for every class that need to be
/// matriculed
///
////////////////////////////////////////////////////////////
class Registrable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ////////////////////////////////////////////////////////////
    Registrable(std::type_index type);

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ////////////////////////////////////////////////////////////
    Registrable(const Registrable& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Overload of the assign operator
    ///
    ////////////////////////////////////////////////////////////
    Registrable& operator=(const Registrable& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Registrable();

    ////////////////////////////////////////////////////////////
    template <typename Type>
    static std::vector<Type*> getRegisteredInstances()
    {
        std::vector<Type*> vector;

        for(const auto& [identifier, instance] : Registrable::registereds[typeid(Type)])
        {
            vector.push_back(dynamic_cast<Type*>(instance));
        }

        return vector;
    }

    ////////////////////////////////////////////////////////////
    template <typename Type>
    static std::vector<Registrable*> getRegisteredPointers()
    {
        std::vector<Registrable*> vector;

        for(const auto& [identifier, instance] : Registrable::registereds[typeid(Type)])
        {
            vector.push_back(instance);
        }

        return vector;
    }

protected:

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    static uint64_t registered_count; ///< Count of registered instances
    static std::unordered_map<std::type_index, std::unordered_map<uint64_t, Registrable*>> registereds; ///< Registered instances
    uint64_t mIdentifier; ///< Identifier of the instance
    std::type_index mType = typeid(*this); ///< Type of the instance

};

} // namespace Core

///////////////////////////////////////////////////////////
template <typename Type>
class Draw : public Type, public Core::Registrable
{
public:
    Draw() : Registrable::Registrable(typeid(sf::Drawable))
    {
        static_assert(std::is_base_of<sf::Drawable, Type>::value, "Invalid type, must be drawable.");
    }
};

} // namespace CNGui

#endif // REGISTRATION_HPP
