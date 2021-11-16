
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise", sf::Style::Fullscreen);    // WIDTH et HEIGHT sont des variable constante présent dans "GeneratorLevel.h"
    window.setVerticalSyncEnabled(true);  // Frame rate de l'écran

    bool displayMenu = false;


    sf::RectangleShape menu = Menu();
    // Fond des informations du ship
    sf::RectangleShape shipInfo = SetupBackground(sf::Vector2f(WIDTH * 0.25, HEIGHT * 0.09), sf::Color::Color(240, 240, 240), sf::Vector2f(WIDTH * 0.27, HEIGHT * 0.18));

    InfoShip infoShip;

    sf::Font arialttf = SetupAnyFont("arial.ttf");
    sf::Font barcadettf = SetupAnyFont("barcade.ttf");

    sf::Text barcadeText = SetUpText("(C++Enterprise)", barcadettf, 80, sf::Color::White, /*pos*/sf::Vector2f(WIDTH/2, HEIGHT/5));
    barcadeText.setOrigin((barcadeText.getGlobalBounds().width / 2), (barcadeText.getGlobalBounds().height / 2));

    bool displayTitle = true;

    //sf::Text arialText = SetUpText("Infos : Lvl 1 / Hp : 150 / ATK : 20", arialttf, 25, sf::Color::Black, /*pos*/sf::Vector2f(125, 170));

    sf::Vector2f posbackG = sf::Vector2f(WIDTH * 0.27, HEIGHT * 0.56);

    // Need to be 2% away based on the width of the Equip (might change)
    int pRight = WIDTH * 0.24;
    int pTop = WIDTH * 0.08;
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

                        int lifePointsBonus = 15;
                        infoShip.lifePoints += lifePointsBonus, equip1.currentStatsBonus += lifePointsBonus;

                        ship.currentLife = infoShip.lifePoints;

                        std::cout << equip1.level << std::endl;

                        //UpdateEquipOnLevelUp(equip1, storage, infoShip, ship);
                    }
                    // ATK
                    if (event.key.code == sf::Keyboard::R && storage.ownResource >= equip2.neededResources && displayMenu)
                    {
                        storage.ownResource -= equip2.neededResources;
                        equip2.neededResources = equip2.neededResources + (equip2.neededResources / 2);
                        equip2.level++;

                        int atkPointsBonus = 20;
                        infoShip.atkPoints += atkPointsBonus, equip2.currentStatsBonus += atkPointsBonus;

                        std::cout << equip2.level << std::endl;
                    }
                    // Bullet Speed
                    if (event.key.code == sf::Keyboard::T && storage.ownResource >= equip3.neededResources && displayMenu)
                    {
                        storage.ownResource -= equip3.neededResources;
                        equip3.neededResources = equip3.neededResources + (equip3.neededResources / 2);
                        equip3.level++;

                        int atkPointsBonus = 25;
                        infoShip.bspeedPoints += atkPointsBonus, equip3.currentStatsBonus += atkPointsBonus;

                        std::cout << equip3.level << std::endl;
                    }
                    // Complicated
                    if (event.key.code == sf::Keyboard::Y && storage.ownResource >= equip4.neededResources && displayMenu)
                    {
                        storage.ownResource -= equip4.neededResources;
                        equip4.neededResources = equip4.neededResources + (equip4.neededResources / 2);
                        equip4.level++;
                        infoShip.lifePoints += 1, equip4.currentStatsBonus += 1;

                        std::cout << equip4.level << std::endl;
                    }

                    if (event.key.code == sf::Keyboard::Space)
                    {
                        CreateBullet(allBullets, infoShip, angle, ship);
                    }
                    if (event.key.code ==sf::Keyboard::G)
                    {
                        //CreatNewEnemy(allEnemies, { 500, 500}, 0);
                        //CreatNewEnemy(allEnemies, { 600, 500 }, 1);
                        //CreatNewEnemy(allEnemies, { 700, 500 }, 2);
                        CreatNewEnemy(allEnemies, { 800, 500 }, 3);
                    }
                    if (event.key.code == sf::Keyboard::P)
                    {
                        window.close();
                        break;
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
                arialttf, 20, sf::Color::Black, /*pos*/sf::Vector2f(WIDTH * 0.275, HEIGHT * 0.235));

            sf::Text InfoShipTitle = SetUpText("Ship Information : Level " + std::to_string(infoShip.shipLevel), arialttf, 25, sf::Color::Black, /*pos*/sf::Vector2f(WIDTH * 0.275, HEIGHT * 0.185));

            storage.nameResource.setString(std::to_string(storage.ownResource));
            storage.nameResource.setPosition(sf::Vector2f(WIDTH * 0.675 - (WIDTH * 0.110 / 2) + (WIDTH * 0.110 / 2), HEIGHT * (0.18 + 0.06)));
            storage.nameResource.setOrigin((storage.nameResource.getGlobalBounds().width / 2), (storage.nameResource.getGlobalBounds().height / 2));

            UpdateTextLevel(equip1, posbackG, " HP");
            UpdateTextLevel(equip2, posbackG + sf::Vector2f(pRight, 0), " Attack");
            UpdateTextLevel(equip3, posbackG + sf::Vector2f(0, pTop), " Bullet Speed");
            UpdateTextLevel(equip4, posbackG + sf::Vector2f(pRight, pTop), " HP");

            // Logique
            sf::Time elapsedTime = clock.restart();


            ShipMovement(ship, elapsedTime.asSeconds(), angle, vitesse);
            ActualisationProps(level, allBullets, storage);
            if (IsOutOfScreen(ship.ship.getPosition(), 10.0f))
            {
                allBullets.clear();
                ResetToCenter(ship);
                level = NewLevel(3, 10, 20, 20, 50);
                displayTitle = false;
            }

            // Rendu
            window.clear();

            if (displayTitle)
            {
                window.draw(barcadeText);
            }
            

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
                DrawEquip(equip1, window);
                DrawEquip(equip2, window);
                DrawEquip(equip3, window);
                DrawEquip(equip4, window);

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
                while (enemyIt != allEnemies.end()) {
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