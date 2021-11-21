#pragma once
#include "AppPath.h"
#include "GeneratorLevel.h"
#include "ShipBehaviour.h"

struct InfoShip;
struct Ship;

struct EquipStruct
{
    int equipID;
    sf::Text name;

    sf::RectangleShape background;

    int level = 1;

    sf::Text textLevel;
    sf::Text previewLevel;

    sf::RectangleShape levelBg;

    sf::Text nameResource;
    sf::RectangleShape resourcesBg;

    sf::Text neededResourcesText;
    int neededResources = 25; //default 25

    sf::Text keyText;
    std::string key;

    sf::Text definition;

    sf::Text currentBonus;
    int currentStatsBonus = 0;
    int statsBonusOnLevelUp = 0;
};

struct RessourcesStorage
{
    sf::Text storage;
    sf::RectangleShape resourcesBg;

    std::string resource = "Resources ";
    sf::Text nameResource;

    int ownResource = 0;// Need 2 272 118 to Lvl99
};

// Fonction qui Setup un text et le place dans la fenetre 
sf::Text SetUpText(std::string textContent, sf::Font& font, int charaSize, sf::Color color, sf::Vector2f posText);

// Fonction qui Setup un RectangleShape/Background et le place dans la fenetre 
sf::RectangleShape SetupBackground(sf::Vector2f backgroundSize, sf::Color color, sf::Vector2f posBackground);

// Fonction qui crée le storage
RessourcesStorage Storage(sf::Font& font);

//Fonction qui crée les Equip
EquipStruct Equip(int equipID, std::string key, std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& font, int statsBonusOnLevelUp, std::string description);

//Fonction qui crée le background du Menu
sf::RectangleShape Menu(sf::Vector2f rectangleSize, sf::Color color, sf::Vector2f position);

void DrawEquip(EquipStruct&, sf::RenderWindow&);

void UpdateTextLevel(EquipStruct& equip, sf::Vector2f posbackG, std::string bonusType, RessourcesStorage& storage);

void UpdateEquipOnLevelUp(EquipStruct& equip, RessourcesStorage& storage, InfoShip& infoShip, Ship& ship);

void UpdateStorage(RessourcesStorage& storage);

void UpdateStorageInGame(RessourcesStorage& storageInGame);

void DrawOneStorage(RessourcesStorage& storage, sf::RenderWindow& window);

void SetOriginText(sf::Text& text);

void UpdateLifeBar(Ship& ship, InfoShip& infoShip, sf::RectangleShape& lifeBar, int maxlifeWidth, int maxLifeHeight, sf::Text& lifeInGame);