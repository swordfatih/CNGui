#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

///////////////////////////////////////////////////////////
void switch_button(CNGui::Container& container, std::vector<CNGui::Button>& buttons, size_t& last_index, const size_t& index)
{
    buttons[last_index].getStyle().main_color.neutral = buttons[index].getStyle().main_color.neutral;
    buttons[index].getStyle().main_color.neutral = buttons[index].getStyle().main_color.clicked;

    last_index = index;

    container.clear();

    std::vector<CNGui::Button*> contents;

    if(index == 0)
    {
        contents.push_back(&buttons.back());
    }
    else
    {
        contents.push_back(&buttons[index - 1]);
    }

    contents.push_back(&buttons[index]);

    for(size_t i = index + 1; i < buttons.size(); ++i)
    {
        if(!(index == 0 && i == buttons.size() - 1))
        {
            contents.push_back(&buttons[i]);
        }
    }

    if(index != 0)
    {
        for(size_t i = 0; i < index - 1; ++i)
        {
            contents.push_back(&buttons[i]);
        }
    }

    for(auto& content: contents)
    {
        container << *content;
    }
}

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({840, 680}, "CNGui 1.1");

    CNGui::InteractiveColor color;
    color.homogeneous({50, 57, 89});

    CNGui::EventHandler handleEvent;

    //Buttons
    std::vector<CNGui::Button> buttons;
    size_t last_index = 1;

    //Textures
    std::vector<sf::Texture> textures;

    for(const auto& entry: std::filesystem::directory_iterator("examples/infinite-scrolling-menu/assets"))
    {
        textures.emplace_back();
        textures.back().loadFromFile(entry.path().string());

        CNGui::Button button("");

        button.getStyle().selectable = false;
        button.getStyle().main_texture = textures.back();

        buttons.push_back(std::move(button));
    }

    //Container
    CNGui::Container container_main(CNGui::Vertical, {100, 600});
    container_main.setPosition(420, 50);
    container_main.setSpacing(0);

    for(auto& button: buttons)
    {
        container_main << button;
    }

    //Background
    sf::ConvexShape shape_background(5);
    shape_background.setFillColor({50, 50, 50});

    float left = container_main.getPosition().x;
    float right = container_main.getPosition().x + container_main.getSize().x;
    float top = container_main.getPosition().y - buttons[0].getSize().y / 2;
    float bottom = container_main.getPosition().y + container_main.getSize().y;

    shape_background.setPoint(0, {left, top});
    shape_background.setPoint(1, {left + buttons[0].getSize().x / 2, top});
    shape_background.setPoint(2, {right, top + buttons[0].getSize().y / 2});
    shape_background.setPoint(3, {right, bottom});
    shape_background.setPoint(4, {left, bottom});

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        if(auto event = handleEvent.get_if(sf::Event::MouseWheelMoved))
        {
            size_t index = last_index;
            if(event->mouseWheel.delta > 1)
            {
                index++;

                if(index >= buttons.size())
                {
                    index = 0;
                }
            }
            else
            {
                index--;

                if(last_index == 0)
                {
                    index = buttons.size() - 1;
                }
            }

            switch_button(container_main, buttons, last_index, index);
        }

        for(auto& button: buttons)
        {
            if(button(window) && button.onClick())
            {
                switch_button(container_main, buttons, last_index, &button - &buttons[0]);
                break;
            }
        }

        window.clear();
        window.draw(shape_background);
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}
