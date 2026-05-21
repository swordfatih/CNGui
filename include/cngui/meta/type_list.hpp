#pragma once

#include <typeindex>
#include <typeinfo>
#include <vector>

namespace cngui::meta
{
template<class... types>
[[nodiscard]] auto type_list() -> std::vector<std::type_index>
{
    return {std::type_index(typeid(types))...};
}
} // namespace cngui::meta
