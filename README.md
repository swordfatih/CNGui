# CNGui

CNGui (Chats Noirs Gui) is a graphical user interface (GUI) library using SFML and C++.
It is actually in development by Fatih#6810 from *Les Chats Noirs du Clair de Lune*.

***
**Prototype example code**


```cpp
#include <SFML/Graphics.hpp>
#include <CNGui.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 480), "Example");
    
    CNGui::EventHandler handleEvent;
    
    CNGui::Style style;
    style.type = CNGui::Style::Rectangle;
    style.hovercolor = sf::Color(200, 200, 200);
    style.rounded = true;
    
    CNGui::Button button("Start#001", sf::Vector2f(100, 50), handleEvent, style);
    
    CNGui::InputText input("Nickname#001", sf::Vector2f(100, 25), handleEvent, CNGui::Style::Default);
    
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

        if(button)
        {
            //Text objects returns output string
            // <<operator sets label of the object
            button << input; 
        }

        window.clear();
        window.draw(input);
        window.draw(button);
        window.display();
    }
}
```

