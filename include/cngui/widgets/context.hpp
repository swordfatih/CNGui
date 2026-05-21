#pragma once

#include <cngui/core/input.hpp>
#include <cngui/core/math.hpp>
#include <cngui/core/node.hpp>
#include <cngui/core/render_command.hpp>
#include <cngui/style/style_registry.hpp>

#include <vector>

namespace cngui::widgets
{
struct measure_context
{
    cngui::size available = {};
};

struct layout_context
{
    rect bounds = {};
};

struct render_context
{
    std::vector<render_command>& commands;
};

[[nodiscard]] inline auto horizontal(edge_lengths value) -> float
{
    return value.left.value + value.right.value;
}

[[nodiscard]] inline auto vertical(edge_lengths value) -> float
{
    return value.top.value + value.bottom.value;
}
} // namespace cngui::widgets
