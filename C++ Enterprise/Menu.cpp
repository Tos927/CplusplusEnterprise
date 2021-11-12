#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "AppPath.h"

// Fond du Menu
sf::RectangleShape Menu()
{
	std::cout << "test" << std::endl;

    sf::RectangleShape menu (sf::Vector2f(600, 300));
    menu.setFillColor(sf::Color::Red);
    menu.setPosition(400, 300);
    menu.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);

    return menu;
}

// Fond des informations du ship
sf::RectangleShape ShipInfo()
{
    sf::RectangleShape menu(sf::Vector2f(380, 30));
    menu.setFillColor(sf::Color::White);
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
    arialText.setFillColor(sf::Color::Blue);
    arialText.setPosition(125, 170);

    return arialText;
}


struct TextEquipInfoStruct Equip(std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf)
{
    TextEquipInfoStruct equip;

    sf::Text nameText;
    nameText.setString(name);
    nameText.setFont(arialttf);
    nameText.setCharacterSize(15);
    nameText.setFillColor(sf::Color::Blue);
    nameText.setPosition(posNameText); //125,170

    equip.name = nameText;

    equip.background = sf::RectangleShape(sf::Vector2f(270, 80));
    equip.background.setPosition(posBackground);
    equip.background.setFillColor(sf::Color::White); 

    //sf::RectangleShape menu(equip1.posBackground);

    /*menu.setFillColor(sf::Color::White);
    menu.setPosition(120, 170); */

    return equip;
}

/*
sf::Text TextEquipInfo(sf::Font& arialttf)
{
    sf::Text arialText;
    arialText.setFont(arialttf);
    arialText.setString("Armor");
    arialText.setCharacterSize(25);
    arialText.setFillColor(sf::Color::Blue);
    arialText.setPosition(125, 170);

    return arialText;
}*/