#pragma once

#include <cngui/core/color.hpp>
#include <cngui/core/geometry.hpp>

namespace cngui
{
inline void merge_if_specified(color& target, color const& source)
{
    if(source.specified)
    {
        target = source;
    }
}

inline void merge_if_specified(length& target, length const& source)
{
    if(source.specified)
    {
        target = source;
    }
}

inline void merge_if_specified(length_pair& target, length_pair const& source)
{
    if(source.specified)
    {
        target = source;
    }
}

inline void merge_if_specified(edge_lengths& target, edge_lengths const& source)
{
    if(source.specified)
    {
        target = source;
    }
}
} // namespace cngui
