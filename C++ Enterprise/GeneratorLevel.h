#pragma once
#include <SFML/Graphics.hpp>

#define WIDTH 1000
#define HEIGHT 1000


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

std::vector<Planet> NewLevel(int planetMax, int planetMin, float radiusMax, float radiusMin, float security);