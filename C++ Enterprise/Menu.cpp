#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "AppPath.h"
#include "GeneratorLevel.h"

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
    sf::RectangleShape menu (sf::Vector2f(WIDTH *0.50, HEIGHT*0.70));
    menu.setFillColor(sf::Color::Color(0, 0, 94));
    menu.setPosition(WIDTH * 0.50, HEIGHT * 0.50);
    menu.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);

    return menu;
}

struct EquipStruct Equip(std::string key, std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf)
{
    EquipStruct equip;

    // Equip background and name text
    equip.name = SetUpText(name, arialttf, 20, sf::Color::Black, posNameText);

    float equipBgWidth = WIDTH * 0.22;
    float equipBgHeight = HEIGHT * 0.12;

    equip.background = SetupBackground(sf::Vector2f(equipBgWidth, equipBgHeight), sf::Color::Color(240, 240, 240), posBackground);

    // Level background and text

    float levelBgWidth = WIDTH * 0.055;
    
    equip.levelBg = SetupBackground(sf::Vector2f(levelBgWidth, equipBgHeight), sf::Color::Color(54, 54, 54), posBackground + sf::Vector2f(equipBgWidth - levelBgWidth, 0)); //190 0

    // Place the text Lvl1 at the center bottom of the level's background 
    equip.textLevel = SetUpText("LvL" + std::to_string(equip.level), arialttf, 25, sf::Color::White, posBackground + sf::Vector2f(equipBgWidth - (levelBgWidth/2), levelBgWidth * 0.80));
    equip.textLevel.setOrigin((equip.textLevel.getGlobalBounds().width / 2), (equip.textLevel.getGlobalBounds().height / 2));

    // Place the text Press E/R/T/Y at the center Top of the level's background 
    equip.keyText = SetUpText("Press " + key, arialttf, 15, sf::Color::White, posBackground + sf::Vector2f(equipBgWidth - (levelBgWidth / 2), levelBgWidth * 0.20));
    equip.keyText.setOrigin((equip.keyText.getGlobalBounds().width / 2), (equip.keyText.getGlobalBounds().height / 2));

    equip.neededResourcesText = SetUpText("Needed resources : " + std::to_string(equip.neededResources), arialttf, 13, sf::Color::Black, posNameText + sf::Vector2f(0, 25));

    return equip;
}

struct RessourcesStorage Storage(sf::Font& arialttf)
{
    RessourcesStorage storage;

    float resourcesBgWidth = WIDTH * 0.110;

    // Place the resourcesBg on top right of the menu at the same place than the equips right
    storage.resourcesBg = SetupBackground(sf::Vector2f(resourcesBgWidth, HEIGHT * 0.10), sf::Color::Color(240,240,240), sf::Vector2f(WIDTH * 0.675 - (resourcesBgWidth/2), HEIGHT * 0.18));

    // Place the text at the middle top of resourcesBg
    storage.storage = SetUpText("Ressource Storage", arialttf, 20, sf::Color::Black, sf::Vector2f(WIDTH * 0.675 - (resourcesBgWidth/2) + (resourcesBgWidth/2), HEIGHT * (0.18 + 0.02)));
    storage.storage.setOrigin((storage.storage.getGlobalBounds().width / 2), (storage.storage.getGlobalBounds().height / 2));

    storage.nameResource = SetUpText(storage.resource + std::to_string(storage.ownResource), arialttf, 25, sf::Color::Black, sf::Vector2f(WIDTH * 0.675 - (resourcesBgWidth / 2) + (resourcesBgWidth / 2), HEIGHT * (0.18 + 0.08)));
    storage.nameResource.setOrigin((storage.nameResource.getGlobalBounds().width / 2), (storage.nameResource.getGlobalBounds().height / 2));

    return storage;
}

void DrawEquip(EquipStruct& equip, sf::RenderWindow& window)
{
    window.draw(equip.background);
    window.draw(equip.name);
    window.draw(equip.levelBg);
    window.draw(equip.textLevel);
    window.draw(equip.neededResourcesText);
    window.draw(equip.keyText);
}

void UpdateTextLevel(EquipStruct& equip, sf::Vector2f posbackG)
{
    equip.textLevel.setString("LvL" + std::to_string(equip.level));

    equip.neededResourcesText.setString("Needed resources : " + std::to_string(equip.neededResources));

    equip.textLevel.setPosition(posbackG + sf::Vector2f(WIDTH * 0.22 - (WIDTH * 0.055 / 2), (WIDTH * 0.055) * 0.80));
    equip.textLevel.setOrigin((equip.textLevel.getGlobalBounds().width / 2), (equip.textLevel.getGlobalBounds().height / 2));
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