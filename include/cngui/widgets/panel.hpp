#pragma once

#include <cngui/core/children.hpp>
#include <cngui/core/color.hpp>
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
struct panel_props
{
    edge_lengths padding = {};
    length       gap     = {};
};

struct panel_style
{
    color        background = {};
    edge_lengths padding    = {};
    length       gap        = {};
    length       radius     = {};
};

template<class... style_classes>
struct panel
{
    using props_type = panel_props;
    using style_type = panel_style;

    panel_props     props    = {};
    cngui::children children = {};
};

inline void merge_style(panel_style& target, panel_style const& source)
{
    merge_if_specified(target.background, source.background);
    merge_if_specified(target.padding, source.padding);
    merge_if_specified(target.gap, source.gap);
    merge_if_specified(target.radius, source.radius);
}

template<class... style_classes>
[[nodiscard]] auto to_node(panel<style_classes...> value) -> node
{
    return node{
        .widget_type   = std::type_index(typeid(panel<>)),
        .style_classes = meta::type_list<style_classes...>(),
        .props         = std::move(value.props),
        .children      = std::move(value.children.nodes),
    };
}

namespace widgets::panel_runtime
{
[[nodiscard]] inline auto type() -> std::type_index
{
    return std::type_index(typeid(panel<>));
}

[[nodiscard]] inline auto matches(node const& value) -> bool
{
    return value.widget_type == type();
}

inline void resolve_style(node& value, style_registry const& styles)
{
    value.style.value = styles.resolve_dynamic<panel>(value.style_classes);
}

[[nodiscard]] inline auto resolved_style(node const& value) -> panel_style const&
{
    return std::any_cast<panel_style const&>(value.style.value);
}

[[nodiscard]] inline auto resolved_props(node const& value) -> panel_props const&
{
    return std::any_cast<panel_props const&>(value.props);
}

[[nodiscard]] inline auto padding(node const& value) -> edge_lengths
{
    auto const& props = resolved_props(value);
    auto const& style = resolved_style(value);
    return props.padding.specified ? props.padding : style.padding;
}

[[nodiscard]] inline auto gap(node const& value) -> float
{
    auto const& props = resolved_props(value);
    auto const& style = resolved_style(value);
    auto const  gap   = props.gap.specified ? props.gap : style.gap;
    return gap.specified ? gap.value : 0.0f;
}

inline void layout(node& value, layout_context context)
{
    value.bounds = context.bounds;
}

inline void render(node const& value, render_context context)
{
    auto const& style = resolved_style(value);
    if(!style.background.specified)
    {
        return;
    }

    context.commands.push_back(render_command{
        .kind   = render_command_kind::rectangle,
        .bounds = value.bounds,
        .fill   = style.background,
        .radius = style.radius,
    });
}
} // namespace widgets::panel_runtime
} // namespace cngui

namespace cngui::meta
{
template<>
struct reflected_style<panel_style>
{
    static constexpr bool available = true;
    static constexpr auto fields    = std::array{std::string_view{"background"}, std::string_view{"padding"}, std::string_view{"gap"}, std::string_view{"radius"}};
};
} // namespace cngui::meta
