#include "Particules.h"

Explosion CreationExplosion(sf::Color color, sf::Vector2f position)
{
	Explosion explosion;
	explosion.explosionShape.setPosition(position);
	explosion.explosionShape.setRadius(0.0f);
	explosion.explosionShape.setFillColor(color);

	float angle = ((double)rand() / RAND_MAX) * (double(360));
	explosion.explosionShape2.setPosition(sf::Vector2f(position));
	explosion.explosionShape2.setRadius(0.0f);
	explosion.explosionShape2.setFillColor(sf::Color::Black);
	explosion.explosionShape2.setRotation(angle);

	return explosion;
}

void ExpendingExplosion(std::vector<Explosion>::iterator& explosionIt, const float& deltaTime) 
{
	explosionIt->currentExpension += deltaTime;

	float expend = explosionIt->currentExpension * explosionIt->expentionSpeed;
	explosionIt->explosionShape.setRadius(expend);
	explosionIt->explosionShape.setOrigin(expend, expend);

	if (explosionIt->currentExpension > explosionIt->startSecondShape) {
		explosionIt->currentSecondExpension += deltaTime * 1.37f;

		float expend2 = explosionIt->currentSecondExpension * explosionIt->expentionSpeed;
		explosionIt->explosionShape2.setRadius(expend2);
		explosionIt->explosionShape2.setOrigin(expend2 + 3, expend2 + 2);
	}

	if (explosionIt->currentExpension > explosionIt->timeToExpend)
	{
		explosionIt->isValid = false;
	}
}

TrailParticule CreatParticuleTrail(sf::Vector2f position, int r, int g, int b, float angle) {
	TrailParticule particule;
	particule.shape.setPosition(position);
	particule.shape.setSize(sf::Vector2f(5,5));
	particule.shape.setOrigin(10, 2.5f);

	particule.color = sf::Color(r, g, b, 255);
	particule.shape.setFillColor(particule.color);

	float oppAngle = angle - 90;
	particule.shape.setRotation(oppAngle);
	return particule;
}

void UpdateTrail(std::vector<TrailParticule>::iterator& trailIt, int clearSpeed, const float& deltaTime) {
	trailIt->timeDisplay -= deltaTime;

	trailIt->color = sf::Color(trailIt->color.r, trailIt->color.g, trailIt->color.b, trailIt->color.a - deltaTime * clearSpeed);
	trailIt->shape.setFillColor(trailIt->color);

	if (trailIt->timeDisplay <= 0) {
		trailIt->isValid = false;
	}
}

void CreatTrail(std::map<int, Torpedo>::iterator& torpedoIt, std::vector<TrailParticule>& allTrailParticules, const float& deltaTime) {
	if (torpedoIt->second.timeTrail >= 0) {
		torpedoIt->second.timeTrail -= deltaTime;
	}
	else {
		allTrailParticules.push_back(CreatParticuleTrail(torpedoIt->second.shap.getPosition(), 255, 255, 255, torpedoIt->second.shap.getRotation()));
		torpedoIt->second.timeTrail = 0.1f;
	}
}