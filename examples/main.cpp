#include <SFML/Graphics.hpp>
#include "CNGui.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "CNGui Example");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style style;
    style.shape = CNGui::Shape::RoundedRectangle;
    style.fillcolor = sf::Color(200, 200, 200);
    style.hovercolor = sf::Color(100, 100, 100);
    style.selectable = true;
    style.outline = true;

    CNGui::Container<CNGui::Container<CNGui::Object>> containerMain(sf::Vector3f(500, 300, 0), CNGui::ContainerType::Vertical);

    CNGui::Container<CNGui::Object> containerButton(sf::Vector3f(200, 150, 0), CNGui::ContainerType::Vertical);
    CNGui::Container<CNGui::Object> containerTest(sf::Vector3f(200, 150, 0), CNGui::ContainerType::Horizontal);

    CNGui::Button buttonStart("Start#001", sf::Vector3f(200, 100, 25), handleEvent, style);
    CNGui::Button buttonReset("Reset#001", sf::Vector3f(200, 100, 25), handleEvent, style);
    CNGui::Button buttonTestOne("Test#001", sf::Vector3f(200, 100, 25), handleEvent, style);
    CNGui::Button buttonTestTwo("Test#002", sf::Vector3f(200, 100, 25), handleEvent, style);

    containerButton << buttonStart << buttonReset;
    containerTest << buttonTestOne << buttonTestTwo;

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
            buttonStart << "I think thats too long hahahahha";

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





