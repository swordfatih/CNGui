#pragma once

#include <cngui/backend/sfml3/color.hpp>
#include <cngui/core/render_command.hpp>

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <optional>
#include <span>
#include <utility>

namespace cngui::sfml3
{
class renderer
{
public:
    auto load_font(std::filesystem::path const& path) -> bool
    {
        auto font = sf::Font{};
        if(!font.openFromFile(path))
        {
            return false;
        }

        font_ = std::move(font);
        return true;
    }

    void draw(sf::RenderWindow& window, std::span<render_command const> commands)
    {
        for(auto const& command : commands)
        {
            if(command.kind == render_command_kind::rectangle)
            {
                draw_rectangle(window, command);
            }
            else if(command.kind == render_command_kind::text)
            {
                draw_text(window, command);
            }
        }
    }

private:
    void draw_rectangle(sf::RenderWindow& window, render_command const& command)
    {
        if(!command.fill.specified)
        {
            return;
        }

        if(command.radius.specified && command.radius.value > 0.0f)
        {
            draw_rounded_rectangle(window, command);
            return;
        }

        auto shape = sf::RectangleShape{{command.bounds.width, command.bounds.height}};
        shape.setPosition({command.bounds.left, command.bounds.top});
        shape.setFillColor(to_sfml_color(command.fill));
        window.draw(shape);
    }

    void draw_rounded_rectangle(sf::RenderWindow& window, render_command const& command)
    {
        auto const radius = std::min(command.radius.value, std::min(command.bounds.width, command.bounds.height) * 0.5f);
        auto       shape  = sf::ConvexShape{};
        auto const steps  = 8U;

        shape.setPointCount(steps * 4);
        auto point_index = 0U;

        auto append_corner = [&](float center_x, float center_y, float start_angle) {
            for(auto index = 0U; index < steps; ++index)
            {
                auto const angle = (start_angle + static_cast<float>(index) / static_cast<float>(steps - 1U) * 90.0f) * 3.1415926535f / 180.0f;
                shape.setPoint(point_index++, {
                                                static_cast<float>(center_x + std::cos(angle) * radius),
                                                static_cast<float>(center_y + std::sin(angle) * radius),
                                            });
            }
        };

        append_corner(command.bounds.left + command.bounds.width - radius, command.bounds.top + radius, -90.0f);
        append_corner(command.bounds.left + command.bounds.width - radius, command.bounds.top + command.bounds.height - radius, 0.0f);
        append_corner(command.bounds.left + radius, command.bounds.top + command.bounds.height - radius, 90.0f);
        append_corner(command.bounds.left + radius, command.bounds.top + radius, 180.0f);

        shape.setFillColor(to_sfml_color(command.fill));
        window.draw(shape);
    }

    void draw_text(sf::RenderWindow& window, render_command const& command)
    {
        if(!font_ || command.text.empty())
        {
            return;
        }

        auto text = sf::Text{*font_};
        text.setString(command.text);
        text.setCharacterSize(static_cast<unsigned int>(command.font_size.value));
        text.setFillColor(to_sfml_color(command.foreground));
        text.setPosition({command.bounds.left, command.bounds.top});
        window.draw(text);
    }

    std::optional<sf::Font> font_;
};
} // namespace cngui::sfml3
