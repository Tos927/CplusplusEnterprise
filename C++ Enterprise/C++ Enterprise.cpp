
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Menu.h"
#include "AppPath.h"
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "EnemiesBehaviour.h"
#include "Particules.h"

float oneSecondElapsed = 0;

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

    // ------------------------------------ Start - Initialization Menu  ------------------------------------ //

    bool displayMenu = false;
    bool displayTitle = true;

    // Setup fonts
    sf::Font aAtmospheric_ttf = SetupAnyFont("aAtmospheric.ttf");
    sf::Font barcadettf = SetupAnyFont("barcade.ttf");

    sf::Text barcadeText = SetUpText("(C++Enterprise)", barcadettf, 80, sf::Color::White, /*pos*/sf::Vector2f(WIDTH / 2, HEIGHT / 5));
    SetOriginText(barcadeText);

    // Initialization all background menu
    sf::RectangleShape menu = Menu(sf::Vector2f(WIDTH * 0.50, HEIGHT * 0.70), sf::Color::Color(0, 0, 53), sf::Vector2f(WIDTH * 0.50, HEIGHT * 0.50));
    sf::RectangleShape menu2 = Menu(sf::Vector2f(WIDTH * 0.50625, HEIGHT * 0.7125), sf::Color::White, sf::Vector2f(WIDTH * 0.50, HEIGHT * 0.50));
    menu2.setOutlineThickness(7);
    menu2.setOutlineColor(sf::Color::Color(54, 54, 54));

    // Background information of the ship 
    sf::RectangleShape shipInfo = SetupBackground(sf::Vector2f(WIDTH * 0.25, HEIGHT * 0.09), sf::Color::Color(240, 240, 240), sf::Vector2f(WIDTH * 0.27, HEIGHT * 0.18));
    shipInfo.setOutlineThickness(3);
    shipInfo.setOutlineColor(sf::Color::Color(54, 54, 54));

    InfoShip infoShip;

    // Position of the first background equip which determines the position of the others later 
    sf::Vector2f posbackG = sf::Vector2f(WIDTH * 0.27, HEIGHT * 0.56);

    // Need to be 2% away based on the width of the Equip (might change)
    int pRight = WIDTH * 0.24;
    int pTop = WIDTH * 0.08;
    // margin for the equip text
    int margin = 3;

    EquipStruct equip1 = Equip(1, "E", "Deflector Shield", posbackG + sf::Vector2f(margin, margin), posbackG, aAtmospheric_ttf, 15, "Energy shield that protects spacecraft\nfrom laser fire, in-flight projectiles and\naccidental space debris interaction.");
    EquipStruct equip2 = Equip(2, "R", "Photon Torpedo", posbackG + sf::Vector2f(pRight + margin, margin), posbackG + sf::Vector2f(pRight, 0), aAtmospheric_ttf, 20, "Improvement of the technology contained in\nthe cannons in order to have a firepower\nthat can cause massive damage to the enemy\nstructures.");
    EquipStruct equip3 = Equip(3, "T", "Artillery", posbackG + sf::Vector2f(margin, pTop + margin), posbackG + sf::Vector2f(0, pTop), aAtmospheric_ttf, 25, "The artillery's upgrade increases the power\nof the ship's cannons, thus increasing the\nspeed at which the projectiles advance\nthrough space.");
    EquipStruct equip4 = Equip(4, "Y", "Crew", posbackG + sf::Vector2f(pRight + margin, pTop + margin), posbackG + sf::Vector2f(pRight, pTop), aAtmospheric_ttf, 1, "Upgrading your ship's crew increases the\nfirepower of your ship as well as the number\nof resources you can harvest and other\nbonuses depending on the level.");
    
    RessourcesStorage storage = Storage(aAtmospheric_ttf);

    // ------------------------------------ End - Initialization Menu  ------------------------------------ //

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

                    // ------------------------------------ Start - Input Menu  ------------------------------------ //

                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        displayMenu = !displayMenu;
                    }
                    // Increase the Life of the Ship 
                    if (event.key.code == sf::Keyboard::E && storage.ownResource >= equip1.neededResources && displayMenu)
                    {
                        UpdateEquipOnLevelUp(equip1, storage, infoShip, ship);
                    }
                    // Increase the ATK of the Ship 
                    if (event.key.code == sf::Keyboard::R && storage.ownResource >= equip2.neededResources && displayMenu)
                    {
                        UpdateEquipOnLevelUp(equip2, storage, infoShip, ship);
                    }
                    // Increase the Bullet Speed of the Ship's bullet
                    if (event.key.code == sf::Keyboard::T && storage.ownResource >= equip3.neededResources && displayMenu)
                    {
                        UpdateEquipOnLevelUp(equip3, storage, infoShip, ship);
                    }
                    // Does many things
                    if (event.key.code == sf::Keyboard::Y && storage.ownResource >= equip4.neededResources && displayMenu)
                    {
                        UpdateEquipOnLevelUp(equip4, storage, infoShip, ship);
                    }

                    // ------------------------------------ End - Input Menu  ------------------------------------ //

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

            // Logique
            sf::Time elapsedTime = clock.restart();

            // ------------------------------------ Start - Dynamic/Update Menu Item ------------------------------------ //

            // Change the current level of the ship according to the average of the Equips 
            infoShip.shipLevel = (equip1.level + equip2.level + equip3.level + equip4.level) / 4;

            // Update ship information
            sf::Text InfoShipTitle = SetUpText("Ship Information : Level " + std::to_string(infoShip.shipLevel), aAtmospheric_ttf, 20, sf::Color::Black, /*pos*/sf::Vector2f(WIDTH * 0.275, HEIGHT * 0.185));

            sf::Text InfoShipValue = SetUpText(infoShip.atkString + std::to_string(infoShip.atkPoints) +
                infoShip.lifeString + std::to_string(infoShip.lifePoints) + infoShip.bspeedString + std::to_string((int)infoShip.bspeedPoints),
                aAtmospheric_ttf, 15, sf::Color::Black, /*pos*/sf::Vector2f(WIDTH * 0.275, HEIGHT * 0.235));

            UpdateStorage(storage);

            UpdateTextLevel(equip1, posbackG, " HP", storage);
            UpdateTextLevel(equip2, posbackG + sf::Vector2f(pRight, 0), " Attack", storage);
            UpdateTextLevel(equip3, posbackG + sf::Vector2f(0, pTop), " Bullet Speed", storage);
            UpdateTextLevel(equip4, posbackG + sf::Vector2f(pRight, pTop), " Attack", storage);

            // Duplicate the storage after updating for the In-Game Storage
            RessourcesStorage storageInGame = storage;
            UpdateStorageInGame(storageInGame);

            // ------------------------------------ End - Dynamic/Update Menu Item ------------------------------------ //
            

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
                window.draw(menu2);
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

                // Draw the menu storage
                DrawOneStorage(storage, window);
            }

            else
            {
                // Draw the In-Game storage
                DrawOneStorage(storageInGame, window);

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