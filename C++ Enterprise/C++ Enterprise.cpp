
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "AppPath.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Enterprise");
    window.setVerticalSyncEnabled(true);  // Frame rate de l'écran

    bool displayMenu = false;
    sf::RectangleShape menu = Menu();
    sf::RectangleShape shipInfo = ShipInfo();

    sf::Font arialttf = ArialFont();
    sf::Text arialText = TextShipInfo(arialttf);

    // ---------------------
    bool displayZone = false;
    sf::RectangleShape zone(sf::Vector2f(400, 100));
    sf::RectangleShape zone2(sf::Vector2f(400, 100));
    zone2.setPosition(0, 200);
    zone.setFillColor(sf::Color::White);
    // ---------------------

    sf::Vector2f posbackG = sf::Vector2f(120, 260);

    int pRight = 290;
    int pTop = 90;
    int margin = 3;

    TextEquipInfoStruct equip1 = Equip("Equip1", posbackG + sf::Vector2f(margin, margin), posbackG, arialttf);

    TextEquipInfoStruct equip2 = Equip("Equip2", posbackG + sf::Vector2f(pRight + margin, margin), posbackG + sf::Vector2f(pRight, 0), arialttf);

    TextEquipInfoStruct equip3 = Equip("Equip3", posbackG + sf::Vector2f(margin, pTop + margin), posbackG + sf::Vector2f(0, pTop), arialttf);

    TextEquipInfoStruct equip4 = Equip("Equip4", posbackG + sf::Vector2f(pRight + margin, pTop + margin), posbackG + sf::Vector2f(pRight, pTop), arialttf);

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
                    if (event.key.code == sf::Keyboard::E)
                    {
                        displayZone = !displayZone;
                    }
                    if (event.key.code == sf::Keyboard::I && equip1.ownRessource > equip1.neededRessources)
                    {
                        equip1.ownRessource -= equip1.neededRessources;
                        equip1.level++;
                        equip1.textLevel.setString("LvL" + std::to_string(equip1.level));
                        std::cout << equip1.level << std::endl;
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
            }

            if (displayZone)
            {
                window.draw(zone);
                window.draw(zone2);
            }

            

            window.display();
        }
    }
}
