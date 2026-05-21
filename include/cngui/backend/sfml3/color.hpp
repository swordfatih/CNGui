#pragma once

#include <cngui/core/color.hpp>

#include <SFML/Graphics/Color.hpp>

namespace cngui::sfml3
{
[[nodiscard]] inline auto to_sfml_color(color value) -> sf::Color
{
    return sf::Color{value.r, value.g, value.b, value.a};
}
} // namespace cngui::sfml3
