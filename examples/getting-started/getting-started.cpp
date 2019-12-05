#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({960, 840}, "CNGui 1.1");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::ProgressIndicator progression("Progression");

    CNGui::Button button_decrease("-");
    CNGui::Button button_increase("+");

    CNGui::Container container_buttons(CNGui::Horizontal);
    container_buttons << button_decrease << button_increase;

    CNGui::Container container_main(CNGui::Vertical, {200, 200});
    container_main.setPosition(200, 200);
    container_main << progression << container_buttons;

    sf::Texture texture;
    texture.loadFromFile("examples/getting-started/shop.png");

    CNGui::Poster poster("News !", {}, {200, 200});
    poster.setPosition(200, 600);
    poster.getStyle().background_color.neutral = {100, 200, 255, 255};
    poster.getStyle().background_texture = texture;
    poster.getStyle().animation_duration = sf::seconds(2);
    poster.setDate("07/08/2019");
    poster.setDescription("Nothing to report today..");

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        if(button_increase(window) && handleEvent.active(&button_increase, "click"))
        {
            progression.add(0.1);
        }

        if(button_decrease(window) && handleEvent.active(&button_decrease, "click"))
        {
            progression.add(-0.1);
        }

        progression();

        poster(window);

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}
