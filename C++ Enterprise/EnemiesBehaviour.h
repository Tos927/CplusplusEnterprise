#pragma once
#include <SFML/Graphics.hpp>
#include "ShipBehaviour.h"


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

	// -- Syst�me de tire -- //
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
	float timeOfBending = 20;
};


void InitializeEnemy(Enemy& enemy, int type);
void CreatNewEnemy(std::vector<Enemy>& allEnemies, sf::Vector2f position, const int& type);
void MoveToPoint(sf::CircleShape& origin, const sf::Vector2f& target, const int& speed, bool isRotate, const float& deltaTime);
int CreatNewTorpedo(std::map<int, Torpedo>& allTorpedo, sf::Vector2f startPosition);
void Shoot(Enemy& enemy, const float& deltaTime);
bool CollideWithShip(Ship& ship, sf::CircleShape origine);
// bool CollideWithFrendlyBullet(std::vector<Bullet> allBullets, sf::CircleShape origine);

std::vector<Enemy>::iterator StratHeavyMove(std::vector<Enemy>::iterator& enemyIt, sf::Vector2f shipPosition, const float& deltaTime);
std::vector<Enemy>::iterator StratBomberMove(std::vector<Enemy>::iterator& enemyIt, std::vector<Enemy>& allEnemy, Ship& ship, const float& deltaTime);
std::vector<Enemy>::iterator StratTorpedoLuncherMove(std::vector<Enemy>::iterator& enemyIt, std::map<int, Torpedo>& enemyTorpedo, sf::Vector2f shipPosition, const float& deltaTime);