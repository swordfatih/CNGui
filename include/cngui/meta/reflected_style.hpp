#pragma once

#include <array>
#include <string_view>

namespace cngui::meta
{
template<class style_type>
struct reflected_style
{
    static constexpr bool available = false;
};
} // namespace cngui::meta
