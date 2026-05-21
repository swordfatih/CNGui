#pragma once

#include <cngui/backend/common.hpp>
#include <cngui/core/contracts.hpp>
#include <cngui/core/retained_tree.hpp>
#include <cngui/state/state_store.hpp>
#include <cngui/style/style_registry.hpp>
#include <cngui/widgets/runtime.hpp>

#include <concepts>
#include <memory>
#include <optional>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

namespace cngui
{
class gui
{
public:
    gui() = default;

    explicit gui(std::unique_ptr<backend_interface> backend)
        : backend_(std::move(backend))
    {
    }

    template<class backend_type>
        requires(std::derived_from<std::remove_cvref_t<backend_type>, backend_interface>)
    explicit gui(backend_type&& backend)
        : backend_(std::make_unique<std::remove_cvref_t<backend_type>>(std::forward<backend_type>(backend)))
    {
    }

    template<class state_type>
    auto state(state_type initial) -> state_type&
    {
        return states_.create(std::move(initial));
    }

    template<template<class...> class widget_type, class... style_classes, class style_type>
    void style(style_type value)
    {
        styles_.set<widget_type, style_classes...>(std::move(value));
        tree_.mark_dirty();
    }

    template<template<class...> class widget_type, class... style_classes>
    [[nodiscard]] auto resolve_style() const -> typename widget_type<>::style_type
    {
        return styles_.resolve<widget_type, style_classes...>();
    }

    template<class widget_type>
        requires(!std::is_invocable_v<widget_type&>)
    void set_ui(widget_type&& value)
    {
        tree_.set_root(std::forward<widget_type>(value));
    }

    template<class function_type>
        requires(std::is_invocable_v<function_type&>)
    void set_dynamic_ui(function_type function)
    {
        tree_.set_factory(std::move(function));
    }

    template<class event_type>
    void handle_event(event_type const& event)
    {
        if constexpr(std::same_as<std::remove_cvref_t<event_type>, input_event>)
        {
            handle_input_event(event);
        }
        else if(backend_)
        {
            auto translated = backend_->translate_native_event(std::type_index(typeid(std::remove_cvref_t<event_type>)), &event);
            if(translated)
            {
                handle_input_event(*translated);
            }
        }
    }

    void update()
    {
        if(states_.consume_changed())
        {
            tree_.mark_dirty();
        }

        tree_.update(styles_, current_viewport_size(), widgets::process);

        if(backend_)
        {
            backend_->update();
        }
    }

    void draw()
    {
        if(backend_)
        {
            backend_->draw(tree_.render_commands());
        }
    }

    void run()
        pre(backend_ != nullptr && backend_->owns_window())
    {
        while(backend_->is_open())
        {
            backend_->run_frame(
                [this](input_event const& event) {
                    handle_input_event(event);
                },
                [this] {
                    update();
                    draw();
                });
        }
    }

    [[nodiscard]] auto root() const -> node const*
    {
        return tree_.root();
    }

    [[nodiscard]] auto render_commands() const -> std::span<render_command const>
    {
        return tree_.render_commands();
    }

private:
    void handle_input_event(input_event const& event)
    {
        tree_.refresh(styles_, current_viewport_size(), widgets::process);

        if(tree_.dispatch(event, widgets::dispatch))
        {
            tree_.refresh(styles_, current_viewport_size(), widgets::process);
        }
    }

    [[nodiscard]] auto current_viewport_size() const -> size
    {
        if(backend_)
        {
            auto const viewport = backend_->viewport_size();
            if(viewport.width > 0.0f && viewport.height > 0.0f)
            {
                return viewport;
            }
        }

        return {.width = 800.0f, .height = 600.0f};
    }

    std::unique_ptr<backend_interface> backend_;
    state_store                        states_;
    style_registry                     styles_;
    retained_tree                      tree_;
};

using app = gui;
} // namespace cngui
