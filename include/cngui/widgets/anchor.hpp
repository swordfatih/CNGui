#pragma once

#include <cngui/core/children.hpp>
#include <cngui/core/geometry.hpp>
#include <cngui/core/node.hpp>
#include <cngui/meta/reflected_style.hpp>
#include <cngui/meta/type_list.hpp>
#include <cngui/widgets/context.hpp>

#include <array>
#include <any>
#include <string_view>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace cngui
{
enum class anchor_position
{
    top_left,
    top_right,
    bottom_left,
    bottom_right,
    center
};

struct anchor_props
{
    anchor_position position = anchor_position::top_left;
    edge_lengths    margin   = {};
};

struct anchor_style
{
};

template<class... style_classes>
struct anchor
{
    using props_type = anchor_props;
    using style_type = anchor_style;

    anchor_props    props    = {};
    cngui::children children = {};
};

inline void merge_style(anchor_style&, anchor_style const&)
{
}

template<class... style_classes>
[[nodiscard]] auto to_node(anchor<style_classes...> value) -> node
{
    return node{
        .widget_type   = std::type_index(typeid(anchor<>)),
        .style_classes = meta::type_list<style_classes...>(),
        .props         = std::move(value.props),
        .children      = std::move(value.children.nodes),
    };
}

namespace widgets::anchor_runtime
{
[[nodiscard]] inline auto type() -> std::type_index
{
    return std::type_index(typeid(anchor<>));
}

[[nodiscard]] inline auto matches(node const& value) -> bool
{
    return value.widget_type == type();
}

inline void resolve_style(node& value, style_registry const& styles)
{
    value.style.value = styles.resolve_dynamic<anchor>(value.style_classes);
}

[[nodiscard]] inline auto resolved_props(node const& value) -> anchor_props const&
{
    return std::any_cast<anchor_props const&>(value.props);
}

inline void layout(node& value, layout_context context)
{
    value.bounds = context.bounds;
}
} // namespace widgets::anchor_runtime
} // namespace cngui

namespace cngui::meta
{
template<>
struct reflected_style<anchor_style>
{
    static constexpr bool available = true;
    static constexpr auto fields    = std::array<std::string_view, 0>{};
};
} // namespace cngui::meta
