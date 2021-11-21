
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "AppPath.h"
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "EnemiesBehaviour.h"
#include "Particules.h"
#include "ScoreBoard.h"
#include <algorithm>

int main()
{
    // Initialisation GameOver
    bool isLost = false;
    // initialisation aléatoire
    srand(time(NULL));

    //Preparation variable et autre pour le vaisseau
    Ship ship;
    Planet planet;
    float angle = 0;
    float vitesse = 0;
    int tableaux = -1;
    InitializeShip(ship);

    //Preparation au scoreboard et augmentation difficulté
    Points points;
    Torpedo torpedo;
    Enemy enemy;

    // object de la scène
    std::vector<Planet> level;
    std::vector<Bullets> allBullets;

    std::vector<Enemy> allEnemies;
    std::map<int, Torpedo> enemyTorpedo;
    std::vector<Bullets> enemyBullets;

    // effets
    std::vector<Explosion> allExplosion;
    std::vector<TrailParticule> allTrailParticules;

    // initialisation windows
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "C++ Enterprise", sf::Style::Fullscreen, settings);    // WIDTH et HEIGHT sont des variable constante présent dans "GeneratorLevel.h"
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
    sf::RectangleShape shipInfo = SetupBackground(sf::Vector2f(WIDTH * 0.24, HEIGHT * 0.12), sf::Color::Color(240, 240, 240), sf::Vector2f(WIDTH * 0.27, HEIGHT * 0.18));
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
    EquipStruct equip3 = Equip(3, "T", "Artillery", posbackG + sf::Vector2f(margin, pTop + margin), posbackG + sf::Vector2f(0, pTop), aAtmospheric_ttf, 1, "The artillery's upgrade increases the power\nof the ship's cannons, thus increasing the\nspeed at which the projectiles advance\nthrough space.");
    EquipStruct equip4 = Equip(4, "Y", "Thruster", posbackG + sf::Vector2f(pRight + margin, pTop + margin), posbackG + sf::Vector2f(pRight, pTop), aAtmospheric_ttf, 1, "Improved ship's thrusters improve your\nspeed of movement in space to cross the\ngalaxy faster");
    
    RessourcesStorage storage = Storage(aAtmospheric_ttf);

    // width and height of the LifeBar's RectangleShape
    int maxlifeWidth(WIDTH * 0.25);
    int maxLifeHeight(HEIGHT * 0.025);

    sf::RectangleShape lifeBar = SetupBackground(sf::Vector2f(maxlifeWidth, maxLifeHeight), sf::Color::Color(255, 45, 0), sf::Vector2f(WIDTH * 0.02, HEIGHT * 0.05));
    sf::RectangleShape lifeBarOutline = SetupBackground(sf::Vector2f(maxlifeWidth, maxLifeHeight), sf::Color::Transparent, sf::Vector2f(WIDTH * 0.02, HEIGHT * 0.05));
    lifeBarOutline.setOutlineColor(sf::Color::White);
    lifeBarOutline.setOutlineThickness(1);

    // Text life on the life bar 
    sf::Text lifeInGame = SetUpText(std::to_string(ship.currentLife) + "/" + std::to_string(infoShip.lifePoints), aAtmospheric_ttf, 15, sf::Color::White, sf::Vector2f(maxlifeWidth, maxLifeHeight) - sf::Vector2f(maxlifeWidth / 2, -32.5));
    
    // Text GameOver and Scoreboard
    sf::Text GameOverText = SetUpText("(GAME-OVER)", barcadettf, 100, sf::Color::Red, sf::Vector2f(WIDTH / 2, HEIGHT / 2));
    SetOriginText(GameOverText);
    sf::Text ToucheP = SetUpText("Appuyer sur P pour quitter", aAtmospheric_ttf, 50, sf::Color::White, sf::Vector2f(WIDTH / 2, HEIGHT / 3));
    SetOriginText(ToucheP);
    ToucheP.setOutlineColor(sf::Color::Black);
    ToucheP.setOutlineThickness(1);
    sf::Text ScoreBoardText = SetUpText("Score : " + std::to_string(points.totalPoints), aAtmospheric_ttf, 20, sf::Color::White, sf::Vector2f(WIDTH/2, HEIGHT * 0.05));
    SetOriginText(ScoreBoardText);
    ScoreBoardText.setOutlineColor(sf::Color::Black);
    ScoreBoardText.setOutlineThickness(1);


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

                if (event.key.code == sf::Keyboard::Escape && !isLost)
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
                if (event.key.code == sf::Keyboard::P)
                {
                    window.close();
                    break;
                }

                // ------------------------------------ End - Input Menu  ------------------------------------ //

                if (event.key.code == sf::Keyboard::Space)
                {
                    CreateBullet(allBullets, infoShip.bspeedPoints, infoShip.atkPoints,ship.ship, ship.ship.getRotation());
                }
                if (event.key.code == sf::Keyboard::G)
                {
                    //CreatNewEnemy(allEnemies, { 500, 500}, 0);
                    //CreatNewEnemy(allEnemies, { 600, 500 }, 1);
                    //CreatNewEnemy(allEnemies, { 700, 500 }, 2);
                    CreatNewEnemy(allEnemies, { 800, 500 }, 3);
                    //allExplosion.push_back(CreationExplosion(sf::Color::Yellow, sf::Vector2f(500, 500)));
                    //allTrailParticules.push_back(CreatParticuleTrail(sf::Vector2f(500, 500), 0));
                }
                break;
            default:
                break;
            }
        }

        // ------------------------------------ Start - Dynamic/Update Menu Item ------------------------------------ //

            // Change the current level of the ship according to the average of the Equips 
        infoShip.shipLevel = (equip1.level + equip2.level + equip3.level + equip4.level) / 4;

        // Update ship information
        sf::Text InfoShipTitle = SetUpText("Ship Information : Level " + std::to_string(infoShip.shipLevel), aAtmospheric_ttf, 20, sf::Color::Black, /*pos*/ sf::Vector2f(WIDTH * 0.275, HEIGHT * 0.185));

        sf::Text InfoShipValue = SetUpText(infoShip.atkString + std::to_string(infoShip.atkPoints) + "\n" +
            infoShip.lifeString + std::to_string(ship.currentLife) + "/" + std::to_string(infoShip.lifePoints) + "\n" + infoShip.bspeedString + std::to_string((int)infoShip.bspeedPoints)
            + "\n" + infoShip.shipSpeed + std::to_string((int)infoShip.speed),
            aAtmospheric_ttf, 13, sf::Color::Black, /*pos*/ sf::Vector2f(WIDTH * 0.275, HEIGHT * 0.235));

        UpdateStorage(storage);

        UpdateTextLevel(equip1, posbackG, " HP", storage);
        UpdateTextLevel(equip2, posbackG + sf::Vector2f(pRight, 0), " Attack", storage);
        UpdateTextLevel(equip3, posbackG + sf::Vector2f(0, pTop), " Bullet Speed", storage);
        UpdateTextLevel(equip4, posbackG + sf::Vector2f(pRight, pTop), " Ship Speed", storage);

        // Duplicate the storage after updating for the In-Game Storage
        RessourcesStorage storageInGame = storage;
        UpdateStorageInGame(storageInGame);

        UpdateLifeBar(ship, infoShip, lifeBar, maxlifeWidth, maxLifeHeight, lifeInGame);

        UpdateScoreBoard(ScoreBoardText, points);

        // ------------------------------------ End - Dynamic/Update Menu Item ------------------------------------ //
        // Logique
        sf::Time elapsedTime = clock.restart();
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
            isLost = !IsShipAlive(ship);

            if (!isLost) 
            {
                ShipMovement(ship, elapsedTime.asSeconds(), angle, vitesse, infoShip);
                ActualisationProps(level, allBullets, storage, tableaux, points.totalPoints, points.levelMultiplicator);
                if (IsOutOfScreen(ship.ship.getPosition(), 10.0f))
                {
                    allEnemies.clear();
                    enemyBullets.clear();
                    allBullets.clear();
                    enemyTorpedo.clear();
                    allTrailParticules.clear();
                    ResetToCenter(ship);
                    tableaux += 1;
                    if (tableaux % 5 == 0) // Augmentation de la difficulté au cours du jeu
                    {
                        planet.vie += 100;
                        torpedo.damage += 10;
                        enemy.damage += 10;
                        enemy.life += 50;
                    }
                    points.levelMultiplicator += tableaux;
                    level = NewLevel(3, 10, 40, 60, 80, 4, 0, 3, 0, 3, 0, allEnemies);
                    //level = NewLevel(3, 10, 40, 60, 80, (4+(points.levelMultiplicator/10)), 0, (3 + (points.levelMultiplicator / 10)), 0, (3 + (points.levelMultiplicator / 10)), 0, allEnemies);
                    displayTitle = false;
                }

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
                        TakeDamage(ship, (*enemyBulletIt).damage, tableaux);
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
                        TakeDamage(ship, infoShip.lifePoints / 4, 0);
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
                    CreatTrail(it, allTrailParticules, elapsedTime.asSeconds());

                    // Actualisation de la torpille - si il est en contacte avec le vaisseau ou par un tir
                    if (CollideWithShip(ship, it->second.shap.getPosition(), it->second.shap.getRadius()) && ship.canTakeDamage) {
                        TakeDamage(ship, it->second.damage, tableaux);
                        allExplosion.push_back(CreationExplosion(sf::Color::Yellow, it->second.shap.getPosition()));
                        it = enemyTorpedo.erase(it);
                        continue;

                    }
                    if (CollideWithFrendlyBullet(allBullets, it->second.shap, true)) {
                        allExplosion.push_back(CreationExplosion(sf::Color::Yellow, it->second.shap.getPosition()));
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
                            StratHeavyMove(enemyIt, allEnemies, allBullets, ship, infoShip, enemyBullets, ship.ship.getPosition(), storage, elapsedTime.asSeconds(), tableaux, points);
                            break;
                        }
                        case 2: {
                            StratBomberMove(enemyIt, allEnemies, allBullets, ship, infoShip, storage, elapsedTime.asSeconds(), tableaux, points);
                            break;
                        }
                        case 3: {
                            StratTorpedoLuncherMove(enemyIt, allEnemies, enemyTorpedo, infoShip, allBullets, ship.ship.getPosition(), storage, elapsedTime.asSeconds(), tableaux, points, ship);
                            break;
                        }
                    }

                    if (!enemyIt->isValid) {
                        allExplosion.push_back(CreationExplosion(sf::Color::Yellow, enemyIt->shape.getPosition()));
                        enemyIt = allEnemies.erase(enemyIt);
                    }
                    else {
                        enemyIt++;
                    }
                }

                std::vector<Explosion>::iterator explosionIt = allExplosion.begin();
                while (explosionIt != allExplosion.end()) {
                    ExpendingExplosion(explosionIt, elapsedTime.asSeconds());

                    if (!explosionIt->isValid) {
                        explosionIt = allExplosion.erase(explosionIt);
                    }
                    else {
                        explosionIt++;
                    }
                }

                std::vector<TrailParticule>::iterator trailIt = allTrailParticules.begin();
                while (trailIt != allTrailParticules.end()) {
                    UpdateTrail(trailIt, 100, elapsedTime.asSeconds());

                    if (!trailIt->isValid) {
                        trailIt = allTrailParticules.erase(trailIt);
                    }
                    else {
                        trailIt++;
                    }
                }

                if (!ship.canTakeDamage) {
                    InvincibilityShip(ship, elapsedTime.asSeconds());
                }
            }

            // ------------ Rendu ------------ //

            // Planètes
            for (Planet p : level) {
                window.draw(p.pShape);
            }

            for (Explosion explosion : allExplosion) {
                window.draw(explosion.explosionShape);
                window.draw(explosion.explosionShape2);
            }

            for (TrailParticule particule : allTrailParticules) {
                window.draw(particule.shape);
            }

            // Ennemis
            for (Enemy enemy : allEnemies) {
                window.draw(enemy.shape);
            }
            
            // Draw the In-Game storage
            DrawOneStorage(storageInGame, window);
            window.draw(lifeBar);
            window.draw(lifeBarOutline);
            window.draw(lifeInGame);
            window.draw(ScoreBoardText);

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

            // Joueur
            if (!isLost)
            {
                DrawShip(ship, window);
            }
            else
            {
                window.draw(GameOverText);
                window.draw(ToucheP);
            }

        }
        window.display();
    }
}