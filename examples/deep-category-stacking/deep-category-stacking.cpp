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

    CNGui::Category category_tres("Category Tres", style_category, {0, 100});
    category_tres.internal().setAlign(CNGui::Vertical).setMode(CNGui::Container::Static).setSize({0, 30});
    CNGui::Shape shape_uno(CNGui::Shape::Rectangle);
    category_tres.internal() << shape_uno;

    CNGui::Category category_quatro("Category Quatro", style_category, {0, 100});
    category_quatro.internal().setAlign(CNGui::Vertical).setMode(CNGui::Container::Static).setSize({0, 30});
    CNGui::Shape shape_dos(CNGui::Shape::Rectangle);
    category_quatro.internal() << shape_dos;

    CNGui::Category category_uno("Category Uno", style_category, {0, 100});
    category_uno.internal().setAlign(CNGui::Vertical).setMode(CNGui::Container::Dynamic).setSpacing(0).setSize({0, 200});
    category_uno.internal() << category_tres << category_quatro;

    CNGui::Category category_dos("Category Dos", style_category, {0, 100});
    category_dos.internal().setAlign(CNGui::Vertical).setMode(CNGui::Container::Static).setSize({0, 40});
    CNGui::Button button;
    category_dos.internal() << button;

    CNGui::Container container_main(CNGui::Vertical, {400, 0});
    container_main.setMode(CNGui::Container::Dynamic);
    container_main << category_uno << category_dos;

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        if(category_uno(window))
        {
            category_tres(window);
            category_quatro(window);
        }

        if(category_dos(window))
        {
            button(window);
        }

        window.clear();
        CNGui::Core::draw(window);
        window.display();
    }

    return 0;
}




