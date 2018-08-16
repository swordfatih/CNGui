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

    CNGui::Button button("Button#001", sf::Vector3f(200, 100, 25), handleEvent, style);
    button.setPosition(50, 50);

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

        if(button(sf::Mouse::getPosition(window)))
            button << "I think thats too long hahahahha";

        window.clear();
        window.draw(button);
        window.display();
    }
}
