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
    sf::RenderWindow window({300, 200}, "CNGui Example");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style styleButton;
    styleButton.shape = CNGui::Shape::RoundedRectangle;
    styleButton.fillcolor = {200, 200, 200};
    styleButton.hovercolor = {100, 100, 100};
    styleButton.outline = true;

    CNGui::Style styleProgression = styleButton;
    styleProgression.fillcolor = {80, 255, 129};
    styleProgression.charactersize = 16;

    CNGui::ProgressIndicator progression("Progression#001", handleEvent, styleProgression);
    CNGui::Button button("Add#001", handleEvent, styleButton);

    CNGui::Container<CNGui::Object> container(CNGui::Vertical, {200, 100});
    container << progression << button;

    container.setPosition(50, 30);
    container.setSpacing(25);

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

        if(button(window) && button.onClick())
            progression.setProgression(progression.getProgression() + 0.1);

        if(progression())
            progression << "Progression done";

        window.clear();
        window.draw(container);
        window.display();
    }

    return 0;
}
```
![output](https://media.discordapp.net/attachments/468477582761918465/491657988185128960/progress2.gif)

***
Classes | Description
------- | -----------
`CNGui::EventHolder` | Class that holds SFML events that you can use further in the code to update your objects.
`CNGui::Style` | Struct that holds style parameters that the user can modify and apply to an object.
`CNGui::Object` | Base class for every objects.
`CNGui::Container` | Class that can hold objects and other containers to sort them.
`CNGui::Shape` | Class that inheritates from `sf::Shape`, you can initialize it with different types of shape as Rectangle, Triangle, Circle or RoundedRectangle.
`CNGui::Font` | Class that holds hex arrays of few free fonts that you can use with an sf::Font by loading from memory. (actually holds only one, license in license.md file)

Objects | Description
------- | -----------
`CNGui::Button` | Button object. Exists as `CNGui::Shape::Rectangle` and `CNGui::Shape::RoundedRectangle` 
`CNGui::ProgressIndicator` | Progress indicator object. Exists as `CNGui::Shape::Rectangle` and `CNGui::Shape::RoundedRectangle` 

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
More examples | Screen
------------- | ------
Stacking containers | ![stacking](https://i.imgur.com/ve9Qk0Y.png)

