#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EnemiesBehaviour.h"

#define WIDTH 1920 
#define HEIGHT 1080

struct Enemy;

struct Planet {
	sf::CircleShape pShape;
	bool isValide = false;
	sf::Vector2f position = { 0.f,0.f };
	int level = 0;
	float radius = 5;

	//Aspect combat
	int vie = 100;
	int collisionDamage = 50;
};

std::vector<Planet> NewLevel(int planetMax, int planetMin, float radiusMax, float radiusMin, float security, int bomberMax, int bomberMin, int torpedoMax, int torpedoMin, int heavyMax, int heavyMin, std::vector<Enemy>& allEnemies);