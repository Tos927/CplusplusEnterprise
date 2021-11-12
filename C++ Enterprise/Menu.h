#pragma once

struct TextEquipInfoStruct
{
    sf::Text name;

    sf::RectangleShape background;

    int level = 1;
    sf::Text textLevel;
    sf::RectangleShape levelBg;

    sf::Text nameRessource;
    sf::RectangleShape ressourcesBg;
    int ownRessource = 150;
    int neededRessources = 25;
};

struct TextEquipInfoStruct Equip(std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf);

sf::RectangleShape Menu();

sf::RectangleShape ShipInfo();

sf::Text TextShipInfo(sf::Font& arialttf);





