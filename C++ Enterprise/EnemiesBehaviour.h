#pragma once
#include <SFML/Graphics.hpp>
#include "ShipBehaviour.h"
#include "Menu.h"


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
	int damage = 25;
	float speed = 5;
	int life = 1;

	// -- Système de tire -- //
	// Semi - automatique
	float speedBullet = 5;
	float rate = 1.f;
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
void Shoot(Enemy& enemy, std::vector<Bullets>& enemyBullets, float angle, const float& deltaTime);
bool CollideWithShip(Ship& ship, sf::Vector2f originePos, int radius);
bool CollideWithFrendlyBullet(std::vector<Bullets>& allBullets, sf::CircleShape origine, bool destroyBullet);
void TakeDamage(Ship& ship, int damage);
void GainResources(RessourcesStorage& ressource, int gain, int tableaux);

std::vector<Enemy>::iterator StratHeavyMove(std::vector<Enemy>::iterator& enemyIt, std::vector<Enemy>& allEnemy, std::vector<Bullets>& shipBullets, Ship& ship, InfoShip& info, std::vector<Bullets>& enemyBullets, sf::Vector2f shipPosition, RessourcesStorage& ressource, const float& deltaTime, int tableaux);
std::vector<Enemy>::iterator StratBomberMove(std::vector<Enemy>::iterator& enemyIt, std::vector<Enemy>& allEnemy, std::vector<Bullets>& allbullets, Ship& ship, InfoShip& info, RessourcesStorage& ressource, const float& deltaTime, int tableaux);
std::vector<Enemy>::iterator StratTorpedoLuncherMove(std::vector<Enemy>::iterator& enemyIt, std::vector<Enemy>& allEnemy, std::map<int, Torpedo>& enemyTorpedo, InfoShip& info, std::vector<Bullets>& allBullets, sf::Vector2f shipPosition, RessourcesStorage& ressource, const float& deltaTime, int tableaux);