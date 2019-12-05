#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({600, 400}, "CNGui 1.1");

    CNGui::EventHandler handleEvent;

    CNGui::Container container_left(CNGui::Vertical);
    CNGui::LineEdit edit_left("Left edit");
    CNGui::Button button_left("Hello");
    sf::RectangleShape shape;
    container_left << edit_left << button_left << shape;

    CNGui::Container container_right(CNGui::Vertical);
    CNGui::LineEdit edit_right("Right edit");
    CNGui::Button button_right("Hello");
    container_right << edit_right << button_right;

    CNGui::Container container_main(CNGui::Horizontal, {200, 200});
    container_main.setPosition(50, 50);
    container_main << container_left << container_right;

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        edit_left(window);
        edit_right(window);

        if(button_left(window) && button_left.onClick())
        {
            button_left << edit_left.getString();
        }
        
        if(button_right(window) && button_right.onClick())
        {
            button_right << edit_right.getString();
        }

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}




