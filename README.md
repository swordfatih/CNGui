**Many things are changing with the 1.1 version (master branch), this version isn't stable.
The following text is about CNGui 1.0.**

# CNGui 1.1 (in development)

CNGui (Chats Noirs Gui) is a new graphical user interface (GUI) library using SFML and C++.
It is actually in development by Fatih#6810 (accfldekur@gmail.com) from *Moonlit Black Cats*.

***
**Example code**

An example code showing how user-friendly and object-oriented CNGui is!

```cpp
#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({400, 400}, "CNGui 1.1");
    window.setFramerateLimit(60);

    CNGui::EventHandler handleEvent;

    CNGui::ProgressIndicator progression("Progression");

    CNGui::Button button_decrease("-");
    CNGui::Button button_increase("+");

    CNGui::Container container_buttons(CNGui::Horizontal);
    container_buttons << button_decrease << button_increase;

    CNGui::Container container_main(CNGui::Vertical, {200, 200});
    container_main.setPosition(100, 100);
    container_main << progression << container_buttons;

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        if(button_increase(window) && handleEvent.active(&button_increase, "click"))
        {
            progression.add(0.1);
        }

        if(button_decrease(window) && handleEvent.active(&button_decrease, "click"))
        {
            progression.add(-0.1);
        }

        progression();

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}
```

![output](https://cdn.discordapp.com/attachments/375019222004137985/652184319657508911/cngui-getting-started.gif)

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

You can easily create a new object by inheriting from the Object class, your class has to contain an `update()` function and a SFML `draw()` function.

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

