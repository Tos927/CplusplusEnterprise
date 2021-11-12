#pragma once
#include <SFML/Graphics.hpp>


enum TypeOfEnemies
{
	SimpleEnemy,
	HeavyEnemy,
	BomberEnemy,
	TorpedoLuncherEnemy,
};

struct Enemy {
	TypeOfEnemies type;
	sf::CircleShape shape;
	float speed = 5;
	int life = 1;

	// Système de tire
	// Semi
	float rate = 1.f;

	// Par rafale
	float semiRate = 0.f;
	int nbBulletSemi = 1;

	float defaultRate = 0.f;
	float defaultSemiRate = 0.f;
	int defaultNbBulletSemi = 0;
};

void InitializeEnemy(Enemy& enemy, int type);
void CreatNewEnemy(std::vector<Enemy>& allEnemies, sf::Vector2f position, const int& type);
void MoveToPoint(sf::CircleShape& origin, const sf::Vector2f& target, const int& speed, bool isRotate, const float& deltaTime);
void Shoot(Enemy& enemy, const float& deltaTime);

void StratHeavyMove(Enemy& enemy, sf::Vector2f shipPosition, const float& deltaTime);
void StratBomberMove(Enemy& enemy, sf::Vector2f shipPosition, const float& deltaTime);