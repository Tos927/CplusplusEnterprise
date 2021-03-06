#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#define PI 3.141592653589793238463

void InitializeShip(Ship& ship) 
{
	//Initialisation des formes du vaisseau
	sf::Vector2f test = { 45.0f, 15.0f };
	ship.ship.setRadius(30.0f);
	ship.weapon.setSize({ 50.0f, 10.0f });
	ship.react1.setSize(test);
	ship.react2.setSize(test);

	//Initialisation des origines de chaques parties du vaisseau
	ship.ship.setOrigin(30.0f, 30.0f);
	ship.weapon.setOrigin(0.0f, 5.0f);
	ship.react1.setOrigin(45.0f, -5.0f);
	ship.react2.setOrigin(45.0f, 20.0f);

	//Initialisation de la position du vaisseau
	ResetToCenter(ship);

	//Colorisation elements
	ship.ship.setFillColor(sf::Color::Blue);
	ship.weapon.setFillColor(sf::Color::Red);
	ship.react1.setFillColor(sf::Color::Green);
	ship.react2.setFillColor(sf::Color::Green);
}

void ShipMovement(Ship& ship, float deltaTime, float& angle, float& vitesse) 
{
	int rotationSpeed = 200;

	//Rotation du vaisseau
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		angle -= rotationSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
		angle += rotationSpeed * deltaTime;
	}
	ship.ship.setRotation(angle);
	ship.weapon.setRotation(angle);
	ship.react1.setRotation(angle);
	ship.react2.setRotation(angle);

	//Propultion du vaisseau
	int speed = 200;
	int maxSpeed = 300;
	int minSpeed = 0;
	sf::Vector2f direction;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction.x = cos(angle/180 * PI) * speed * deltaTime;
		direction.y = sin(angle/180 * PI) * speed * deltaTime;
		ship.ship.move(direction);
		ship.weapon.move(direction);
		ship.react1.move(direction);
		ship.react2.move(direction);

	}
}

bool IsOutOfScreen(sf::Vector2f shipPosition, float screenTrigger)
{
	if (shipPosition.x + screenTrigger >= 1000 || shipPosition.x + screenTrigger <= 0 || shipPosition.y + screenTrigger >= 1000 || shipPosition.y + screenTrigger <= 0)
	{
		return true;
	}
	return false;
}

void ResetToCenter(Ship& ship) 
{
	ship.ship.setPosition(sf::Vector2f(500.0f, 500.0f));
	ship.weapon.setPosition(sf::Vector2f(500.0f, 500.0f));
	ship.react1.setPosition(sf::Vector2f(500.0f, 500.0f));
	ship.react2.setPosition(sf::Vector2f(500.0f, 500.0f));
}

void CreateBullet(std::vector<Bullets>& bullets, InfoShip& infoShip, float bulletAngle, const Ship& shipPosition)
{
	Bullets newBullet;

	newBullet.bullet.setSize({ 5.f, 2.f });

	newBullet.position = shipPosition.ship.getPosition();
	newBullet.bulletSpeed = infoShip.bspeedPoints;
	newBullet.direction.x = cos(shipPosition.ship.getRotation() / 180 * PI);
	newBullet.direction.y = sin(shipPosition.ship.getRotation() / 180 * PI);

	newBullet.bullet.setPosition(newBullet.position);
	newBullet.bullet.setRotation(shipPosition.ship.getRotation());

	newBullet.damage = infoShip.atkPoints;

	bullets.push_back(newBullet);
}

void MouvBullet(Bullets& bullet, float deltaTime) {
	sf::Vector2f move = bullet.direction * bullet.bulletSpeed * deltaTime;
	bullet.bullet.move(move);
}

void ActualisationProps(std::vector<Planet>& planete, std::vector<Bullets>& bullet)
{
	auto pIt = planete.begin();
	while (pIt != planete.end())
	{
		auto bulIt = bullet.begin();
		while (bulIt != bullet.end())
		{
			float distance = std::sqrt(pow(pIt->position.x - (*bulIt).bullet.getPosition().x, 2) + pow(pIt->position.y - (*bulIt).bullet.getPosition().y, 2));
			if (distance <= pIt->radius)
			{
				pIt->vie -= bulIt->damage;
				bulIt = bullet.erase(bulIt);
				std::cout << "Touche" << std::endl;
			}
			else
			{
				bulIt++;
			}
		}
		if ((*pIt).vie <= 0)
		{
			pIt = planete.erase(pIt);
		}
		else
		{
			pIt++;
		}
	}
}