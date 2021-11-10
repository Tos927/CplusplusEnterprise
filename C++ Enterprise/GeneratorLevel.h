#pragma once
#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 600

#define MIN_PLANET 1.f
#define MAX_PLANET 5.f

#define MIN_RADIUS 5.f
#define MAX_RADIUS 20.f
#define SECURITY_RADIUS 5.f


struct Planet {
	sf::CircleShape pShape;
	bool isValide = false;
	sf::Vector2f position = { 0.f,0.f };
	int level = 0;
	float radius = MIN_RADIUS;

	//Aspect combat
	int vie = 100;
};


std::vector<Planet> NewLevel();