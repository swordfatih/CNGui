#pragma once

#include <cngui/core/math.hpp>

namespace cngui
{
enum class pointer_button
{
    left,
    right,
    middle
};

enum class input_event_kind
{
    pointer_move,
    pointer_down,
    pointer_up,
    window_closed
};

struct input_event
{
    input_event_kind kind   = input_event_kind::pointer_move;
    vec2             point  = {};
    pointer_button   button = pointer_button::left;
};
} // namespace cngui
