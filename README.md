# CNGui v2 Experiment

> Disclaimer: this branch is an experiment for the CNGui v2 direction. The API, internals, rendering model, and CMake options are still expected to change. Use it as a prototype for retained-mode, typed C++ UI ideas, not as a stable production dependency yet.

CNGui is a C++26 GUI framework experiment focused on building real application/game UI.

The current direction is:

- backend-independent core
- retained-mode widget tree
- static UI roots by default
- callable props for reactive values
- typed widget props
- typed widget styles
- type-safe style classes
- normal C++ functions for reusable components
- optional CNGui-owned window or embedding into an existing SFML window

## Requirements

- CMake 3.30+
- A C++26 compiler with support for the contract syntax used by the project
- GCC with `-freflection` support for the current experimental build setup
- SFML 3.1.0 is fetched by the project CMake

This project intentionally targets experimental C++ features. If your compiler does not support C++26 contracts or reflection flags yet, the build may fail.

## Consume With FetchContent

Add CNGui to your CMake project with `FetchContent`:

```cmake
include(FetchContent)

FetchContent_Declare(
    cngui
    GIT_REPOSITORY https://github.com/<owner>/cngui2.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)

set(CNGUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CNGUI_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(cngui)

add_executable(my_game main.cpp)
target_link_libraries(my_game PRIVATE cngui::cngui)
target_compile_features(my_game PRIVATE cxx_std_26)
```

Replace the repository URL and tag with the version you want to consume.

## Basic Model

CNGui uses a retained widget tree:

```cpp
app.set_ui(anchor{
    .props = {
        .position = anchor_position::top_right,
        .margin = 16_px,
    },
    .children = {
        text<my_style>{
            .props = {
                .value = "Hello CNGui",
            },
        },
    },
});
```

The root is static by default. This is intentional. Reactive values should usually be callables inside props:

```cpp
text<my_style>{
    .props = {
        .value = [&] {
            return std::format("Coins: {}", state.coins);
        },
    },
}
```

Use `set_dynamic_ui(...)` only when the root structure itself must be regenerated, such as large conditional trees or loops that change shape.

## Embedded In An Existing SFML Window

```cpp
#include <cngui/backend/sfml3.hpp>
#include <cngui/cngui.hpp>

#include <SFML/Graphics.hpp>
#include <format>
#include <utility>

using namespace cngui;

struct primary {};
struct rounded {};
struct snow {};

struct game_state
{
    int coins = 0;
    bool paused = false;
};

int main()
{
    sf::RenderWindow window{
        sf::VideoMode{{1280, 720}},
        "Game",
    };

    auto backend = sfml3::backend(window);
    backend.load_font("C:/Windows/Fonts/arial.ttf");

    gui app{std::move(backend)};
    auto& state = app.state(game_state{});

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

    app.set_ui(anchor{
        .props = {
            .position = anchor_position::top_right,
            .margin = 16_px,
        },
        .children = {
            button<primary, rounded>{
                .props = {
                    .text = [&] {
                        return state.paused ? "Resume" : "Pause";
                    },
                    .on_click = [&] {
                        state.paused = !state.paused;
                    },
                },
            },
            text<snow>{
                .props = {
                    .value = [&] {
                        return std::format("Coins: {}", state.coins);
                    },
                },
            },
        },
    });

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
            ++state.coins;
        }

        window.clear();
        app.update();
        app.draw();
        window.display();
    }
}
```

## CNGui-Owned Window

```cpp
#include <cngui/backend/sfml3.hpp>
#include <cngui/cngui.hpp>

using namespace cngui;

struct primary {};
struct rounded {};

int main()
{
    gui app{sfml3::backend(sfml3::window_options{
        .title = "CNGui App",
        .size = {900, 600},
        .vsync = true,
        .font_path = "C:/Windows/Fonts/arial.ttf",
    })};

    app.style<button, primary>(button_style{
        .background = colors::blue,
        .foreground = colors::white,
        .padding = {14_px, 10_px},
        .radius = 12_px,
    });

    app.set_ui(anchor{
        .props = {
            .position = anchor_position::center,
        },
        .children = {
            button<primary, rounded>{
                .props = {
                    .text = "Start",
                },
            },
        },
    });

    app.run();
}
```

## Style Classes

Style classes are C++ types:

```cpp
struct primary {};
struct danger {};
struct rounded {};
```

Styles are registered per widget type:

```cpp
app.style<button>(button_style{
    .background = colors::dark_gray,
    .foreground = colors::white,
});

app.style<button, primary>(button_style{
    .background = colors::blue,
});

app.style<button, rounded>(button_style{
    .radius = 12_px,
});
```

Then use the classes in the widget type:

```cpp
button<primary, rounded>{
    .props = {
        .text = "Save",
    },
}
```

The style type must match the widget type. For example, `app.style<button>(text_style{...})` is rejected at compile time.

## Repository Layout

- `include/cngui/core`: backend-independent primitives, retained nodes, input, render commands
- `include/cngui/widgets`: widget props, style, layout, render, and event behavior
- `include/cngui/style`: typed style registry and style merging
- `include/cngui/state`: state ownership and dirty detection
- `include/cngui/backend`: common backend interface and backend implementations
- `include/cngui/backend/sfml3`: SFML3 backend, renderer, event translation, window options
- `examples`: small runnable examples
- `tests`: Catch2 tests when `CNGUI_BUILD_TESTS` is enabled

## Current Limitations

- This is not a stable release.
- Layout is still minimal and will need richer containers.
- Text measurement is approximate in the core pipeline.
- Font handling is basic.
- Only the SFML3 backend exists right now.
- Reflection and contract usage follows the current experimental compiler support.

## Build Options

```cmake
CNGUI_BUILD_EXAMPLES=OFF
CNGUI_BUILD_TESTS=OFF
```

Tests use CTest and Catch2 when enabled:

```sh
cmake -S . -B build -DCNGUI_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```
