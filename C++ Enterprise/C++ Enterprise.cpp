
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Enterprise");
    window.setVerticalSyncEnabled(true);  // Frame rate de l'écran

    sf::Clock clock;

    while (window.isOpen()) {

        // Input
        sf::Event event;
        while (window.pollEvent(event)) {
            {
                switch(event.type)
                {
				case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
                }
            }

            // Logique
            sf::Time elapsedTime = clock.restart();

            // Rendu
            window.clear();

            // Whatever I want to draw goes here
            window.display();
        }
    }
}
