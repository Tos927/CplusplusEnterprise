#pragma once

struct InfoShip
{
    int shipLevel = 1;

    std::string atkString = "ATK : ";
    int atkPoints = 50;

    std::string lifeString = " / Life : ";
    int lifePoints = 100;

    std::string bspeedString = " / Bullet Speed : ";
    float bspeedPoints = 300.0f;
};

struct EquipStruct
{
    sf::Text name;

    sf::RectangleShape background;

    int level = 1;

    sf::Text textLevel;
    sf::RectangleShape levelBg;

    sf::Text nameResource;
    sf::RectangleShape resourcesBg;

    sf::Text neededResourcesText;
    int neededResources = 25;

    sf::Text keyText;
    std::string key;
};

struct RessourcesStorage
{
    sf::Text storage;
    sf::RectangleShape resourcesBg;

    std::string resource = "Resources ";
    sf::Text nameResource;
    
    int ownResource = 0;
};

// Fonction qui Setup un text et le place dans la fenetre 
sf::Text SetUpText(std::string textContent, sf::Font& arialttf, int charaSize, sf::Color color, sf::Vector2f posText);

// Fonction qui Setup un RectangleShape/Background et le place dans la fenetre 
sf::RectangleShape SetupBackground(sf::Vector2f backgroundSize, sf::Color color, sf::Vector2f posBackground);

// Fonction qui crée le storage
RessourcesStorage Storage(sf::Font& arialttf);

//Fonction qui crée les Equip
EquipStruct Equip(std::string key, std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf);

//Fonction qui crée le background du Menu
sf::RectangleShape Menu();