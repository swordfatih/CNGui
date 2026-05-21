#pragma once

#include <functional>
#include <string>
#include <type_traits>
#include <utility>

namespace cngui
{
using callback = std::function<void()>;

struct computed_string
{
    std::string                  literal;
    std::function<std::string()> compute;
    bool                         dynamic = false;

    computed_string() = default;

    computed_string(std::string value)
        : literal(std::move(value))
    {
    }

    computed_string(char const* value)
        : literal(value)
    {
    }

    template<class function_type>
        requires(!std::is_same_v<std::remove_cvref_t<function_type>, computed_string> && std::is_invocable_r_v<std::string, function_type&>)
    computed_string(function_type function)
        : compute(std::move(function))
        , dynamic(true)
    {
    }

    [[nodiscard]] auto value() const -> std::string
    {
        if(dynamic)
        {
            return compute();
        }

        return literal;
    }
};
} // namespace cngui
