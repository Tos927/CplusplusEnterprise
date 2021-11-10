
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"



int main()
{
    //Preparation variable et autre pour le vaisseau
    Ship ship;
    float angle = 0;
    float vitesse = 0;
    InitializeShip(ship);

    std::vector<Planet> level;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise");    // WIDTH et HEIGHT sont des variable constante présent dans "GeneratorLevel.h"
    window.setVerticalSyncEnabled(true);  // Frame rate de l'écran

    sf::Clock clock;

    while (window.isOpen()) {

        // Input
        sf::Event event;
        while (window.pollEvent(event)) 
            {
                switch(event.type)
                {
				case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        
                    }
                    break;

                default:
                    break;
                }
            }


            // Logique
            sf::Time elapsedTime = clock.restart();
            ShipMovement(ship, elapsedTime.asSeconds(), angle, vitesse);
            if (IsOutOfScreen(ship.ship.getPosition(), 10.0f))
            {
                level = NewLevel(1, 5, 2, 20, 5);
            }
       
            // Rendu
            window.clear();

            window.draw(ship.ship);
            window.draw(ship.weapon);
            window.draw(ship.react1);
            window.draw(ship.react2);

            for (Planet p : level) {
                window.draw(p.pShape);
            }

            // Whatever I want to draw goes here
            window.display();
        
    }
}
