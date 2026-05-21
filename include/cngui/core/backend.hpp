#pragma once

#include <cngui/core/input.hpp>
#include <cngui/core/math.hpp>
#include <cngui/core/render_command.hpp>

#include <functional>
#include <optional>
#include <span>
#include <typeindex>
#include <typeinfo>

namespace cngui
{
class backend_interface
{
public:
    virtual ~backend_interface() = default;

    virtual void update()
    {
    }

    virtual void draw(std::span<render_command const>)
    {
    }

    [[nodiscard]] virtual auto viewport_size() const -> size
    {
        return {};
    }

    [[nodiscard]] virtual auto translate_native_event(std::type_index, void const*) const -> std::optional<input_event>
    {
        return std::nullopt;
    }

    [[nodiscard]] virtual auto owns_window() const -> bool
    {
        return false;
    }

    [[nodiscard]] virtual auto is_open() const -> bool
    {
        return false;
    }

    virtual void run_frame(std::function<void(input_event const&)> const&, std::function<void()> const& frame)
    {
        if(frame)
        {
            frame();
        }
    }
};
} // namespace cngui
