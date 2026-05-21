#include <cngui/cngui.hpp>

#include <catch2/catch_test_macros.hpp>

#include <concepts>
#include <memory>
#include <string>
#include <typeindex>

using namespace cngui;

namespace
{
struct primary
{
};

struct rounded
{
};

struct snow
{
};

struct game_state
{
    int coins = 0;

    [[nodiscard]] friend auto operator==(game_state const&, game_state const&) -> bool = default;
};

class test_backend final : public cngui::backend_interface
{
public:
    [[nodiscard]] auto viewport_size() const -> cngui::size override
    {
        return {.width = 800.0f, .height = 600.0f};
    }
};
} // namespace

TEST_CASE("typed styles merge defaults and style classes in order")
{
    cngui::gui app;

    app.style<cngui::button>(cngui::button_style{
        .background = cngui::colors::dark_gray,
        .foreground = cngui::colors::white,
        .padding    = {12_px, 8_px},
        .radius     = 4_px,
    });

    app.style<cngui::button, primary>(cngui::button_style{
        .background = cngui::colors::blue,
    });

    app.style<cngui::button, rounded>(cngui::button_style{
        .radius = 12_px,
    });

    auto const style = app.resolve_style<cngui::button, primary, rounded>();

    CHECK(style.background.r == cngui::colors::blue.r);
    CHECK(style.foreground.r == cngui::colors::white.r);
    CHECK(style.padding.x.value == 12.0f);
    CHECK(style.padding.y.value == 8.0f);
    CHECK(style.radius.value == 12.0f);
}

TEST_CASE("heterogeneous children become a retained node tree")
{
    auto tree = cngui::to_node(cngui::panel<rounded>{
        .props = {
            .padding = 16_px,
            .gap     = 8_px,
        },
        .children = {
            cngui::text<snow>{
                .props = {.value = "Inventory"},
            },
            cngui::button<primary, rounded>{
                .props = {.text = "Use"},
            },
        },
    });

    REQUIRE(tree.widget_type == std::type_index(typeid(cngui::panel<>)));
    REQUIRE(tree.children.size() == 2);
    CHECK(tree.children[0].widget_type == std::type_index(typeid(cngui::text<>)));
    CHECK(tree.children[1].widget_type == std::type_index(typeid(cngui::button<>)));
}

TEST_CASE("state changes rebuild computed render commands")
{
    cngui::gui app;
    auto&      state = app.state(game_state{});

    app.set_ui(cngui::text<snow>{
            .props = {
                .value = [&] {
                    return std::string{"Coins: "} + std::to_string(state.coins);
                },
            },
        });

    app.update();
    REQUIRE(app.render_commands().size() == 1);
    CHECK(app.render_commands()[0].text == "Coins: 0");

    state.coins = 42;
    app.update();

    REQUIRE(app.render_commands().size() == 1);
    CHECK(app.render_commands()[0].text == "Coins: 42");
}

TEST_CASE("widget style API rejects mismatched style structs at compile time")
{
    STATIC_CHECK(std::same_as<cngui::button<>::style_type, cngui::button_style>);
    STATIC_CHECK(!std::same_as<cngui::button<>::style_type, cngui::text_style>);
}

TEST_CASE("anchor positions content relative to the backend viewport")
{
    cngui::gui app{std::make_unique<test_backend>()};

    app.set_ui(cngui::anchor{
            .props = {
                .position = cngui::anchor_position::top_right,
                .margin   = 16_px,
            },
            .children = {
                cngui::button<primary>{
                    .props = {.text = "Use"},
                },
            },
        });

    app.update();

    auto const* root = app.root();
    REQUIRE(root != nullptr);
    REQUIRE(root->children.size() == 1);
    CHECK(root->children[0].bounds.right() == 784.0f);
}

TEST_CASE("button dispatches click callbacks through hit testing")
{
    cngui::gui app{std::make_unique<test_backend>()};
    auto       clicked = false;

    app.set_ui(cngui::button<primary>{
            .props = {
                .text = "Use",
                .on_click = [&] {
                    clicked = true;
                },
            },
        });

    app.handle_event(cngui::input_event{
        .kind  = cngui::input_event_kind::pointer_down,
        .point = {.x = 20.0f, .y = 20.0f},
    });
    app.handle_event(cngui::input_event{
        .kind  = cngui::input_event_kind::pointer_up,
        .point = {.x = 20.0f, .y = 20.0f},
    });

    CHECK(clicked);
}
