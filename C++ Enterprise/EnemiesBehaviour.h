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
	int life = 1;
	sf::CircleShape shape;
};

void InitializeEnemy(Enemy& enemy, int type);
void StartBomberMove(Enemy& enemy, sf::Vector2f shipPosition, float deltatime);
void CreatNewEnemy(std::vector<Enemy>& allEnemies, sf::Vector2f position, const int& type);
