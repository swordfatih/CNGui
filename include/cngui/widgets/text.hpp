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
struct text_props
{
    computed_string value = {};
};

struct text_style
{
    color  foreground = {};
    length font_size  = {};
};

template<class... style_classes>
struct text
{
    using props_type = text_props;
    using style_type = text_style;

    text_props      props    = {};
    cngui::children children = {};
};

inline void merge_style(text_style& target, text_style const& source)
{
    merge_if_specified(target.foreground, source.foreground);
    merge_if_specified(target.font_size, source.font_size);
}

template<class... style_classes>
[[nodiscard]] auto to_node(text<style_classes...> value) -> node
{
    return node{
        .widget_type   = std::type_index(typeid(text<>)),
        .style_classes = meta::type_list<style_classes...>(),
        .props         = std::move(value.props),
        .children      = std::move(value.children.nodes),
    };
}

namespace widgets::text_runtime
{
[[nodiscard]] inline auto type() -> std::type_index
{
    return std::type_index(typeid(text<>));
}

[[nodiscard]] inline auto matches(node const& value) -> bool
{
    return value.widget_type == type();
}

inline void resolve_style(node& value, style_registry const& styles)
{
    value.style.value = styles.resolve_dynamic<text>(value.style_classes);
}

[[nodiscard]] inline auto resolved_style(node const& value) -> text_style const&
{
    return std::any_cast<text_style const&>(value.style.value);
}

[[nodiscard]] inline auto resolved_props(node const& value) -> text_props const&
{
    return std::any_cast<text_props const&>(value.props);
}

[[nodiscard]] inline auto measure(node const& value, measure_context) -> cngui::size
{
    auto const& props     = resolved_props(value);
    auto const& style     = resolved_style(value);
    auto const  font_size = style.font_size.specified ? style.font_size.value : 16.0f;
    auto const  width     = static_cast<float>(props.value.value().size()) * font_size * 0.58f;

    return {
        .width  = std::max(1.0f, width),
        .height = font_size * 1.35f,
    };
}

inline void layout(node& value, layout_context context)
{
    value.bounds = context.bounds;
}

inline void render(node const& value, render_context context)
{
    auto const& props     = resolved_props(value);
    auto const& style     = resolved_style(value);
    auto const  font_size = style.font_size.specified ? style.font_size : 16_px;

    context.commands.push_back(render_command{
        .kind       = render_command_kind::text,
        .bounds     = value.bounds,
        .foreground = style.foreground.specified ? style.foreground : colors::white,
        .font_size  = font_size,
        .text       = props.value.value(),
    });
}
} // namespace widgets::text_runtime
} // namespace cngui

namespace cngui::meta
{
template<>
struct reflected_style<text_style>
{
    static constexpr bool available = true;
    static constexpr auto fields    = std::array{std::string_view{"foreground"}, std::string_view{"font_size"}};
};
} // namespace cngui::meta
