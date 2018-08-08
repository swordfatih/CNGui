# CNGui

CNGui (Chats Noirs Gui) is a graphical user interface (GUI) library using SFML and C++.
It is actually in development by Fatih#6810 from *Les Chats Noirs du Clair de Lune*.

***
**Prototype example code**


```cpp
#include <SFML/Graphics.hpp>
#include <CNGui.hpp>

struct Style
{
    sf::Color hoverColor;
} buttonStyle;

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 480), "Example");
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
        }
    }
}
```

