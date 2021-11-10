#include <iostream>
#include <SFML/Graphics.hpp>
#include "ShipBehaviour.h"

int main()
{
    //Preparation variable et autre pour le vaisseau
    Ship ship;
    float angle = 0;
    float vitesse = 0;
    InitializeShip(ship);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "C++ Enterprise");
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    
    while (window.isOpen()) {
        // Inputs
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            // Process any input event here
            switch (event.type)
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
        ShipMovement(ship, elapsedTime.asSeconds(), angle, vitesse);
        if (IsOutOfScreen(ship.ship.getPosition(), 10.0f))
        {
            std::cout << "Touché" << std::endl;
        }

        // Rendu
        window.clear();

        window.draw(ship.ship);
        window.draw(ship.weapon);
        window.draw(ship.react1);
        window.draw(ship.react2);

        window.display();
    }
}