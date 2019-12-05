#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({960, 840}, "CNGui 1.1");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style style_input;
    style_input.animation_duration = sf::milliseconds(200);
    style_input.main_shape = CNGui::Shape::RoundedRectangle;
    style_input.title_color.homogeneous(sf::Color::White);
    style_input.title_size = 20;
    style_input.outline = true;
    style_input.outline_thickness = 2;
    style_input.outline_color = style_input.main_color;
    style_input.outline_color.clicked = {220, 220, 220};

    CNGui::Container container_main;
    container_main.setPosition(50, 50);
    container_main.setAlign(CNGui::Vertical).setMode(CNGui::Container::Dynamic).setSize({400, 0});

    std::vector<CNGui::KeyEdit> input_edits;

    input_edits.resize(10);

    for(size_t i = 0; i < input_edits.size(); ++i)
    {
        input_edits[i].setStyle(style_input);
        input_edits[i].setName("String");
        container_main << input_edits[i];
    }

    CNGui::Container container_button;
    container_button.setAlign(CNGui::Horizontal).setMode(CNGui::Container::Static).setSize({400, 30});

    CNGui::Button button;

    CNGui::Text text;
    text.setFont(style_input.title_font);
    text.setString("String");
    text.setCharacterSize(18);

    container_button << text << button;

    container_main << container_button;

    CNGui::Slider slider;
    slider.setPosition(500, 200);
    slider.setSize({300, 24});
    slider.setStep(5);
    slider.setRange({-40, 150});
    slider.getStyle().title = false;

    auto&& style_slider = slider.getStyle();
    style_slider.main_shape = CNGui::Shape::Circle;
    style_slider.background_shape = CNGui::Shape::RoundedRectangle;
    style_slider.background_color.homogeneous({50, 50, 50});
    style_slider.secondary_color.homogeneous({100, 100, 100});
    style_slider.secondary_shape = style_slider.background_shape;
    style_slider.secondary_width = 24;
    style_slider.main_color.hovered.a = 200;
    style_slider.main_color.clicked.a = 200;
    style_slider.output_size = 24;
    style_slider.outline = true;
    style_slider.outline_thickness = 2;
    style_slider.outline_color.homogeneous(sf::Color::White);

    CNGui::LineSelect lineSelect;
    lineSelect.setStyle(slider.getStyle());
    lineSelect.getStyle().title = true;
    lineSelect.setPosition(500, 400);
    lineSelect.setSize({300, 24});
    lineSelect.setLines({"On", "Off", "Maybe", "Maybe not", "Not Sure", "Probably", "I don't know"});

    CNGui::Draw<sf::RectangleShape> hitbox;
    hitbox.setSize(lineSelect.getSize());
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(5);
    auto color_red = sf::Color::Red;
    color_red.a = 100;
    hitbox.setOutlineColor(color_red);
    hitbox.setPosition(lineSelect.getPosition());

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        for(auto& edit_key: input_edits)
        {
            edit_key(window);
        }

        if(button(window) && handleEvent.active(&button, "click"))
        {
            lineSelect.setValue(lineSelect.getValue() + 1);
        }

        slider(window);

        lineSelect(window);

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}
