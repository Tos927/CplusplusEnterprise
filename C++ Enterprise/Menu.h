#pragma once

struct TextEquipInfoStruct
{
    sf::Text name;

    sf::RectangleShape background;

    /*char nameEquip;
    int charaSize;
    char setFillColor = ("sf::Color::Blue");
    Vector
        arialText.setString("Armor");
    arialText.setCharacterSize(25);
    arialText.setFillColor(sf::Color::Blue);
    arialText.setPosition(125, 170);*/
};

struct TextEquipInfoStruct Equip(std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf);

sf::RectangleShape Menu();

sf::RectangleShape ShipInfo();

sf::Text TextShipInfo(sf::Font& arialttf);





