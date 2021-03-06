#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "AppPath.h"
#include "GeneratorLevel.h"
#include "Menu.h"
#include <vector>

struct Ship
{
	int damagePower = 50;
	int currentLife;
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