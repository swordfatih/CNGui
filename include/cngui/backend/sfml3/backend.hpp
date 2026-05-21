#pragma once

#include <cngui/backend/sfml3/renderer.hpp>
#include <cngui/backend/sfml3/window_options.hpp>
#include <cngui/backend/common.hpp>
#include <cngui/core/contracts.hpp>

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include <optional>
#include <span>
#include <typeindex>
#include <typeinfo>

namespace cngui::sfml3
{
class backend final : public backend_interface
{
public:
    explicit backend(sf::RenderWindow& window)
        : window_(&window)
    {
    }

    explicit backend(window_options options)
        : owned_window_(std::make_unique<sf::RenderWindow>(sf::VideoMode{options.size}, options.title, options.state, options.settings))
        , window_(owned_window_.get())
    {
        window_->setVerticalSyncEnabled(options.vsync);
        if(options.font_path)
        {
            renderer_.load_font(*options.font_path);
        }
    }

    auto load_font(std::filesystem::path const& path) -> bool
    {
        return renderer_.load_font(path);
    }

    [[nodiscard]] auto window() const -> sf::RenderWindow&
        pre(window_ != nullptr)
    {
        return *window_;
    }

    [[nodiscard]] auto owns_window() const -> bool override
    {
        return owned_window_ != nullptr;
    }

    [[nodiscard]] auto is_open() const -> bool override
    {
        return window_ != nullptr && window_->isOpen();
    }

    [[nodiscard]] auto viewport_size() const -> cngui::size override
    {
        if(window_ == nullptr)
        {
            return {};
        }

        auto const value = window_->getSize();
        return {.width = static_cast<float>(value.x), .height = static_cast<float>(value.y)};
    }

    [[nodiscard]] auto translate_native_event(std::type_index type, void const* event_pointer) const -> std::optional<input_event> override
    {
        if(type != std::type_index(typeid(sf::Event)) || event_pointer == nullptr)
        {
            return std::nullopt;
        }

        auto const& event = *static_cast<sf::Event const*>(event_pointer);

        if(event.is<sf::Event::Closed>())
        {
            return input_event{.kind = input_event_kind::window_closed};
        }

        if(auto const* moved = event.getIf<sf::Event::MouseMoved>())
        {
            return input_event{
                .kind  = input_event_kind::pointer_move,
                .point = {.x = static_cast<float>(moved->position.x), .y = static_cast<float>(moved->position.y)},
            };
        }

        if(auto const* pressed = event.getIf<sf::Event::MouseButtonPressed>())
        {
            return input_event{
                .kind   = input_event_kind::pointer_down,
                .point  = {.x = static_cast<float>(pressed->position.x), .y = static_cast<float>(pressed->position.y)},
                .button = to_pointer_button(pressed->button),
            };
        }

        if(auto const* released = event.getIf<sf::Event::MouseButtonReleased>())
        {
            return input_event{
                .kind   = input_event_kind::pointer_up,
                .point  = {.x = static_cast<float>(released->position.x), .y = static_cast<float>(released->position.y)},
                .button = to_pointer_button(released->button),
            };
        }

        return std::nullopt;
    }

    void run_frame(std::function<void(input_event const&)> const& event_sink, std::function<void()> const& frame) override
    {
        contract_assert(window_ != nullptr);
        contract_assert(static_cast<bool>(event_sink));
        contract_assert(static_cast<bool>(frame));

        while(auto event = window_->pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window_->close();
            }

            auto translated = translate_native_event(std::type_index(typeid(sf::Event)), &*event);
            if(translated)
            {
                event_sink(*translated);
            }
        }

        window_->clear();
        frame();
        window_->display();
    }

    void draw(std::span<render_command const> commands) override
    {
        contract_assert(window_ != nullptr);
        renderer_.draw(*window_, commands);
    }

private:
    [[nodiscard]] static auto to_pointer_button(sf::Mouse::Button button) -> pointer_button
    {
        switch(button)
        {
        case sf::Mouse::Button::Left:
            return pointer_button::left;
        case sf::Mouse::Button::Right:
            return pointer_button::right;
        case sf::Mouse::Button::Middle:
            return pointer_button::middle;
        default:
            return pointer_button::left;
        }
    }

    std::unique_ptr<sf::RenderWindow> owned_window_;
    sf::RenderWindow*                 window_ = nullptr;
    renderer                          renderer_;
};
} // namespace cngui::sfml3
