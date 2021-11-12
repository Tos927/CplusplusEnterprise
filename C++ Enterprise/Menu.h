#pragma once

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
};

struct RessourcesStorage
{
    sf::Text storage;
    sf::RectangleShape resourcesBg;

    std::string stone = "Stone";
    sf::Text nameResource;
    
    int ownResource = 15000;
};

// Fonction qui Setup un text et le place dans la fenetre 
sf::Text SetUpText(std::string textContent, sf::Font& arialttf, int charaSize, sf::Color color, sf::Vector2f posText);

// Fonction qui Setup un RectangleShape/Background et le place dans la fenetre 
sf::RectangleShape SetupBackground(sf::Vector2f backgroundSize, sf::Color color, sf::Vector2f posBackground);

// Fonction qui crée le storage
struct RessourcesStorage Storage(sf::Font& arialttf);

//Fonction qui crée les Equip
struct EquipStruct Equip(std::string name, sf::Vector2f posNameText, sf::Vector2f posBackground, sf::Font& arialttf);

//Fonction qui crée le background du Menu
sf::RectangleShape Menu();






