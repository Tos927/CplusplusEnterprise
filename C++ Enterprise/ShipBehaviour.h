#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "AppPath.h"
#include "GeneratorLevel.h"
#include <vector>

struct InfoShip
{
	int shipLevel = 1;

	std::string atkString = "ATK : ";
	int atkPoints = 50;

	std::string lifeString = " / HP : ";
	int lifePoints = 100;

	std::string bspeedString = " / Bullet Speed : ";
	float bspeedPoints = 300.0f;
};

struct Ship
{
	int damagePower = 50;
	int currentLife = 100;
	sf::CircleShape ship;
	sf::RectangleShape weapon;
	sf::RectangleShape react1;
	sf::RectangleShape react2;

};

struct Bullets
{
	int damage = 1;
	float bulletSpeed = 0.0f;
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::RectangleShape bullet;
};

void InitializeShip(Ship& ship);
void ShipMovement(Ship& ship, float deltaTime, float& angle, float& vitesse);
bool IsOutOfScreen(sf::Vector2f shipPosition, float screenTrigger);
void ResetToCenter(Ship& ship);
void CreateBullet(std::vector<Bullets>& bullets, InfoShip& infoShip, float bulletAngle, const Ship& shipPosition);
void MouvBullet(Bullets& bullet, float deltaTime);
void ActualisationProps(std::vector<Planet>& planete, std::vector<Bullets>& bullet, RessourcesStorage& ressource);