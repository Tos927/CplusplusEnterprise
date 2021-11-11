
#include <iostream>
#include <vector>
#include "EnemiesBehaviour.h"



void InitializeEnemy(Enemy& enemy, int type) {

	switch (type)
	{
		case 0: {
			enemy.type = TypeOfEnemies::SimpleEnemy;
			enemy.shape = sf::CircleShape(20, 3);
			enemy.shape.setFillColor(sf::Color::Blue);
			enemy.shape.setOrigin(20, 20);
			break;
		}
		
		case 1: {
			enemy.type = TypeOfEnemies::HeavyEnemy;
			enemy.shape = sf::CircleShape(20, 5);
			enemy.shape.setFillColor(sf::Color::Red);
			enemy.shape.setOrigin(20, 20);
			break;
		}

		case 2: {
			enemy.type = TypeOfEnemies::BomberEnemy;
			enemy.shape.setRadius(10);
			enemy.shape.setOutlineThickness(1);
			enemy.shape.setFillColor(sf::Color::Transparent);
			enemy.shape.setOutlineColor(sf::Color::Red);
			enemy.shape.setOrigin(10, 10);
			break;
		}

		case 3: {
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


void StartBomberMove(Enemy& enemy, sf::Vector2f shipPosition, float deltatime) {
	
}