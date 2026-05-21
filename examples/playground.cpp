#include <string>
#include <utility>

#include <cngui/backend/sfml3.hpp>
#include <cngui/cngui.hpp>

#include <SFML/Graphics.hpp>

using namespace cngui;

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
    int  hp = 100;
    int  coins = 0;
    bool paused = false;
};

void hud(gui& app, game_state& state)
{
    app.style<button>(button_style{
        .background = colors::dark_gray,
        .foreground = colors::white,
        .padding = {12_px, 8_px},
        .radius = 4_px,
    });

    app.style<button, primary>(button_style{
        .background = colors::blue,
    });

    app.style<button, rounded>(button_style{
        .radius = 12_px,
    });

    app.style<text, snow>(text_style{
        .foreground = colors::white,
        .font_size = 18_px,
    });

    app.style<panel, snow>(panel_style{
        .background = colors::black_alpha(0.55f),
        .padding = 12_px,
    });

    app.style<panel, rounded>(panel_style{
        .radius = 12_px,
    });

    app.set_ui(anchor{
        .props = {
            .position = anchor_position::top_right,
            .margin = 16_px,
        },
        .children = {
            panel<snow, rounded>{
                .props = {
                    .gap = 8_px,
                },
                .children = {
                    text<snow>{
                        .props = {
                            .value = [&]
                            {
                                return std::format("HP: {}", state.hp);
                            },
                        },
                    },
                    text<snow>{
                        .props = {
                            .value = [&]
                            {
                                return std::format("Coins: {}", state.coins);
                            },
                        },
                    },
                    button<primary, rounded>{
                        .props = {
                            .text = [&]
                            {
                                return state.paused ? "Resume" : "Pause";
                            },
                            .on_click = [&]
                            {
                                state.paused = !state.paused;
                            },
                        },
                    },
                },
            },
        },
    });
}

int main()
{
    sf::RenderWindow window{
        sf::VideoMode{{1280, 720}},
        "CNGui playground",
    };

    auto backend = sfml3::backend(window);
    backend.load_font("C:/Windows/Fonts/arial.ttf");

    gui app{backend};

    auto& state = app.state<game_state>({});

    hud(app, state);

    while(window.isOpen())
    {
        while(auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            app.handle_event(*event);
        }

        if(!state.paused)
        {
            state.coins += 1;
        }

        window.clear();
        app.update();
        app.draw();
        window.display();
    }
}
