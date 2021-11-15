#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "AppPath.h"

sf::Text SetUpText(std::string textContent, sf::Font& arialttf, int charaSize, sf::Color color, sf::Vector2f posText)
{
    sf::Text text;

    text.setString(textContent);
    text.setFont(arialttf);
    text.setCharacterSize(charaSize);
    text.setFillColor(color);
    text.setPosition(posText);

    return text;
}

sf::RectangleShape SetupBackground(sf::Vector2f backgroundSize, sf::Color color, sf::Vector2f posBackground)
{
    sf::RectangleShape background(backgroundSize);
    background.setFillColor(color); // RGB sf::Color::Color(255, 255, 255)
    background.setPosition(posBackground);

    return background;
}

// Fond du Menu
sf::RectangleShape Menu()
{
    sf::RectangleShape menu (sf::Vector2f(600, 300));
    menu.setFillColor(sf::Color::Color(0, 0, 94));
    menu.setPosition(400, 300);
    menu.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);

    return menu;
}

struct EquipStruct Equip(std::string key, std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf)
{
    EquipStruct equip;

    // Equip background and name text
    equip.name = SetUpText(name, arialttf, 15, sf::Color::Black, posNameText);

    equip.background = SetupBackground(sf::Vector2f(270, 80), sf::Color::Color(240, 240, 240), posBackground);

    // Level background and text

    equip.levelBg = SetupBackground(sf::Vector2f(80, 80), sf::Color::Color(54, 54, 54), posBackground + sf::Vector2f(190, 0));

    equip.textLevel = SetUpText("LvL" + std::to_string(equip.level), arialttf, 25, sf::Color::White, posNameText + sf::Vector2f(195, 40));

    equip.keyText = SetUpText("Press " + key, arialttf, 15, sf::Color::White, posNameText + sf::Vector2f(195, 0));

    equip.neededResourcesText = SetUpText("Needed resources : " + std::to_string(equip.neededResources), arialttf, 12, sf::Color::Black, posNameText + sf::Vector2f(0, 20));

    return equip;
}

struct RessourcesStorage Storage(sf::Font& arialttf)
{
    RessourcesStorage storage;

    storage.resourcesBg = SetupBackground(sf::Vector2f(100, 80), sf::Color::Color(240, 240, 240), sf::Vector2f(580, 170));

    storage.storage = SetUpText("Storage", arialttf, 20, sf::Color::Black, sf::Vector2f(595, 170));

    storage.nameResource = SetUpText(storage.resource + std::to_string(storage.ownResource), arialttf, 11, sf::Color::Black, sf::Vector2f(585, 200));


    return storage;
}




/*
// Resources background and text
equip.resourcesBg = sf::RectangleShape(sf::Vector2f(80, 80));
equip.resourcesBg.setPosition(posBackground + sf::Vector2f(190, 0));
equip.resourcesBg.setFillColor(sf::Color::Color(54, 54, 54));

equip.nameRessource.setString("LvL" + std::to_string(equip.level));
equip.nameResource.setFont(arialttf);
equip.nameResource.setCharacterSize(25);
equip.nameResource.setFillColor(sf::Color::White);
equip.nameResource.setPosition(posNameText + sf::Vector2f(195, 40));*/