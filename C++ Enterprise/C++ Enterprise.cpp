
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "AppPath.h"
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "EnemiesBehaviour.h"
#include "Particules.h"


int main()
{
    // initialisation aléatoire
    srand(time(NULL));

    //Preparation variable et autre pour le vaisseau
    Ship ship;
    float angle = 0;
    float vitesse = 0;
    InitializeShip(ship);

    // object de la scène
    std::vector<Planet> level;
    std::vector<Bullets> allBullets;
    
    std::vector<Enemy> allEnemies;
    std::map<int, Torpedo> enemyTorpedo;

    std::vector<Explosion> allExplosion;

    // initialisation windows
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise");    // WIDTH et HEIGHT sont des variable constante présent dans "GeneratorLevel.h"
    window.setVerticalSyncEnabled(true);  // Frame rate de l'écran

    bool displayMenu = false;

    sf::RectangleShape menu = Menu();
    // Fond des informations du ship
    sf::RectangleShape shipInfo = SetupBackground(sf::Vector2f(380, 70), sf::Color::Color(240, 240, 240), sf::Vector2f(120, 170));

    InfoShip infoShip;

    sf::Font arialttf = ArialFont();

    //sf::Text arialText = SetUpText("Infos : Lvl 1 / Hp : 150 / ATK : 20", arialttf, 25, sf::Color::Black, /*pos*/sf::Vector2f(125, 170));

    sf::Vector2f posbackG = sf::Vector2f(120, 260);

    int pRight = 290;
    int pTop = 90;
    int margin = 3;

    EquipStruct equip1 = Equip("E", "Deflector Shield", posbackG + sf::Vector2f(margin, margin), posbackG, arialttf);
    EquipStruct equip2 = Equip("R", "Phaser Canon", posbackG + sf::Vector2f(pRight + margin, margin), posbackG + sf::Vector2f(pRight, 0), arialttf);
    EquipStruct equip3 = Equip("T", "Artillery", posbackG + sf::Vector2f(margin, pTop + margin), posbackG + sf::Vector2f(0, pTop), arialttf);
    EquipStruct equip4 = Equip("Y", "Crew", posbackG + sf::Vector2f(pRight + margin, pTop + margin), posbackG + sf::Vector2f(pRight, pTop), arialttf);
    
    RessourcesStorage storage = Storage(arialttf);

    sf::Clock clock;

    while (window.isOpen()) {

        // Input
        sf::Event event;
        while (window.pollEvent(event)) 
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        displayMenu = !displayMenu;
                    }
                    // Life
                    if (event.key.code == sf::Keyboard::E && storage.ownResource >= equip1.neededResources && displayMenu)
                    {
                        storage.ownResource -= equip1.neededResources;
                        equip1.neededResources = equip1.neededResources + (equip1.neededResources / 2);
                        equip1.level++;
                        infoShip.lifePoints += 15;

                        std::cout << equip1.level << std::endl;
                    }
                    // ATK
                    if (event.key.code == sf::Keyboard::R && storage.ownResource >= equip2.neededResources && displayMenu)
                    {
                        storage.ownResource -= equip2.neededResources;
                        equip2.neededResources = equip2.neededResources + (equip2.neededResources / 2);
                        equip2.level++;
                        infoShip.atkPoints += 20;

                        std::cout << equip2.level << std::endl;
                    }
                    // Bullet Speed
                    if (event.key.code == sf::Keyboard::T && storage.ownResource >= equip3.neededResources && displayMenu)
                    {
                        storage.ownResource -= equip3.neededResources;
                        equip3.neededResources = equip3.neededResources + (equip3.neededResources / 2);
                        equip3.level++;
                        infoShip.bspeedPoints += 25;

                        std::cout << equip3.level << std::endl;
                    }
                    // Complicated
                    if (event.key.code == sf::Keyboard::Y && storage.ownResource >= equip4.neededResources && displayMenu)
                    {
                        storage.ownResource -= equip4.neededResources;
                        equip4.neededResources = equip4.neededResources + (equip4.neededResources / 2);
                        equip4.level++;
                        infoShip.lifePoints += 1;

                        std::cout << equip4.level << std::endl;
                    }

                    if (event.key.code == sf::Keyboard::Space)
                    {
                        CreateBullet(allBullets, infoShip, angle, ship);
                    }
                    if (event.key.code ==sf::Keyboard::G)
                    {
                        //CreatNewEnemy(allEnemies, { 500, 500}, 0);
                        CreatNewEnemy(allEnemies, { 600, 500 }, 1);
                        CreatNewEnemy(allEnemies, { 700, 500 }, 2);
                        CreatNewEnemy(allEnemies, { 800, 500 }, 3);
                    }
                    break;
                default:
                    break;
                }
        }

            // Element du menu qui sont dynamique

            infoShip.shipLevel = (equip1.level + equip2.level + equip3.level + equip4.level) / 4;

            sf::Text InfoShipValue = SetUpText(infoShip.atkString + std::to_string(infoShip.atkPoints) +
                infoShip.lifeString + std::to_string(infoShip.lifePoints) + infoShip.bspeedString + std::to_string((int)infoShip.bspeedPoints),
                arialttf, 20, sf::Color::Black, /*pos*/sf::Vector2f(125, 210));

            sf::Text InfoShipTitle = SetUpText("Ship Information : Level " + std::to_string(infoShip.shipLevel), arialttf, 25, sf::Color::Black, /*pos*/sf::Vector2f(125, 170));

            storage.nameResource.setString(storage.resource + std::to_string(storage.ownResource));

            equip1.textLevel.setString("LvL" + std::to_string(equip1.level));
            equip1.neededResourcesText.setString("Needed resources : " + std::to_string(equip1.neededResources));

            equip2.textLevel.setString("LvL" + std::to_string(equip2.level));
            equip2.neededResourcesText.setString("Needed resources : " + std::to_string(equip2.neededResources));

            equip3.textLevel.setString("LvL" + std::to_string(equip3.level));
            equip3.neededResourcesText.setString("Needed resources : " + std::to_string(equip3.neededResources));

            equip4.textLevel.setString("LvL" + std::to_string(equip4.level));
            equip4.neededResourcesText.setString("Needed resources : " + std::to_string(equip4.neededResources));

            // Logique
            sf::Time elapsedTime = clock.restart();

            ShipMovement(ship, elapsedTime.asSeconds(), angle, vitesse);
            ActualisationProps(level, allBullets, storage);
            if (IsOutOfScreen(ship.ship.getPosition(), 10.0f))
            {
                allBullets.clear();
                ResetToCenter(ship);
                level = NewLevel(3, 10, 20, 20, 50);
            }

            // Rendu
            window.clear();



            // Whatever I want to draw goes here 
            if (displayMenu)
            {

                // Draw the Menu background
                window.draw(menu);

                // Draw Ship Info
                window.draw(shipInfo);
                window.draw(InfoShipTitle);
                window.draw(InfoShipValue);

                // Draw the different Equip struct
                window.draw(equip1.background);
                window.draw(equip1.name);
                window.draw(equip1.levelBg);
                window.draw(equip1.textLevel);
                window.draw(equip1.neededResourcesText);
                window.draw(equip1.keyText);

                window.draw(equip2.background);
                window.draw(equip2.name);
                window.draw(equip2.levelBg);
                window.draw(equip2.textLevel);
                window.draw(equip2.neededResourcesText);
                window.draw(equip2.keyText);

                window.draw(equip3.background);
                window.draw(equip3.name);
                window.draw(equip3.levelBg);
                window.draw(equip3.textLevel);
                window.draw(equip3.neededResourcesText);
                window.draw(equip3.keyText);

                window.draw(equip4.background);
                window.draw(equip4.name);
                window.draw(equip4.levelBg);
                window.draw(equip4.textLevel);
                window.draw(equip4.neededResourcesText);
                window.draw(equip4.keyText);

                // Draw the storage
                window.draw(storage.resourcesBg);
                window.draw(storage.storage);
                window.draw(storage.nameResource);

            }

            else
            {
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

                std::map<const int, Torpedo>::iterator it = enemyTorpedo.begin();
                while (it != enemyTorpedo.end()) {
                    MoveToPoint(it->second.shap, ship.ship.getPosition(), it->second.speed, true, elapsedTime.asSeconds());
                    window.draw(it->second.shap);

                    // Actualisation de la torpille - si il est en contacte avec le vaisseau ou par un tir
                    if (CollideWithShip(ship, it->second.shap) || CollideWithFrendlyBullet(allBullets, it->second.shap, true)) {
                        it = enemyTorpedo.erase(it);
                    }
                    else {
                        it++;
                    }
                }

                std::vector<Enemy>::iterator enemyIt = allEnemies.begin();
                while (enemyIt != allEnemies.end()) {
                    window.draw((*enemyIt).shape);
                    switch ((*enemyIt).type)
                    {
                        case 0: {
                            break;
                        }
                        case 1: {
                            enemyIt = StratHeavyMove(enemyIt, allEnemies, allBullets, ship.ship.getPosition(), elapsedTime.asSeconds());
                            break;
                        }
                        case 2: {
                            enemyIt = StratBomberMove(enemyIt, allEnemies, allBullets, ship, infoShip,  elapsedTime.asSeconds());
                            break;
                        }
                        case 3: {
                            enemyIt = StratTorpedoLuncherMove(enemyIt, allEnemies, enemyTorpedo, allBullets, ship.ship.getPosition(), elapsedTime.asSeconds());
                            break;
                        }
                    }

                    if (enemyIt != allEnemies.end()) {
                        enemyIt++;
                    }
                }

                /*auto exploIt = allExplosion.begin();
                while (exploIt != allExplosion.end())
                {
                    window.draw(exploIt->explosionShape);
                    if (exploIt != allExplosion.end())
                    {
                        ExpendingExplosion(exploIt, allExplosion, elapsedTime.asSeconds());
                    }
                    else
                    {
                        exploIt++;
                    }
                }*/
            }

            window.display();
    }
}