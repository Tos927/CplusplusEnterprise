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
	// General
	TypeOfEnemies type;
	sf::CircleShape shape;
	float speed = 5;
	int life = 1;

	// -- Système de tire -- //
	// Semi - automatique
	float rate = 1.f;

	// Par rafale
	float semiRate = 0.f;
	int nbBulletSemi = 1;

	// Torpille
	int torpedoKey;

	float defaultRate = 0.f;
	float defaultSemiRate = 0.f;
	int defaultNbBulletSemi = 0;
};


struct Torpedo
{
	sf::CircleShape shap;
	int damage = 5;
	int speed = 100;
};


void InitializeEnemy(Enemy& enemy, int type);
void CreatNewEnemy(std::vector<Enemy>& allEnemies, sf::Vector2f position, const int& type);
void MoveToPoint(sf::CircleShape& origin, const sf::Vector2f& target, const int& speed, bool isRotate, const float& deltaTime);
int CreatNewTorpedo(std::map<int, Torpedo>& allTorpedo, sf::Vector2f startPosition);
void Shoot(Enemy& enemy, const float& deltaTime);

void StratHeavyMove(Enemy& enemy, sf::Vector2f shipPosition, const float& deltaTime);
void StratBomberMove(Enemy& enemy, sf::Vector2f shipPosition, const float& deltaTime);
void StratTorpedoLuncherMove(Enemy& enemy, std::map<int, Torpedo>& enemyTorpedo, sf::Vector2f shipPosition, const float& deltaTime);