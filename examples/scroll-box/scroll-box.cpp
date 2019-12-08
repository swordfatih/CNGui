#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({960, 840}, "CNGui 1.1");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style style_box;
    style_box.outline = true;
    style_box.title = true;
    style_box.title_size = 48;
    style_box.main_color.homogeneous({50, 50, 50});
    style_box.background_color.homogeneous({30, 30, 30});

    CNGui::Style style_category;
    style_category.outline = true;
    style_category.background_color.homogeneous({100, 100, 100});

    sf::Texture texture;
    texture.loadFromFile("examples/scroll-box/assets/picture.jpg");

    /*sf::RectangleShape shape(sf::Vector2f(texture.getSize()));
    shape.setTexture(&texture);*/

    CNGui::Box box("Object", style_box, {400, 400});
    box.setPosition(100, 100);
    box.internal().setAlign(CNGui::Vertical).setMode(CNGui::Container::Dynamic).setSize({500, 0});

    CNGui::Category category;
    category.setName("Credits");
    category.setSize({0, 40});
    category.internal().setAlign(CNGui::Vertical).setMode(CNGui::Container::Stacked).setSize({0, 0});

    CNGui::Poster poster("Poster", {}, {500, 500});
    poster.setDescription("blablabla");
    poster.getStyle().background_texture = texture;

    category.internal() << poster;
    box.internal() << category;

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        box(window);

        auto cropped_mouse = box.crop_position(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

        if(category(cropped_mouse))
        {
            poster(cropped_mouse);
        }

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}
