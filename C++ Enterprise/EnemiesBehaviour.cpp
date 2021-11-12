
#include <iostream>
#include <vector>
#include "EnemiesBehaviour.h"


void InitializeEnemy(Enemy& enemy, int type) {

	switch (type)
	{
		case 0: {
			// Apparence
			enemy.type = TypeOfEnemies::SimpleEnemy;
			enemy.shape = sf::CircleShape(20, 3);
			enemy.shape.setFillColor(sf::Color::Blue);
			enemy.shape.setOrigin(20, 20);
			break;
		}
		
		case 1: {
			// Apparence
			enemy.type = TypeOfEnemies::HeavyEnemy;
			enemy.shape = sf::CircleShape(20, 5);
			enemy.shape.setFillColor(sf::Color::Red);
			enemy.shape.setOrigin(20, 20);

			// Système de tire
			enemy.rate = 3.f;
			enemy.defaultRate = 3.f;
			enemy.semiRate = 0.2f;
			enemy.defaultSemiRate = 0.2f;
			enemy.nbBulletSemi = 4;
			enemy.defaultNbBulletSemi = 4;

			break;
		}

		case 2: {
			// Apparence
			enemy.type = TypeOfEnemies::BomberEnemy;
			enemy.shape.setRadius(10);
			enemy.shape.setOutlineThickness(1);
			enemy.shape.setFillColor(sf::Color::Transparent);
			enemy.shape.setOutlineColor(sf::Color::Red);
			enemy.shape.setOrigin(10, 10);

			// Pas de tire.
			enemy.speed = 70;
			break;
		}

		case 3: {
			// Apparence
			enemy.type = TypeOfEnemies::TorpedoLuncherEnemy;
			enemy.shape = sf::CircleShape(15, 4);
			enemy.shape.setFillColor(sf::Color::Cyan);
			enemy.shape.setOrigin(15, 15);
			break;
		}

	}
}


void CreatNewEnemy(std::vector<Enemy>& allEnemies, sf::Vector2f position, const int& type) {
	Enemy newEnemy;
	InitializeEnemy(newEnemy, type);
	newEnemy.shape.setPosition(position);
	allEnemies.push_back(newEnemy);
}


void StratHeavyMove(Enemy& enemy, sf::Vector2f shipPosition, const float& deltaTime) {
	// Système de tire par rafale
	Shoot(enemy, deltaTime);
}


void StratBomberMove(Enemy& enemy, sf::Vector2f shipPosition, const float& deltaTime) {
	// L'ennemi ce dirige sur la position du vaiseau
	MoveToPoint(enemy.shape, shipPosition, enemy.speed, false, deltaTime);
}


void Shoot(Enemy& enemy, const float& deltaTime) {
	enemy.rate -= deltaTime;

	if (enemy.rate < 0) {
		enemy.semiRate -= deltaTime;

		if (enemy.semiRate < 0) {

			if (enemy.nbBulletSemi > 0) {

				std::cout << "shoot" << std::endl;

				enemy.semiRate = enemy.defaultSemiRate;
				enemy.nbBulletSemi--;
			}
			else {
				enemy.rate = enemy.defaultRate;
				enemy.semiRate = enemy.defaultSemiRate;
				enemy.nbBulletSemi = enemy.defaultNbBulletSemi;
			}
		}
	}
}


void MoveToPoint(sf::CircleShape& origin, const sf::Vector2f& target, const int& speed, bool isRotate, const float& deltaTime) {
	double radians = atan2(target.y - origin.getPosition().y, target.x - origin.getPosition().x);

	sf::Vector2f direction;
	direction.x = cos(radians) * speed * deltaTime;
	direction.y = sin(radians) * speed * deltaTime;

	origin.move(direction);

	if (isRotate) {
		origin.setRotation(radians * 180 / 3.141592653589793238463);
	}
}