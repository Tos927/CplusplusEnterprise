
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GeneratorLevel.h"



int main()
{
    std::vector<Planet> level;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise");    // WIDTH et HEIGHT sont des variable constante présent dans "GeneratorLevel.h"
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

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        level = NewLevel(1, 5, 2, 20, 5);
                    }
                    break;

                default:
                    break;
                }
            }


            // Logique
            sf::Time elapsedTime = clock.restart();
       
            // Rendu
            window.clear();

            for (Planet p : level) {
                window.draw(p.pShape);
            }

            // Whatever I want to draw goes here
            window.display();
        }
    }
}
