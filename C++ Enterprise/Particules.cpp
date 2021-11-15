#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "Menu.h"
#include "AppPath.h"
#include "Particules.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Explosion CreationExplosion(sf::Color color)
{
	Explosion explosion;
	explosion.explosionShape.setPosition(sf::Vector2f(200.0f, 300.0f));
	explosion.explosionShape.setRadius(0.0f);
	explosion.explosionShape.setFillColor(color);
	return explosion;
}

void ExpendingExplosion(std::vector<Explosion>::iterator& explosionIt, std::vector<Explosion>& explosion, float deltaTime) 
{
	explosionIt->currentExpension += deltaTime;
	explosionIt->explosionShape.setRadius(explosionIt->currentExpension * 5);
	if (explosionIt->currentExpension > explosionIt->timeToExpend)
	{
		explosion.erase(explosionIt);
	}
}