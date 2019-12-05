#include <CNGui/CNGui.hpp>
#include <CNGui/Tools/Scissors.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({960, 840}, "CNGui 1.1");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    sf::CircleShape circle(100);
    circle.setPosition(50, 50);

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        window.clear();

        auto scissorStart = window.mapCoordsToPixel({circle.getPosition().x, circle.getPosition().y + circle.getRadius()});
        auto scissorSize = window.mapCoordsToPixel({circle.getRadius(), circle.getRadius()});

        CNGui::Scissors scissors({scissorStart.x, window.getSize().y - scissorStart.y, scissorSize.x, scissorSize.y});

        window.draw(circle);
        window.display();
    }

    return 0;
}
