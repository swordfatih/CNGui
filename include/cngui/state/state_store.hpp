#pragma once

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace cngui
{
class state_store
{
public:
    template<class state_type>
    auto create(state_type initial) -> state_type&
    {
        struct holder final : state_holder
        {
            explicit holder(state_type value)
                : data(std::move(value))
                , snapshot(data)
            {
            }

            [[nodiscard]] auto changed() -> bool override
            {
                if constexpr(requires(state_type const& lhs, state_type const& rhs) { lhs == rhs; })
                {
                    if(snapshot == data)
                    {
                        return false;
                    }

                    snapshot = data;
                    return true;
                }
                else
                {
                    return true;
                }
            }

            state_type data;
            state_type snapshot;
        };

        auto owned = std::make_unique<holder>(std::move(initial));
        auto& data = owned->data;
        states_.push_back(std::move(owned));
        return data;
    }

    [[nodiscard]] auto consume_changed() -> bool
    {
        auto changed = false;
        for(auto& state : states_)
        {
            changed = state->changed() || changed;
        }

        return changed;
    }

private:
    struct state_holder
    {
        virtual ~state_holder() = default;
        [[nodiscard]] virtual auto changed() -> bool = 0;
    };

    std::vector<std::unique_ptr<state_holder>> states_;
};
} // namespace cngui
