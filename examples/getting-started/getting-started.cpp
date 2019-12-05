#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({400, 400}, "CNGui 1.1");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::ProgressIndicator progression("Progression");

    CNGui::Button button_decrease("-");
    CNGui::Button button_increase("+");

    CNGui::Container container_buttons(CNGui::Horizontal);
    container_buttons << button_decrease << button_increase;

    CNGui::Container container_main(CNGui::Vertical, {200, 200});
    container_main.setPosition(100, 100);
    container_main << progression << container_buttons;

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

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}
