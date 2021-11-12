#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "AppPath.h"

// Fond du Menu
sf::RectangleShape Menu()
{
	std::cout << "test" << std::endl;

    sf::RectangleShape menu (sf::Vector2f(600, 300));
    menu.setFillColor(sf::Color::Color(0, 0, 94));
    menu.setPosition(400, 300);
    menu.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);

    return menu;
}

// Fond des informations du ship
sf::RectangleShape ShipInfo()
{
    sf::RectangleShape menu(sf::Vector2f(380, 30));
    menu.setFillColor(sf::Color::Color(240, 240, 240));
    menu.setPosition(120, 170);

    return menu;
}

// Text des informations du ship
sf::Text TextShipInfo(sf::Font& arialttf)
{
    sf::Text arialText;
    arialText.setFont(arialttf);
    arialText.setString("Infos : Lvl 1 / Hp : 150 / ATK : 20");
    arialText.setCharacterSize(25);
    arialText.setFillColor(sf::Color::Black);
    arialText.setPosition(125, 170);

    return arialText;
}


struct TextEquipInfoStruct Equip(std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf)
{
    TextEquipInfoStruct equip;

    // Equip background and name text
    equip.name.setString(name);
    equip.name.setFont(arialttf);
    equip.name.setCharacterSize(15);
    equip.name.setFillColor(sf::Color::Black);
    equip.name.setPosition(posNameText); //125,170

    equip.background = sf::RectangleShape(sf::Vector2f(270, 80));
    equip.background.setPosition(posBackground);
    equip.background.setFillColor(sf::Color::Color(240, 240, 240));

    // Level background and text
    equip.levelBg = sf::RectangleShape(sf::Vector2f(80, 80));
    equip.levelBg.setPosition(posBackground + sf::Vector2f(190, 0));
    equip.levelBg.setFillColor(sf::Color::Color(54, 54, 54));

    equip.textLevel.setString("LvL" + std::to_string(equip.level));
    equip.textLevel.setFont(arialttf);
    equip.textLevel.setCharacterSize(25);
    equip.textLevel.setFillColor(sf::Color::White);
    equip.textLevel.setPosition(posNameText + sf::Vector2f(195, 40));

    return equip;
}

/*
// Ressources background and text
equip.ressourcesBg = sf::RectangleShape(sf::Vector2f(80, 80));
equip.ressourcesBg.setPosition(posBackground + sf::Vector2f(190, 0));
equip.ressourcesBg.setFillColor(sf::Color::Color(54, 54, 54));

equip.nameRessource.setString("LvL" + std::to_string(equip.level));
equip.nameRessource.setFont(arialttf);
equip.nameRessource.setCharacterSize(25);
equip.nameRessource.setFillColor(sf::Color::White);
equip.nameRessource.setPosition(posNameText + sf::Vector2f(195, 40));*/