#pragma once

#include <cngui/core/children.hpp>
#include <cngui/core/color.hpp>
#include <cngui/core/computed.hpp>
#include <cngui/core/geometry.hpp>
#include <cngui/core/node.hpp>
#include <cngui/meta/reflected_style.hpp>
#include <cngui/meta/type_list.hpp>
#include <cngui/style/merge.hpp>
#include <cngui/widgets/context.hpp>

#include <algorithm>
#include <any>
#include <string_view>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace cngui
{
struct button_props
{
    computed_string text     = {};
    callback        on_click = {};
    bool            disabled = false;
};

struct button_style
{
    color       background = {};
    color       foreground = {};
    length_pair padding    = {};
    length      radius     = {};
};

template<class... style_classes>
struct button
{
    using props_type = button_props;
    using style_type = button_style;

    button_props    props    = {};
    cngui::children children = {};
};

inline void merge_style(button_style& target, button_style const& source)
{
    merge_if_specified(target.background, source.background);
    merge_if_specified(target.foreground, source.foreground);
    merge_if_specified(target.padding, source.padding);
    merge_if_specified(target.radius, source.radius);
}

template<class... style_classes>
[[nodiscard]] auto to_node(button<style_classes...> value) -> node
{
    return node{
        .widget_type   = std::type_index(typeid(button<>)),
        .style_classes = meta::type_list<style_classes...>(),
        .props         = std::move(value.props),
        .children      = std::move(value.children.nodes),
    };
}

namespace widgets::button_runtime
{
[[nodiscard]] inline auto type() -> std::type_index
{
    return std::type_index(typeid(button<>));
}

[[nodiscard]] inline auto matches(node const& value) -> bool
{
    return value.widget_type == type();
}

inline void resolve_style(node& value, style_registry const& styles)
{
    value.style.value = styles.resolve_dynamic<button>(value.style_classes);
}

[[nodiscard]] inline auto resolved_style(node const& value) -> button_style const&
{
    return std::any_cast<button_style const&>(value.style.value);
}

[[nodiscard]] inline auto resolved_props(node const& value) -> button_props const&
{
    return std::any_cast<button_props const&>(value.props);
}

[[nodiscard]] inline auto measure(node const& value, measure_context) -> cngui::size
{
    auto const& props      = resolved_props(value);
    auto const& style      = resolved_style(value);
    auto const  font_size  = 16.0f;
    auto const  padding    = style.padding.specified ? style.padding : length_pair{12_px, 8_px};
    auto const  text_width = static_cast<float>(props.text.value().size()) * font_size * 0.58f;

    return {
        .width  = std::max(80.0f, text_width + padding.x.value * 2.0f),
        .height = font_size + padding.y.value * 2.0f,
    };
}

inline void layout(node& value, layout_context context)
{
    value.bounds = context.bounds;
}

inline void render(node const& value, render_context context)
{
    auto const& props = resolved_props(value);
    auto const& style = resolved_style(value);

    auto const background = style.background.specified ? style.background : colors::dark_gray;
    auto const foreground = style.foreground.specified ? style.foreground : colors::white;
    auto const padding    = style.padding.specified ? style.padding : length_pair{12_px, 8_px};

    context.commands.push_back(render_command{
        .kind   = render_command_kind::rectangle,
        .bounds = value.bounds,
        .fill   = background,
        .radius = style.radius,
    });

    context.commands.push_back(render_command{
        .kind       = render_command_kind::text,
        .bounds     = {.left = value.bounds.left + padding.x.value, .top = value.bounds.top + padding.y.value, .width = std::max(0.0f, value.bounds.width - padding.x.value * 2.0f), .height = std::max(0.0f, value.bounds.height - padding.y.value * 2.0f)},
        .foreground = foreground,
        .font_size  = 16_px,
        .text       = props.text.value(),
    });
}

[[nodiscard]] inline auto dispatch(node& value, input_event const& event) -> bool
{
    if(event.button != pointer_button::left)
    {
        return false;
    }

    auto const& props = resolved_props(value);
    if(props.disabled)
    {
        return false;
    }

    if(event.kind == input_event_kind::pointer_down)
    {
        value.pointer_down = value.bounds.contains(event.point);
        return value.pointer_down;
    }

    if(event.kind == input_event_kind::pointer_up)
    {
        auto const should_click = value.pointer_down && value.bounds.contains(event.point) && static_cast<bool>(props.on_click);
        value.pointer_down      = false;

        if(should_click)
        {
            props.on_click();
            return true;
        }
    }

    return false;
}
} // namespace widgets::button_runtime
} // namespace cngui

namespace cngui::meta
{
template<>
struct reflected_style<button_style>
{
    static constexpr bool available = true;
    static constexpr auto fields    = std::array{std::string_view{"background"}, std::string_view{"foreground"}, std::string_view{"padding"}, std::string_view{"radius"}};
};
} // namespace cngui::meta
