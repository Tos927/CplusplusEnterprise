#pragma once
#include <SFML/Graphics.hpp>

struct Ship
{
	int shipLife = 100;
	sf::CircleShape ship;
	sf::RectangleShape weapon;
	sf::RectangleShape react1;
	sf::RectangleShape react2;

};

void InitializeShip(Ship& ship);
void ShipMovement(Ship& ship, float deltaTime, float& angle);
bool IsOutOfScreen(sf::Vector2f shipPosition, float screenTrigger);