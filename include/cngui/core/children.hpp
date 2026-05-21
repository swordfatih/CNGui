#pragma once

#include <cngui/core/node.hpp>

#include <cstddef>
#include <utility>
#include <vector>

namespace cngui
{
struct children
{
    std::vector<node> nodes;

    children() = default;

    template<class... child_types>
    children(child_types&&... values)
    {
        (push(std::forward<child_types>(values)), ...);
    }

    template<class child_type>
    void push(child_type&& value)
    {
        nodes.push_back(to_node(std::forward<child_type>(value)));
    }

    [[nodiscard]] auto size() const -> std::size_t
    {
        return nodes.size();
    }

    [[nodiscard]] auto empty() const -> bool
    {
        return nodes.empty();
    }
};
} // namespace cngui
