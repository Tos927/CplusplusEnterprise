#pragma once
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "Menu.h"
#include "AppPath.h"
#include <iostream>
#include <SFML/Graphics.hpp>

struct Explosion
{
	sf::CircleShape explosionShape;
	float timeToExpend = 1.0f;
	float currentExpension = 0.0f;
};

Explosion CreationExplosion(sf::Color color);
void ExpendingExplosion(std::vector<Explosion>::iterator& explosionIt, std::vector<Explosion>& explosion, float deltaTime);