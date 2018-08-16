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
    style.shape = CNGui::Style::Rectangle;
    style.fillcolor = sf::Color(200, 200, 200);
    style.hovercolor = sf::Color(100, 100, 100);
    style.rounded = true;
    
    CNGui::Button button("Start#001", sf::Vector2f(100, 50), handleEvent, style);
    
    CNGui::InputText input("Nickname#001", sf::Vector2f(100, 25), handleEvent, CNGui::Style);
    
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

***
## Creating a new object made easy

```cpp
class Button : public Object
{
public:
    using Object::Object;

private:
    void update()
    {
        if(mUpdate)
        {
            mShape.setType(mStyle.shape);
            mShape.setSize(mSize);
            mShape.setFillColor(mStyle.fillcolor);
            mUpdate = false;
        }
        
                if(sf::FloatRect(getPosition().x, getPosition().y, mShape.getGlobalBounds().width, mShape.getGlobalBounds().height).contains(mMouse))
        {
            if(mHandleEvent.isActive(sf::Event::MouseButtonPressed))
            {
                mShape.setFillColor(mStyle.clickedcolor);
                mReturn = true;
            }
            else
            {
                mShape.setFillColor(mStyle.hovercolor);
                mReturn = false;
            }
        }
        else
        {
            mShape.setFillColor(mStyle.fillcolor);
        }
    }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(mShape, states);
    }

    Shape mShape; // Background shape
};
```
