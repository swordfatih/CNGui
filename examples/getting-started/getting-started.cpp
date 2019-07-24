#include <CNGui/CNGui.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({400, 400}, "CNGui 1.1");

    CNGui::EventHandler handleEvent;

    CNGui::Button button_add("Click to add");
    CNGui::ProgressIndicator progression("Progression");

    CNGui::Container container(CNGui::Vertical, {200, 200});
    container << button_add << progression;

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        if(button_add(window) && button_add.onClick())
        {
            progression.add(0.1);
        }

        progression();

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}
