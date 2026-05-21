#pragma once

#include <algorithm>
#include <cstdint>

namespace cngui
{
struct color
{
    std::uint8_t r         = 0;
    std::uint8_t g         = 0;
    std::uint8_t b         = 0;
    std::uint8_t a         = 0;
    bool         specified = false;

    [[nodiscard]] static constexpr auto rgba(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255) -> color
    {
        return color{.r = red, .g = green, .b = blue, .a = alpha, .specified = true};
    }
};

namespace colors
{
inline constexpr color transparent = color{};
inline constexpr color white       = color::rgba(255, 255, 255);
inline constexpr color black       = color::rgba(0, 0, 0);
inline constexpr color dark_gray   = color::rgba(38, 38, 42);
inline constexpr color blue        = color::rgba(56, 116, 255);
inline constexpr color red         = color::rgba(220, 54, 70);

[[nodiscard]] constexpr auto black_alpha(float alpha) -> color
{
    auto const clamped = std::clamp(alpha, 0.0f, 1.0f);
    return color::rgba(0, 0, 0, static_cast<std::uint8_t>(clamped * 255.0f));
}
} // namespace colors
} // namespace cngui
