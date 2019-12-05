#include <CNGui/CNGui.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({940, 680}, "CNGui 1.1");

    CNGui::EventHandler handleEvent;

    CNGui::Style style_category;
    style_category.outline = true;
    style_category.background_color = {{50, 50, 50}, {20, 20, 20}, {45, 89, 125}};
    style_category.title_size = 48;

    CNGui::Shape shape_uno(CNGui::Shape::Rectangle, {100, 0});
    CNGui::Shape shape_dos(CNGui::Shape::Rectangle, {100, 0});
    CNGui::Button button;

    CNGui::Category category_dos("Category Dos", style_category, {250, 0});
    category_dos.internal().setAlign(CNGui::Vertical).setMode(CNGui::Container::Dynamic).setSize({250, 0});
    category_dos.internal() << button;

    CNGui::Category category_uno("Category Uno", style_category, {400, 200});
    category_uno.internal().setAlign(CNGui::Horizontal).setMode(CNGui::Container::Dynamic).setSpacing(0).setSize({0, 200});
    category_uno.internal() << shape_uno << category_dos << shape_dos;

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        if(category_uno(window))
        {
            if(category_dos(window))
            {
                button(window);
            }
        }

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}




