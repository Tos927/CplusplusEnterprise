#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Enterprise");
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {{
            // Process any input event here
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        sf::Time elapsedTime = clock.restart();
        window.clear();
        // Whatever I want to draw goes here
        window.display();
    }
}
