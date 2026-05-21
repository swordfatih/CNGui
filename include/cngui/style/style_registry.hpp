#pragma once

#include <cngui/meta/type_list.hpp>

#include <any>
#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>

namespace cngui
{
class style_registry
{
public:
    template<template<class...> class widget_type, class... style_classes, class style_type>
    void set(style_type value)
    {
        using expected_style = typename widget_type<>::style_type;
        static_assert(std::same_as<std::remove_cvref_t<style_type>, expected_style>, "style type does not match the widget type");

        entries_.push_back(style_entry{
            .widget        = std::type_index(typeid(widget_type<>)),
            .style_classes = meta::type_list<style_classes...>(),
            .value         = std::move(value),
        });
    }

    template<template<class...> class widget_type, class... style_classes>
    [[nodiscard]] auto resolve() const -> typename widget_type<>::style_type
    {
        using style_type = typename widget_type<>::style_type;
        auto result      = style_type{};

        merge_for<widget_type>(result, {});
        (merge_for<widget_type>(result, std::vector<std::type_index>{std::type_index(typeid(style_classes))}), ...);

        return result;
    }

    template<template<class...> class widget_type>
    [[nodiscard]] auto resolve_dynamic(std::vector<std::type_index> const& style_classes) const -> typename widget_type<>::style_type
    {
        using style_type = typename widget_type<>::style_type;
        auto result      = style_type{};

        merge_for<widget_type>(result, {});
        for(auto const& style_class : style_classes)
        {
            merge_for<widget_type>(result, {style_class});
        }

        return result;
    }

private:
    struct style_entry
    {
        std::type_index              widget;
        std::vector<std::type_index> style_classes;
        std::any                     value;
    };

    template<template<class...> class widget_type>
    void merge_for(typename widget_type<>::style_type& result, std::vector<std::type_index> const& style_classes) const
    {
        for(auto const& entry : entries_)
        {
            if(entry.widget == std::type_index(typeid(widget_type<>)) && entry.style_classes == style_classes)
            {
                merge_style(result, std::any_cast<typename widget_type<>::style_type const&>(entry.value));
            }
        }
    }

    std::vector<style_entry> entries_;
};
} // namespace cngui
