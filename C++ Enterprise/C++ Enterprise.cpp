
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "EnemiesBehaviour.h"



int main()
{
    // initialisation al�atoire
    srand(time(NULL));

    //Preparation variable et autre pour le vaisseau
    Ship ship;
    float angle = 0;
    float vitesse = 0;
    InitializeShip(ship);

    std::vector<Planet> level;
    std::vector<Enemy> allEnemies;
    std::map<int, Torpedo> enemyTorpedo;

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
                        //CreatNewEnemy(allEnemies, { 500, 500}, 0);
                        //CreatNewEnemy(allEnemies, { 600, 500 }, 1);
                        //CreatNewEnemy(allEnemies, { 700, 500 }, 2);
                        CreatNewEnemy(allEnemies, { 800, 500 }, 3);
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

            for (const Planet& p : level) {
                window.draw(p.pShape);
            }


            std::map<const int, Torpedo>::iterator it = enemyTorpedo.begin();
            while (it != enemyTorpedo.end()) {
                MoveToPoint(it->second.shap, ship.ship.getPosition(), it->second.speed, true, elapsedTime.asSeconds());
                window.draw(it->second.shap);
 
                // Actualisation de la torpille - si il est en contacte avec le vaisseau
                if (CollideWithShip(ship, it->second.shap)) {
                    it = enemyTorpedo.erase(it);
                    std::cout << "touche" << std::endl;
                }
                else {
                    it++;
                }
            }


            std::vector<Enemy>::iterator enemyIt = allEnemies.begin();
            while ( enemyIt != allEnemies.end()) {
                window.draw((*enemyIt).shape);
                switch ((*enemyIt).type)
                {
                    case 0: {
                        break;
                    }
                    case 1: {
                        StratHeavyMove(enemyIt, ship.ship.getPosition(), elapsedTime.asSeconds());
                        break;
                    }
                    case 2: {
                        enemyIt = StratBomberMove(enemyIt, allEnemies, ship, elapsedTime.asSeconds());
                        break;
                    }
                    case 3: {
                        StratTorpedoLuncherMove(enemyIt, enemyTorpedo, ship.ship.getPosition(), elapsedTime.asSeconds());
                        break;
                    }
                }

                if (enemyIt != allEnemies.end()) {
                    enemyIt++;
                }
            }

            // Whatever I want to draw goes here
            window.display();
        
    }
}
