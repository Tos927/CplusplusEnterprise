#pragma once
#include "EnemiesBehaviour.h"
#include <iostream>
#include <SFML/Graphics.hpp>

struct Explosion
{
	bool isValid = true;
	sf::CircleShape explosionShape;
	sf::CircleShape explosionShape2;
	float timeToExpend = 0.7f;

	float currentExpension = 0.0f;
	float currentSecondExpension = 0.0f;

	float startSecondShape = 0.14f;
	int expentionSpeed = 80;
};

struct TrailParticule {
	bool isValid = true;
	sf::RectangleShape shape;
	sf::Color color;
	float timeDisplay = 2.0f;
};

Explosion CreationExplosion(sf::Color color, sf::Vector2f position);
void ExpendingExplosion(std::vector<Explosion>::iterator& explosionIt,const float& deltaTime);
TrailParticule CreatParticuleTrail(sf::Vector2f position, int r, int g, int b, float angle);
void UpdateTrail(std::vector<TrailParticule>::iterator& trailIt, int clearSpeed, const float& deltaTime);
void CreatTrail(std::map<int, Torpedo>::iterator& torpedoIt, std::vector<TrailParticule>& allTrailParticules, const float& deltaTime);