
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
    std::vector<Bullets> enemyBullets;

    std::vector<Explosion> allExplosion;

    // initialisation windows
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise");    // WIDTH et HEIGHT sont des variable constante présent dans "GeneratorLevel.h"
    window.setVerticalSyncEnabled(true);  // Frame rate de l'écran

    bool displayMenu = false;

    sf::RectangleShape menu = Menu();
    // Fond des informations du ship
    sf::RectangleShape shipInfo = SetupBackground(sf::Vector2f(380, 70), sf::Color::Color(240, 240, 240), sf::Vector2f(120, 170));

    InfoShip infoShip;

    sf::Font arialttf = SetupAnyFont("arial.ttf");
    sf::Font barcadettf = SetupAnyFont("barcade.ttf");

    sf::Text barcadeText = SetUpText("(C++Enterprise)", barcadettf, 80, sf::Color::White, /*pos*/sf::Vector2f(WIDTH / 2, HEIGHT / 5));

    bool displayTitle = true;

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
                    ship.currentLife = infoShip.lifePoints;

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
                    CreateBullet(allBullets, infoShip.bspeedPoints, infoShip.atkPoints,ship.ship, ship.ship.getRotation());
                }
                if (event.key.code == sf::Keyboard::G)
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


        //TODO//
        //bouger le code d'en dessous dans else pour pas que le vaisseau bouge dans le menu
        ShipMovement(ship, elapsedTime.asSeconds(), angle, vitesse);
        ActualisationProps(level, allBullets, storage);
        if (IsOutOfScreen(ship.ship.getPosition(), 10.0f))
        {
            allBullets.clear();
            ResetToCenter(ship);
            level = NewLevel(3, 10, 20, 20, 50);
            displayTitle = false;
            //TODO//
            //Créer une variable pour le nombre de ressoucres gagner par planete et enemies, et l'augmenter a chaque nouvel ecran
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
            // ------------ logique ------------ //

            
            // Déplacement des balles alliers
            for (Bullets& bul : allBullets)
            {
                MouvBullet(bul, elapsedTime.asSeconds());
            }

            std::vector<Bullets>::iterator enemyBulletIt = enemyBullets.begin();
            while (enemyBulletIt != enemyBullets.end())
            {
                MouvBullet((*enemyBulletIt), elapsedTime.asSeconds());
                if (CollideWithShip(ship, (*enemyBulletIt).bullet.getPosition(), 0) && ship.canTakeDamage) {
                    TakeDamage(ship, (*enemyBulletIt).damage);
                    enemyBulletIt = enemyBullets.erase(enemyBulletIt);
                }
                else {
                    enemyBulletIt++;
                }
            }
            
            std::vector<Planet>::iterator planetIt = level.begin();
            while (planetIt != level.end())
            {
                if (CollideWithShip(ship, (*planetIt).pShape.getPosition(), (*planetIt).radius) && ship.canTakeDamage) {
                    ship.canTakeDamage = false;
                    TakeDamage(ship, infoShip.lifePoints / 4);
                    planetIt = level.erase(planetIt);
                }
                else {
                    planetIt++;
                }
            }

            // Déplacement des Torpilles
            std::map<const int, Torpedo>::iterator it = enemyTorpedo.begin();
            while (it != enemyTorpedo.end()) {
                MoveToPoint(it->second.shap, ship.ship.getPosition(), it->second.speed, true, elapsedTime.asSeconds());

                // Actualisation de la torpille - si il est en contacte avec le vaisseau ou par un tir
                if (CollideWithShip(ship, it->second.shap.getPosition(), it->second.shap.getRadius())  && ship.canTakeDamage) {
                    infoShip.lifePoints -= it->second.damage;
                    TakeDamage(ship, it->second.damage);

                    it = enemyTorpedo.erase(it);
                    continue;

                }
                if (CollideWithFrendlyBullet(allBullets, it->second.shap, true)) {
                    infoShip.lifePoints -= it->second.damage;
                    it = enemyTorpedo.erase(it);
                    continue;
                }
                it++;
            }

            // déplacement des enemis
            std::vector<Enemy>::iterator enemyIt = allEnemies.begin();
            while (enemyIt != allEnemies.end()) {
                switch ((*enemyIt).type)
                {
                case 0: {
                    break;
                }
                case 1: {
                    enemyIt = StratHeavyMove(enemyIt, allEnemies, allBullets, ship, enemyBullets, ship.ship.getPosition(), storage, elapsedTime.asSeconds());
                    break;
                }
                case 2: {
                    enemyIt = StratBomberMove(enemyIt, allEnemies, allBullets, ship, infoShip, storage, elapsedTime.asSeconds());
                    break;
                }
                case 3: {
                    enemyIt = StratTorpedoLuncherMove(enemyIt, allEnemies, enemyTorpedo, allBullets, ship.ship.getPosition(), storage, elapsedTime.asSeconds());
                    break;
                }
                }

                if (enemyIt != allEnemies.end()) {
                    enemyIt++;
                }
            }
            
            if (!ship.canTakeDamage) {
                InvincibilityShip(ship, elapsedTime.asSeconds());
            }


            // ------------ Rendu ------------ //

            // Joueur
            DrawShip(ship, window);

            // Ennemis
            for (Enemy enemy : allEnemies) {
                window.draw(enemy.shape);
            }

            // Planètes
            for (Planet p : level) {
                window.draw(p.pShape);
            }

            // Balles alliers
            for (Bullets& bul : allBullets)
            {
                window.draw(bul.bullet);
            }

            for (Bullets& bul : enemyBullets)
            {
                window.draw(bul.bullet);
            }

            // Torpilles ennemis
            for (std::pair<const int, Torpedo> topedo : enemyTorpedo) {
                window.draw(topedo.second.shap);
            }
        }
        window.display();
    }
}