#pragma once

#include <cngui/backend/sfml3/backend.hpp>

#include <memory>
#include <utility>

namespace cngui::sfml3
{
[[nodiscard]] inline auto backend_for(sf::RenderWindow& window) -> std::unique_ptr<backend_interface>
{
    return std::make_unique<backend>(window);
}

[[nodiscard]] inline auto backend_for(window_options options) -> std::unique_ptr<backend_interface>
{
    return std::make_unique<backend>(std::move(options));
}

[[nodiscard]] inline auto make_backend(sf::RenderWindow& window) -> std::unique_ptr<backend_interface>
{
    return backend_for(window);
}

[[nodiscard]] inline auto make_backend(window_options options) -> std::unique_ptr<backend_interface>
{
    return backend_for(std::move(options));
}
} // namespace cngui::sfml3
