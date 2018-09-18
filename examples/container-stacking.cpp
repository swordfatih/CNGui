#include <SFML/Graphics.hpp>
#include "CNGui.hpp"

int main()
{
    sf::RenderWindow window({640, 480}, "CNGui Example");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style style;
    style.shape = CNGui::Shape::RoundedRectangle;
    style.fillcolor = {200, 200, 200};
    style.hovercolor = {100, 100, 100};
    style.selectable = true;
    style.outline = true;

    CNGui::Button buttonStart("Start#001", handleEvent, style, {200, 100});
    CNGui::Button buttonReset("Reset#001", handleEvent, style, {200, 100});
    CNGui::Button buttonTestOne("Test#001", handleEvent, style, {200, 100});
    CNGui::Button buttonTestTwo("Test#002", handleEvent, style, {200, 100});

    CNGui::Container<CNGui::Object> containerButton(CNGui::Vertical, sf::Vector2f(200, 150));
    containerButton << buttonStart << buttonReset;
    
    CNGui::Container<CNGui::Object> containerTest(CNGui::Horizontal, sf::Vector2f(200, 150));
    containerTest << buttonTestOne << buttonTestTwo;

    CNGui::Container<CNGui::Container<CNGui::Object>> containerMain(CNGui::Vertical, {500, 300});
    containerMain << containerButton << containerTest;
    
    containerMain.setSpacing(50);
    containerMain.setPosition(70, 50);

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

        buttonTestOne(window);
        buttonTestTwo(window);

        window.clear();
        window.draw(containerMain);
        window.display();
    }

    return 0;
}





