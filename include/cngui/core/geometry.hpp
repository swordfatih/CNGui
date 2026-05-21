#pragma once

namespace cngui
{
struct length
{
    float value     = 0.0f;
    bool  specified = false;

    [[nodiscard]] constexpr explicit operator float() const
    {
        return value;
    }
};

[[nodiscard]] constexpr auto operator""_px(unsigned long long value) -> length
{
    return length{.value = static_cast<float>(value), .specified = true};
}

[[nodiscard]] constexpr auto operator""_px(long double value) -> length
{
    return length{.value = static_cast<float>(value), .specified = true};
}

struct length_pair
{
    length x;
    length y;
    bool   specified = false;

    constexpr length_pair() = default;

    constexpr length_pair(length horizontal, length vertical)
        : x(horizontal)
        , y(vertical)
        , specified(horizontal.specified || vertical.specified)
    {
    }
};

struct edge_lengths
{
    length left;
    length top;
    length right;
    length bottom;
    bool   specified = false;

    constexpr edge_lengths() = default;

    constexpr edge_lengths(length all)
        : left(all)
        , top(all)
        , right(all)
        , bottom(all)
        , specified(all.specified)
    {
    }

    constexpr edge_lengths(length horizontal, length vertical)
        : left(horizontal)
        , top(vertical)
        , right(horizontal)
        , bottom(vertical)
        , specified(horizontal.specified || vertical.specified)
    {
    }

    constexpr edge_lengths(length left_value, length top_value, length right_value, length bottom_value)
        : left(left_value)
        , top(top_value)
        , right(right_value)
        , bottom(bottom_value)
        , specified(left_value.specified || top_value.specified || right_value.specified || bottom_value.specified)
    {
    }
};
} // namespace cngui
