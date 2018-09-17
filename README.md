# CNGui (in development)

CNGui (Chats Noirs Gui) is a graphical user interface (GUI) library using SFML and C++.
It is actually in development by Fatih#6810 (accfldekur@gmail.com) from *Les Chats Noirs du Clair de Lune*.

***
**Example code**

An example code showing how CNGui is user-friendly and object-oriented! 

```cpp
#include <SFML/Graphics.hpp>
#include "CNGui.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 240), "CNGui Example");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style style;
    style.shape = CNGui::Shape::RoundedRectangle;
    style.fillcolor = sf::Color(200, 200, 200);
    style.hovercolor = sf::Color(100, 100, 100);
    style.selectable = true;
    style.outline = true;

    CNGui::Container<CNGui::Object> container(sf::Vector2f(200, 150), CNGui::Vertical);

    CNGui::Button buttonStart("Start#001", sf::Vector3f(200, 100, 25), handleEvent, style);
    CNGui::Button buttonReset("Reset#002", sf::Vector3f(200, 100, 25), handleEvent, style);

    container << buttonStart << buttonReset;
    container.setPosition(50, 30);
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
            buttonStart << "I think thats too long hahahahha";

        if(buttonReset(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView())))
            buttonStart << "Start";

        window.clear();
        window.draw(container);
        window.display();
    }

    return 0;
}
```
![output](https://media.giphy.com/media/orTDrM9QZH4H9P7QCJ/giphy.gif)

***
**Explanations**

`CNGui::EventHolder` class that holds SFML events that you can use further in the code to update your objects.

`CNGui::Style` struct that holds style parameters that the user can modify and apply to an object.

`CNGui::Object` base class for every objects.

`CNGui::Container` Class that can hold objects and other containers.

`CNGui::Shape` class that inheritates from `sf::Shape`, you can initialize it with different types of shape as Rectangle, Triangle, Circle or RoundedRectangle.

`CNGui::Font` class that holds hex arrays of few free fonts that you can use with an sf::Font by loading from memory. (actually holds only one, license in license.md file)

***
**Creating a new object made easy**

You can easily create a new object by inheriting from the Object class, your class has to contain an `uptade()` function and a SFML `draw()` function.

```cpp
#include "CNGui/Objects/Object.hpp"

class Button : public CNGui::Object
{
public:
    using CNGui::Object::Object;

private:
    void update()
    {
        if(mUpdate) 
        {
            //Update object's appearance here
            mShape.setType(mStyle.shape);
            mShape.setSize(mSize);
            mShape.setFillColor(mStyle.fillcolor);
            mUpdate = false;
        }
        
        //Update the object here
        if(sf::FloatRect(getPosition().x, getPosition().y, mShape.getGlobalBounds().width, mShape.getGlobalBounds().height).contains(mMouse)) //If button is hovered
        {
            if(mHandleEvent.isActive(sf::Event::MouseButtonPressed)) //If button is clicked
            {
                mShape.setFillColor(mStyle.clickedcolor);
                mReturn = true; 
            }
            else //If button is only hovered
            {
                mShape.setFillColor(mStyle.hovercolor);
                mReturn = false;
            }
        }
        else //If button is not hovered
        {
            mShape.setFillColor(mStyle.fillcolor);
        }
    }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        //Draw your members here
        target.draw(mShape, states);
    }

    CNGui::Shape mShape; ///< Background shape
};
```

Check `CNGui::Object`'s members to see what you can use for your object. If you need more style parameters to customize your object add it to the `CNGui::Style` struct.
Feel free to share your new super objects with the other users !

***
**More examples**

Stacking containers:

![stacking](https://i.imgur.com/ve9Qk0Y.png)

