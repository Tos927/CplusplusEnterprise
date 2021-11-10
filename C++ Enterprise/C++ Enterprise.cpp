
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
    std::vector<Bullets> allBullets;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise");    // WIDTH et HEIGHT sont des variable constante pr�sent dans "GeneratorLevel.h"
    window.setVerticalSyncEnabled(true);  // Frame rate de l'�cran

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
                        CreateBullet(allBullets, 300.0f, angle, ship);
                    }
                    break;

                default:
                    break;
                }
            }


            // Logique
            sf::Time elapsedTime = clock.restart();
            ShipMovement(ship, elapsedTime.asSeconds(), angle, vitesse);
            ActualisationProps(level, allBullets);
            if (IsOutOfScreen(ship.ship.getPosition(), 10.0f))
            {
                allBullets.clear();
                ResetToCenter(ship);
                level = NewLevel(5, 20, 20, 2, 50);
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

            for (Bullets& bul : allBullets) 
            {
                MouvBullet(bul, elapsedTime.asSeconds());
                window.draw(bul.bullet);
            }

            // Whatever I want to draw goes here
            window.display();
        
    }
}
