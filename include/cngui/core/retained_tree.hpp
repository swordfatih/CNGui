#pragma once

#include <cngui/core/node.hpp>
#include <cngui/core/render_command.hpp>
#include <cngui/core/input.hpp>
#include <cngui/style/style_registry.hpp>

#include <functional>
#include <optional>
#include <span>
#include <utility>
#include <vector>

namespace cngui
{
class retained_tree
{
public:
    using processor_type        = std::function<void(node&, style_registry const&, size, std::vector<render_command>&)>;
    using event_dispatcher_type = std::function<bool(node&, input_event const&)>;

    template<class function_type>
    void set_factory(function_type function)
    {
        ui_factory_ = [fn = std::move(function)]() mutable {
            return to_node(fn());
        };
        dirty_ = true;
    }

    template<class widget_type>
    void set_root(widget_type&& value)
    {
        ui_factory_ = {};
        root_       = to_node(std::forward<widget_type>(value));
        last_viewport_.reset();
        dirty_ = false;
    }

    void mark_dirty()
    {
        if(ui_factory_)
        {
            dirty_ = true;
        }
        else
        {
            last_viewport_.reset();
        }
    }

    void update(style_registry const& styles, size viewport, processor_type const& process)
        pre(static_cast<bool>(process))
    {
        if(!root_ && !ui_factory_)
        {
            return;
        }

        auto const viewport_changed = !last_viewport_ || *last_viewport_ != viewport;
        auto       should_process   = viewport_changed;

        if(dirty_)
        {
            if(ui_factory_)
            {
                root_ = ui_factory_();
            }
            dirty_ = false;
            should_process = true;
        }

        if(should_process)
        {
            rebuild_render_commands(styles, viewport, process);
            last_viewport_ = viewport;
        }
    }

    void refresh(style_registry const& styles, size viewport, processor_type const& process)
        pre(static_cast<bool>(process))
    {
        if(!root_ && ui_factory_)
        {
            root_ = ui_factory_();
            dirty_ = false;
        }

        if(root_)
        {
            rebuild_render_commands(styles, viewport, process);
            last_viewport_ = viewport;
        }
    }

    auto dispatch(input_event const& event, event_dispatcher_type const& dispatch_event) -> bool
        pre(static_cast<bool>(dispatch_event))
    {
        if(!root_)
        {
            return false;
        }

        return dispatch_event(*root_, event);
    }

    [[nodiscard]] auto root() const -> node const*
    {
        return root_ ? &*root_ : nullptr;
    }

    [[nodiscard]] auto render_commands() const -> std::span<render_command const>
    {
        return render_commands_;
    }

private:
    void rebuild_render_commands(style_registry const& styles, size viewport, processor_type const& process)
    {
        render_commands_.clear();
        if(root_)
        {
            process(*root_, styles, viewport, render_commands_);
        }
    }

    std::function<node()>       ui_factory_;
    std::optional<node>         root_;
    std::optional<size>         last_viewport_;
    std::vector<render_command> render_commands_;
    bool                        dirty_ = false;
};
} // namespace cngui
