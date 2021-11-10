#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Ship
{
	int shipLife = 100;
	sf::CircleShape ship;
	sf::RectangleShape weapon;
	sf::RectangleShape react1;
	sf::RectangleShape react2;

};

struct Bullets
{
	float bulletSpeed = 0.0f;
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::RectangleShape bullet;
};

void InitializeShip(Ship& ship);
void ShipMovement(Ship& ship, float deltaTime, float& angle, float& vitesse);
bool IsOutOfScreen(sf::Vector2f shipPosition, float screenTrigger);
void ResetToCenter(Ship& ship);
void CreateBullet(std::vector<Bullets>& bullets, float bulletSpeed, float bulletAngle, const Ship& shipPosition);
void MouvBullet(Bullets& bullet, float deltaTime);