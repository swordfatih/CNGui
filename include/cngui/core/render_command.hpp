#pragma once

#include <cngui/core/color.hpp>
#include <cngui/core/geometry.hpp>
#include <cngui/core/math.hpp>

#include <string>

namespace cngui
{
enum class render_command_kind
{
    rectangle,
    text
};

struct render_command
{
    render_command_kind kind       = render_command_kind::rectangle;
    rect                bounds     = {};
    color               fill       = colors::transparent;
    color               foreground = colors::transparent;
    length              font_size  = {};
    length              radius     = {};
    std::string         text       = {};
};
} // namespace cngui
