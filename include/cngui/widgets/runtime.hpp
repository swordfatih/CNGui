#pragma once

#include <cngui/widgets/anchor.hpp>
#include <cngui/widgets/button.hpp>
#include <cngui/widgets/context.hpp>
#include <cngui/widgets/panel.hpp>
#include <cngui/widgets/text.hpp>

#include <algorithm>
#include <typeindex>
#include <typeinfo>
#include <vector>

namespace cngui::widgets
{
inline void resolve_styles(node& value, style_registry const& styles)
{
    if(anchor_runtime::matches(value))
    {
        anchor_runtime::resolve_style(value, styles);
    }
    else if(panel_runtime::matches(value))
    {
        panel_runtime::resolve_style(value, styles);
    }
    else if(text_runtime::matches(value))
    {
        text_runtime::resolve_style(value, styles);
    }
    else if(button_runtime::matches(value))
    {
        button_runtime::resolve_style(value, styles);
    }

    for(auto& child : value.children)
    {
        resolve_styles(child, styles);
    }
}

[[nodiscard]] inline auto measure(node& value, measure_context context) -> cngui::size
{
    if(text_runtime::matches(value))
    {
        value.measured_size = text_runtime::measure(value, context);
        return value.measured_size;
    }

    if(button_runtime::matches(value))
    {
        value.measured_size = button_runtime::measure(value, context);
        return value.measured_size;
    }

    if(panel_runtime::matches(value))
    {
        auto const padding = panel_runtime::padding(value);
        auto const gap     = panel_runtime::gap(value);

        auto children_width  = 0.0f;
        auto children_height = 0.0f;
        auto first_child     = true;

        auto const child_available = cngui::size{
            .width  = std::max(0.0f, context.available.width - horizontal(padding)),
            .height = std::max(0.0f, context.available.height - vertical(padding)),
        };

        for(auto& child : value.children)
        {
            auto const child_size = measure(child, {.available = child_available});
            children_width        = std::max(children_width, child_size.width);
            children_height += child_size.height;
            if(!first_child)
            {
                children_height += gap;
            }
            first_child = false;
        }

        value.measured_size = {
            .width  = children_width + horizontal(padding),
            .height = children_height + vertical(padding),
        };
        return value.measured_size;
    }

    if(anchor_runtime::matches(value))
    {
        auto children_width  = 0.0f;
        auto children_height = 0.0f;

        for(auto& child : value.children)
        {
            auto const child_size = measure(child, context);
            children_width        = std::max(children_width, child_size.width);
            children_height       = std::max(children_height, child_size.height);
        }

        value.measured_size = {.width = children_width, .height = children_height};
        return value.measured_size;
    }

    value.measured_size = {};
    return value.measured_size;
}

inline void layout(node& value, layout_context context)
{
    if(text_runtime::matches(value))
    {
        text_runtime::layout(value, context);
        return;
    }

    if(button_runtime::matches(value))
    {
        button_runtime::layout(value, context);
        return;
    }

    if(panel_runtime::matches(value))
    {
        panel_runtime::layout(value, context);

        auto const padding = panel_runtime::padding(value);
        auto const gap     = panel_runtime::gap(value);
        auto       y       = context.bounds.top + padding.top.value;

        for(auto& child : value.children)
        {
            auto const child_bounds = rect{
                .left   = context.bounds.left + padding.left.value,
                .top    = y,
                .width  = child.measured_size.width,
                .height = child.measured_size.height,
            };

            layout(child, {.bounds = child_bounds});
            y += child.measured_size.height + gap;
        }
        return;
    }

    if(anchor_runtime::matches(value))
    {
        anchor_runtime::layout(value, context);
        auto const& props = anchor_runtime::resolved_props(value);
        auto const  margin = props.margin;

        for(auto& child : value.children)
        {
            auto x = context.bounds.left + margin.left.value;
            auto y = context.bounds.top + margin.top.value;

            switch(props.position)
            {
            case anchor_position::top_left:
                break;
            case anchor_position::top_right:
                x = context.bounds.right() - margin.right.value - child.measured_size.width;
                break;
            case anchor_position::bottom_left:
                y = context.bounds.bottom() - margin.bottom.value - child.measured_size.height;
                break;
            case anchor_position::bottom_right:
                x = context.bounds.right() - margin.right.value - child.measured_size.width;
                y = context.bounds.bottom() - margin.bottom.value - child.measured_size.height;
                break;
            case anchor_position::center:
                x = context.bounds.left + (context.bounds.width - child.measured_size.width) * 0.5f;
                y = context.bounds.top + (context.bounds.height - child.measured_size.height) * 0.5f;
                break;
            }

            layout(child, {.bounds = {.left = x, .top = y, .width = child.measured_size.width, .height = child.measured_size.height}});
        }
    }
}

inline void render(node const& value, render_context context)
{
    if(panel_runtime::matches(value))
    {
        panel_runtime::render(value, context);
    }
    else if(text_runtime::matches(value))
    {
        text_runtime::render(value, context);
    }
    else if(button_runtime::matches(value))
    {
        button_runtime::render(value, context);
    }

    for(auto const& child : value.children)
    {
        render(child, context);
    }
}

[[nodiscard]] inline auto dispatch(node& value, input_event const& event) -> bool
{
    for(auto child = value.children.rbegin(); child != value.children.rend(); ++child)
    {
        if(dispatch(*child, event))
        {
            return true;
        }
    }

    if(button_runtime::matches(value))
    {
        return button_runtime::dispatch(value, event);
    }

    return false;
}

inline void process(node& root, style_registry const& styles, cngui::size viewport, std::vector<render_command>& commands)
{
    resolve_styles(root, styles);
    measure(root, {.available = viewport});

    auto const root_bounds = anchor_runtime::matches(root)
                               ? rect{.left = 0.0f, .top = 0.0f, .width = viewport.width, .height = viewport.height}
                               : rect{.left = 0.0f, .top = 0.0f, .width = root.measured_size.width, .height = root.measured_size.height};

    layout(root, {.bounds = root_bounds});
    render(root, {.commands = commands});
}
} // namespace cngui::widgets
