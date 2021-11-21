#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"

void SetOriginText(sf::Text& text)
{
    text.setOrigin((text.getGlobalBounds().width / 2), (text.getGlobalBounds().height / 2));
}

sf::Text SetUpText(std::string textContent, sf::Font& font, int charaSize, sf::Color color, sf::Vector2f posText)
{
    sf::Text text;

    text.setString(textContent);
    text.setFont(font);
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
sf::RectangleShape Menu(sf::Vector2f rectangleSize, sf::Color color, sf::Vector2f position)
{
    sf::RectangleShape menu(rectangleSize);
    menu.setFillColor(color);
    menu.setPosition(position);
    menu.setOrigin(menu.getSize().x / 2, menu.getSize().y / 2);

    return menu;
}

struct EquipStruct Equip(int equipID, std::string key, std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& font, int statsBonusOnLevelUp, std::string description)
{
    EquipStruct equip;

    equip.equipID = equipID;

    equip.statsBonusOnLevelUp = statsBonusOnLevelUp;

    // Equip background and name text
    equip.name = SetUpText(name, font, 17, sf::Color::Black, posNameText);

    float equipBgWidth = WIDTH * 0.22;
    float equipBgHeight = HEIGHT * 0.12;

    equip.background = SetupBackground(sf::Vector2f(equipBgWidth, equipBgHeight), sf::Color::Color(240, 240, 240), posBackground);

    // Level background and text

    float levelBgWidth = WIDTH * 0.055;

    equip.levelBg = SetupBackground(sf::Vector2f(levelBgWidth, equipBgHeight), sf::Color::Color(54, 54, 54), posBackground + sf::Vector2f(equipBgWidth - levelBgWidth, 0)); //190 0

    // Place the text Lvl1 at the center bottom of the level's background 
    equip.textLevel = SetUpText("LvL" + std::to_string(equip.level), font, 20, sf::Color::White, posBackground + sf::Vector2f(equipBgWidth - (levelBgWidth / 2), levelBgWidth * 0.80));
    SetOriginText(equip.textLevel);

    // Place the preview level 
    equip.previewLevel = SetUpText("LvL" + std::to_string(equip.level) + " -> LvL" + std::to_string(equip.level + 1), font, 10, sf::Color::White, posBackground + sf::Vector2f(equipBgWidth - (levelBgWidth / 2), levelBgWidth * 0.40));
    SetOriginText(equip.previewLevel);

    // Place the text Press E/R/T/Y at the center Top of the level's background 
    equip.keyText = SetUpText("Press " + key, font, 10, sf::Color::White, posBackground + sf::Vector2f(equipBgWidth - (levelBgWidth / 2), levelBgWidth * 0.20));
    SetOriginText(equip.keyText);

    equip.neededResourcesText = SetUpText("Needed resources : " + std::to_string(equip.neededResources), font, 10, sf::Color::Black, posNameText + sf::Vector2f(0, 25));

    equip.definition = SetUpText(description, font, 8, sf::Color::Black, posNameText + sf::Vector2f(0, 45));

    equip.currentBonus = SetUpText("Current bonus stats : " + std::to_string(equip.currentStatsBonus) + "Current bonus stats : " + std::to_string(equip.currentStatsBonus + equip.statsBonusOnLevelUp), font, 9, sf::Color::Black, posNameText + sf::Vector2f(0, 110));

    equip.background.setOutlineThickness(3);
    equip.background.setOutlineColor(sf::Color::Color(255, 255, 255));

    return equip;
}

struct RessourcesStorage Storage(sf::Font& font)
{
    RessourcesStorage storage;

    float resourcesBgWidth = WIDTH * 0.110;

    // Place the resourcesBg on top right of the menu at the same place than the equips right
    storage.resourcesBg = SetupBackground(sf::Vector2f(resourcesBgWidth, HEIGHT * 0.10), sf::Color::Color(240, 240, 240), sf::Vector2f(WIDTH * 0.675 - (resourcesBgWidth / 2), HEIGHT * 0.18));

    // Place the text at the middle top of resourcesBg
    storage.storage = SetUpText("Ressource Storage", font, 13, sf::Color::Black, sf::Vector2f(WIDTH * 0.675 - (resourcesBgWidth / 2) + (resourcesBgWidth / 2), HEIGHT * (0.18 + 0.02)));
    SetOriginText(storage.storage);

    storage.nameResource = SetUpText(storage.resource + std::to_string(storage.ownResource), font, 25, sf::Color::Black, sf::Vector2f(WIDTH * 0.675 - (resourcesBgWidth / 2) + (resourcesBgWidth / 2), HEIGHT * (0.18 + 0.08)));


    storage.resourcesBg.setOutlineThickness(3);
    storage.resourcesBg.setOutlineColor(sf::Color::Color(54, 54, 54));

    return storage;
}


void DrawEquip(EquipStruct& equip, sf::RenderWindow& window)
{
    window.draw(equip.background);
    window.draw(equip.name);
    window.draw(equip.levelBg);
    window.draw(equip.textLevel);
    window.draw(equip.previewLevel);
    window.draw(equip.neededResourcesText);
    window.draw(equip.keyText);
    window.draw(equip.definition);
    window.draw(equip.currentBonus);
}

void UpdateTextLevel(EquipStruct& equip, sf::Vector2f posbackG, std::string bonusType, RessourcesStorage& storage)
{
    equip.textLevel.setString("LvL" + std::to_string(equip.level));
    equip.textLevel.setPosition(posbackG + sf::Vector2f(WIDTH * 0.22 - (WIDTH * 0.055 / 2), (WIDTH * 0.055) * 0.80));
    SetOriginText(equip.textLevel);

    equip.currentBonus.setString("Stats bonus : " + std::to_string(equip.currentStatsBonus) + " -> " + std::to_string(equip.currentStatsBonus + equip.statsBonusOnLevelUp) + bonusType);

    if (equip.level >= 99)
    {
        equip.previewLevel.setString("LvL Max");
        equip.previewLevel.setPosition(posbackG + sf::Vector2f(WIDTH * 0.22 - (WIDTH * 0.055 / 2), (WIDTH * 0.055) * 0.40));
        SetOriginText(equip.previewLevel);
        equip.previewLevel.setFillColor(sf::Color::Black);

        equip.neededResourcesText.setString("Needed resources : Max");

        return;
    }
    else
    {
        if (storage.ownResource >= equip.neededResources)
        {
            equip.previewLevel.setFillColor(sf::Color::Green);
        }
        else
        {
            equip.previewLevel.setFillColor(sf::Color::Red);
        }
    }

    equip.previewLevel.setString("LvL" + std::to_string(equip.level) + " -> LvL" + std::to_string(equip.level + 1));
    equip.previewLevel.setPosition(posbackG + sf::Vector2f(WIDTH * 0.22 - (WIDTH * 0.055 / 2), (WIDTH * 0.055) * 0.40));
    SetOriginText(equip.previewLevel);

    equip.neededResourcesText.setString("Needed resources : " + std::to_string(equip.neededResources));

}

void UpdateEquipOnLevelUp(EquipStruct& equip, RessourcesStorage& storage, InfoShip& infoShip, Ship& ship)
{
    if (equip.level < 99)
    {
        storage.ownResource -= equip.neededResources;
        equip.neededResources = equip.neededResources + (equip.neededResources * 0.10);

        equip.level++;

        if (equip.equipID != 3 && equip.equipID != 4)
        {
            equip.statsBonusOnLevelUp += 10;
        }   

        if (equip.equipID == 3 && equip.level > 27)
        {
            equip.statsBonusOnLevelUp += 1;
        }

        if (equip.equipID == 4)
        {
            switch (equip.level)
            {
            case 10:
            case 20:
            case 30:
            case 40:
            case 50:
            case 60:
                equip.statsBonusOnLevelUp += 1;
                break;
            case 70:
            case 80:
            case 90:
                equip.statsBonusOnLevelUp += 2;
                break;
            }
        }

        equip.currentStatsBonus += equip.statsBonusOnLevelUp;
        
        switch (equip.equipID)
        {
        case 1:
            // Increases the maximum life of the ship 
            infoShip.lifePoints += equip.statsBonusOnLevelUp;
            // Add the stats bonus on lpppevelup at the current life
            ship.currentLife += equip.statsBonusOnLevelUp;
            break;
        case 2:
            // Increases the attack of the ship 
            infoShip.atkPoints += equip.statsBonusOnLevelUp;
            break;
        case 3:
            // Increases the bullet speed of the ship
            infoShip.bspeedPoints += equip.statsBonusOnLevelUp;

            Clamp(infoShip.bspeedPoints, 0, 3000);
            Clamp(equip.currentStatsBonus, 0, 2700);

            if (infoShip.bspeedPoints >= 3000)
            {
                equip.statsBonusOnLevelUp = 0;
            }
            break;
        case 4:
            infoShip.speed += equip.statsBonusOnLevelUp;
            break;
        }
    }
}

void UpdateStorage(RessourcesStorage& storage)
{
    storage.nameResource.setString(std::to_string(storage.ownResource));
    storage.nameResource.setPosition(sf::Vector2f(WIDTH * 0.675 - (WIDTH * 0.110 / 2) + (WIDTH * 0.110 / 2), HEIGHT * (0.18 + 0.06)));
    SetOriginText(storage.nameResource);
}

void UpdateStorageInGame(RessourcesStorage& storageInGame)
{
    storageInGame.resourcesBg.setFillColor(sf::Color::Black);
    storageInGame.resourcesBg.setPosition(sf::Vector2f(WIDTH * 5, HEIGHT * 5));
    storageInGame.storage.setPosition(sf::Vector2f(WIDTH * 0.925, HEIGHT * 0.04));
    storageInGame.storage.setFillColor(sf::Color::White);
    storageInGame.storage.setOutlineColor(sf::Color::Black);
    storageInGame.storage.setOutlineThickness(1);

    storageInGame.nameResource.setPosition(sf::Vector2f(WIDTH * 0.925, HEIGHT * 0.08));
    storageInGame.nameResource.setFillColor(sf::Color::White);
    storageInGame.nameResource.setOutlineColor(sf::Color::Black);
    storageInGame.nameResource.setOutlineThickness(1);
}

void DrawOneStorage(RessourcesStorage& storage, sf::RenderWindow& window)
{
    window.draw(storage.resourcesBg);
    window.draw(storage.storage);
    window.draw(storage.nameResource);
}

void UpdateLifeBar(Ship& ship, InfoShip& infoShip, sf::RectangleShape& lifeBar, int maxlifeWidth, int maxLifeHeight, sf::Text& lifeInGame)
{
    if (ship.currentLife < 0)
    {
        ship.currentLife = 0;
    }

    if (ship.currentLife > infoShip.lifePoints)
    {
        ship.currentLife = infoShip.lifePoints;
    }

    // Create a float that contains the current percentage of life 
    float currentPercentageOfLife = ((float)ship.currentLife / (float)infoShip.lifePoints);

    // Set the life bar on the current percentage of life
    lifeBar.setSize(sf::Vector2f(maxlifeWidth * currentPercentageOfLife, maxLifeHeight));

    // Update the Text of life on the life bar
    lifeInGame.setString(std::to_string(ship.currentLife) + "/" + std::to_string(infoShip.lifePoints));
    SetOriginText(lifeInGame);
    //lifeInGame.setPosition(sf::Vector2f(maxlifeWidth, maxLifeHeight) - sf::Vector2f(maxlifeWidth / 2, -32.5));
    lifeInGame.setPosition(sf::Vector2f(WIDTH * 0.02, HEIGHT * 0.05) + sf::Vector2f(maxlifeWidth /2, maxLifeHeight/3));
}

void Clamp(int& valeur, int min, int max)
{
    if (valeur > max)
    {
        valeur = max;
    }
    else if (valeur < min)
    {
        valeur = min;
    }
}

void Clamp(float& valeur, float min, float max)
{
    if (valeur > max)
    {
        valeur = max;
    }
    else if (valeur < min)
    {
        valeur = min;
    }
}