# CNGui

CNGui (Chats Noirs Gui) is a graphical user interface (GUI) library using SFML and C++.
It is actually in development by Fatih#6810 from *Les Chats Noirs du Clair de Lune*.

***
**Prototype example code**


```cpp
#include <SFML/Graphics.hpp>
#include <CNGui.hpp>

struct ButtonStyle
{
    CNGui::Type type = CNGui::Type::Circle;
    sf::Color hoverColor = sf::Color(200, 200, 200);
} buttonStyle;

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 480), "Example");
    
    CNGui::Button buttonStart("start#001", sf::Vector2f(100, 50), buttonStyle); 
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(button)
        {
            //Action
        }

        window.clear();
        window.draw(button);
        window.display();
    }
}
```

