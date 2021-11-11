
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "EnemiesBehaviour.h"



int main()
{
    // initialisation aléatoire
    srand(time(NULL));

    //Preparation variable et autre pour le vaisseau
    Ship ship;
    float angle = 0;
    float vitesse = 0;
    InitializeShip(ship);

    std::vector<Planet> level;
    std::vector<Enemy> allEnemies;

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
                        CreatNewEnemy(allEnemies, { 500,500 }, 2);
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
                ResetToCenter(ship);
                level = NewLevel(7, 7, 50, 50, 10);
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

            for (Enemy& enemy : allEnemies) {
                switch (enemy.type)
                {
                    case 0: {
                        break;
                    }
                    case 1: {
                        break;
                    }
                    case 2: {
                        break;
                    }
                    case 3: {
                        break;
                    }
                }
                window.draw(enemy.shape);
            }

            // Whatever I want to draw goes here
            window.display();
        
    }
}
