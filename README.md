# CNGui 

CNGui (Chats Noirs Gui) is a new graphical user interface (GUI) library using SFML and C++.
It is actually in development by Fatih#6810 (accfldekur@gmail.com) from *Moonlit Black Cats*.

***
**Example code**

An example code showing how CNGui is user-friendly and object-oriented! 

```cpp
#include <SFML/Graphics.hpp>
#include <CNGui/CNGui.hpp>

int main()
{
    sf::RenderWindow window({300, 200}, "CNGui Example");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::Style styleButton;
    styleButton.shape = CNGui::Shape::RoundedRectangle;
    styleButton.outline = true;

    CNGui::Style styleProgression = styleButton;
    styleProgression.fillcolor = {80, 255, 129};
    styleProgression.charactersize = 16;

    CNGui::ProgressIndicator progression("Progression#001", handleEvent, styleProgression);
    CNGui::Button button("Add#001", handleEvent, styleButton);

    CNGui::Container<CNGui::Object> container(CNGui::Vertical, {200, 150});
    container.setPosition(50, 20);

    container << progression << button;

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
            progression.add(0.1);

        if(progression())
            progression << "Progression done";

        window.clear();
        window.draw(container);
        window.display();
    }

    return 0;
}
```

![output](https://cdn.discordapp.com/attachments/468477582761918465/493467406740750347/progressease4.gif)

***
Utilities | Description
------- | -----------
`CNGui::EventHolder` | Class that holds SFML events that you can use further in the code to update your objects.
`CNGui::Style` | Struct that holds style parameters that the user can modify and apply to an object.
`CNGui::Shape` | Class that inheritates from `sf::Shape`, you can initialize it with different types of shape as Rectangle, Triangle, Circle or RoundedRectangle.
`CNGui::Font` | Class that holds hex arrays of few free fonts that you can use with an sf::Font by loading from memory. (actually holds only one, license in license.md file)
`CNGui::Text` | Class that inheritates from `sf::Text`, you can apply a limit size that the text wont exceed.
`CNGui::FunctionWrapper` | Class that can store a `std::function` and execute it on another `std::thread`.

Containers | Description
------- | -----------
`CNGui::Container` | Class that can hold objects and other containers to sort them.

Objects | Description
------- | -----------
`CNGui::Object` | Base class for every objects.
`CNGui::Button` | Button object. Exists as `CNGui::Shape::Rectangle`, `CNGui::Shape::RoundedRectangle`, `CNGui::Shape::Triangle` and `CNGui::Shape::Circle`.
`CNGui::ProgressIndicator` | Progress indicator object. Exists as `CNGui::Shape::Rectangle` and `CNGui::Shape::RoundedRectangle`, animatable.
`CNGui::LineEdit` | Line edit object to input text, animatable. 
`CNGui::Poster` | Poster object to add a title, date and a description to your pictures, animatable.

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
Stacking containers | ![stacking](https://media.discordapp.net/attachments/468477582761918465/491665422438105088/containerstacking.PNG?width=378&height=300)
Poster object | ![poster](https://cdn.discordapp.com/attachments/414535658410082341/526071702614966272/poster.gif)

