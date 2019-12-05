#include <CNGui/CNGui.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
int main()
{
    sf::RenderWindow window({960, 640}, "CNGui 1.1", sf::Style::Fullscreen);
    window.setFramerateLimit(10);

    CNGui::EventHandler handleEvent;

    std::vector<sf::CircleShape> points;

    sf::Clock clock_current;
    const sf::Time duration = sf::seconds(10);

    size_t count_frame = 0;

    while(window.isOpen())
    {
        handleEvent.process(window);

        if(handleEvent.get_if(sf::Event::Closed))
        {
            window.close();
        }

        if(clock_current.getElapsedTime() < duration)
        {
            // Trigonometry
            points.emplace_back(2).setPosition(50 + count_frame, 200 - CNGui::ease(CNGui::trigonometry::in, clock_current, duration, 150));
            points.emplace_back(2).setPosition(250 + count_frame, 200 - CNGui::ease(CNGui::trigonometry::out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(450 + count_frame, 200 - CNGui::ease(CNGui::trigonometry::in_out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(650 + count_frame, 200 - CNGui::ease(CNGui::trigonometry::out_in, clock_current, duration, 150));

            // Power of 2
            points.emplace_back(2).setPosition(950 + count_frame, 200 - CNGui::ease(CNGui::power::in<2>, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1150 + count_frame, 200 - CNGui::ease(CNGui::power::out<2>, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1350 + count_frame, 200 - CNGui::ease(CNGui::power::in_out<2>, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1550 + count_frame, 200 - CNGui::ease(CNGui::power::out_in<2>, clock_current, duration, 150));

            // Root
            points.emplace_back(2).setPosition(50 + count_frame, 400 - CNGui::ease(CNGui::root::in, clock_current, duration, 150));
            points.emplace_back(2).setPosition(250 + count_frame, 400 - CNGui::ease(CNGui::root::out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(450 + count_frame, 400 - CNGui::ease(CNGui::root::in_out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(650 + count_frame, 400 - CNGui::ease(CNGui::root::out_in, clock_current, duration, 150));

            // Exponential
            points.emplace_back(2).setPosition(950 + count_frame, 400 - CNGui::ease(CNGui::exponential::in, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1150 + count_frame, 400 - CNGui::ease(CNGui::exponential::out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1350 + count_frame, 400 - CNGui::ease(CNGui::exponential::in_out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1550 + count_frame, 400 - CNGui::ease(CNGui::exponential::out_in, clock_current, duration, 150));

            // Back
            points.emplace_back(2).setPosition(50 + count_frame, 600 - CNGui::ease(CNGui::drop::in<10>, clock_current, duration, 150));
            points.emplace_back(2).setPosition(250 + count_frame, 600 - CNGui::ease(CNGui::drop::out<10>, clock_current, duration, 150));
            points.emplace_back(2).setPosition(450 + count_frame, 600 - CNGui::ease(CNGui::drop::in_out<10>, clock_current, duration, 150));
            points.emplace_back(2).setPosition(650 + count_frame, 600 - CNGui::ease(CNGui::drop::out_in<10>, clock_current, duration, 150));

            // Elastic
            points.emplace_back(2).setPosition(950 + count_frame, 600 - CNGui::ease(CNGui::elastic::in, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1150 + count_frame, 600 - CNGui::ease(CNGui::elastic::out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1350 + count_frame, 600 - CNGui::ease(CNGui::elastic::in_out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(1550 + count_frame, 600 - CNGui::ease(CNGui::elastic::out_in, clock_current, duration, 150));

            // Drop
            points.emplace_back(2).setPosition(50 + count_frame, 800 - CNGui::ease(CNGui::bounce::in, clock_current, duration, 150));
            points.emplace_back(2).setPosition(250 + count_frame, 800 - CNGui::ease(CNGui::bounce::out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(450 + count_frame, 800 - CNGui::ease(CNGui::bounce::in_out, clock_current, duration, 150));
            points.emplace_back(2).setPosition(650 + count_frame, 800 - CNGui::ease(CNGui::bounce::out_in, clock_current, duration, 150));

            count_frame += 2;
        }

        window.clear();

        for(const auto& point: points)
        {
            window.draw(point);
        }

        window.display();
    }

    return 0;
}
