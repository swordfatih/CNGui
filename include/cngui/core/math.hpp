#pragma once

namespace cngui
{
struct vec2
{
    float x = 0.0f;
    float y = 0.0f;

    [[nodiscard]] friend auto operator==(vec2 const&, vec2 const&) -> bool = default;
};

struct size
{
    float width  = 0.0f;
    float height = 0.0f;

    [[nodiscard]] friend auto operator==(size const&, size const&) -> bool = default;
};

struct rect
{
    float left   = 0.0f;
    float top    = 0.0f;
    float width  = 0.0f;
    float height = 0.0f;

    [[nodiscard]] auto right() const -> float
    {
        return left + width;
    }

    [[nodiscard]] auto bottom() const -> float
    {
        return top + height;
    }

    [[nodiscard]] auto contains(vec2 point) const -> bool
    {
        return point.x >= left && point.x <= right() && point.y >= top && point.y <= bottom();
    }
};
} // namespace cngui
