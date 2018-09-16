#include <SFML/Graphics.hpp>
#include "CNGui.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 480), "CNGui Example");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style style;
    style.shape = CNGui::Shape::RoundedRectangle;
    style.fillcolor = sf::Color(200, 200, 200);
    style.hovercolor = sf::Color(100, 100, 100);
    style.selectable = false;
    style.outline = true;

    CNGui::Container<CNGui::Object> container(sf::Vector2f(500, 200), CNGui::Container<CNGui::Object>::Horizontal);

    CNGui::Button button("Button#001", sf::Vector3f(200, 100, 25), handleEvent, style);
    CNGui::Button button2("Start#002", sf::Vector3f(200, 100, 25), handleEvent, style);

    container << button << button2;
    container.setPosition(200, 100);
    container.setSpacing(10);

    while(window.isOpen())
    {
        handleEvent.clear();

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            handleEvent.push(event);
        }

        if(button(window) && button.onClick())
            button << "I think thats too long hahahahha";

        button2(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView()));

        window.clear();
        window.draw(container);
        window.display();
    }

    return 0;
}
