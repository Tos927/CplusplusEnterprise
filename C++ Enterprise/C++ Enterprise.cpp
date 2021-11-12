
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "AppPath.h"

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

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise");    // WIDTH et HEIGHT sont des variable constante présent dans "GeneratorLevel.h"
    window.setVerticalSyncEnabled(true);  // Frame rate de l'écran

    // ------------------- Menu -------------------- //
    bool displayMenu = false;
    sf::RectangleShape menu = Menu();
    // Fond des informations du ship
    sf::RectangleShape shipInfo = SetupBackground(sf::Vector2f(380, 30), sf::Color::Color(240, 240, 240), sf::Vector2f(120, 170));

    sf::Font arialttf = ArialFont();
    sf::Text arialText = SetUpText("Infos : Lvl 1 / Hp : 150 / ATK : 20", arialttf, 25, sf::Color::Black, /*pos*/sf::Vector2f(125, 170));

    sf::Vector2f posbackG = sf::Vector2f(120, 260);

    int pRight = 290;
    int pTop = 90;
    int margin = 3;

    EquipStruct equip1 = Equip("Equip1", posbackG + sf::Vector2f(margin, margin), posbackG, arialttf);

    EquipStruct equip2 = Equip("Equip2", posbackG + sf::Vector2f(pRight + margin, margin), posbackG + sf::Vector2f(pRight, 0), arialttf);

    EquipStruct equip3 = Equip("Equip3", posbackG + sf::Vector2f(margin, pTop + margin), posbackG + sf::Vector2f(0, pTop), arialttf);

    EquipStruct equip4 = Equip("Equip4", posbackG + sf::Vector2f(pRight + margin, pTop + margin), posbackG + sf::Vector2f(pRight, pTop), arialttf);

    RessourcesStorage storage = Storage(arialttf);

    // ------------------- Menu -------------------- //

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
                    if (event.key.code == sf::Keyboard::A)
                    {
                        displayMenu = !displayMenu;
                    }
                    if (event.key.code == sf::Keyboard::I && storage.ownResource >= equip1.neededResources)
                    {
                        storage.ownResource -= equip1.neededResources;
                        equip1.neededResources = equip1.neededResources + (equip1.neededResources / 2);
                        equip1.level++;
                        equip1.textLevel.setString("LvL" + std::to_string(equip1.level));
                        storage.nameResource.setString("Stone " + std::to_string(storage.ownResource));
                        equip1.neededResourcesText.setString("Needed resources : " + std::to_string(equip1.neededResources));
                        
                        std::cout << equip1.level << std::endl;
                    }
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
                level = NewLevel(7, 7, 50, 50, 10);
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
                window.draw(arialText);

                // Draw the different Equip struct
                window.draw(equip1.background);
                window.draw(equip1.name);
                window.draw(equip1.levelBg);
                window.draw(equip1.textLevel);
                window.draw(equip1.neededResourcesText);
                

                window.draw(equip2.background);
                window.draw(equip2.name);
                window.draw(equip2.levelBg);
                window.draw(equip2.textLevel);

                window.draw(equip3.background);
                window.draw(equip3.name);
                window.draw(equip3.levelBg);
                window.draw(equip3.textLevel);

                window.draw(equip4.background);
                window.draw(equip4.name);
                window.draw(equip4.levelBg);
                window.draw(equip4.textLevel);

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
            }

            window.display();
        }
    }
}
