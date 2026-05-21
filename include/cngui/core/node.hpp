#pragma once

#include <cngui/core/math.hpp>
#include <cngui/core/render_command.hpp>

#include <any>
#include <typeindex>
#include <typeinfo>
#include <vector>

namespace cngui
{
struct resolved_style
{
    std::any value = {};
};

struct node
{
    std::type_index              widget_type = std::type_index(typeid(void));
    std::vector<std::type_index> style_classes = {};
    std::any                     props         = {};
    std::vector<node>            children      = {};
    resolved_style               style         = {};
    rect                         bounds        = {};
    size                         measured_size = {};
    bool                         pointer_down  = false;
    bool                         props_dirty   = true;
    bool                         layout_dirty  = true;
    bool                         paint_dirty   = true;
};

template<class... style_classes>
struct button;

template<class... style_classes>
struct text;

template<class... style_classes>
struct panel;

template<class... style_classes>
struct anchor;

template<class... style_classes>
[[nodiscard]] auto to_node(button<style_classes...> value) -> node;

template<class... style_classes>
[[nodiscard]] auto to_node(text<style_classes...> value) -> node;

template<class... style_classes>
[[nodiscard]] auto to_node(panel<style_classes...> value) -> node;

template<class... style_classes>
[[nodiscard]] auto to_node(anchor<style_classes...> value) -> node;
} // namespace cngui
