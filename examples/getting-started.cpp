#include <SFML/Graphics.hpp>
#include "CNGui.hpp"

int main()
{
    sf::RenderWindow window({960, 480}, "CNGui Example");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style style;
    style.shape = CNGui::Shape::RoundedRectangle;
    style.fillcolor = {200, 200, 200};
    style.hovercolor = {100, 100, 100};
    style.selectable = true;
    style.outline = true;

    CNGui::Button buttonStart("Start#001", handleEvent, style, {200, 100});
    CNGui::Button buttonReset("Reset#002", handleEvent, style, {200, 100});

    CNGui::Container<CNGui::Object> container(CNGui::Horizontal, sf::Vector2f{500, 200});
    container << buttonStart << buttonReset;
    
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

        if(buttonStart(window) && buttonStart.onClick())
            buttonStart << "I think thats too long";

        if(buttonReset(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView())))
            buttonStart << "Start";

        window.clear();
        window.draw(container);
        window.display();
    }

    return 0;
}
