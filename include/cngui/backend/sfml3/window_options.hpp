#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <optional>
#include <string>

namespace cngui::sfml3
{
struct window_options
{
    std::string         title = "CNGui";
    sf::Vector2u        size  = {900, 600};
    bool                vsync = true;
    sf::State           state = sf::State::Windowed;
    sf::ContextSettings settings;
    std::optional<std::filesystem::path> font_path;
};
} // namespace cngui::sfml3
