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

TrailParticule CreatParticuleTrail(sf::Vector2f position, float angle) {
	TrailParticule particule;
	particule.shape.setPosition(position);
	particule.shape.setRadius(5);
	particule.shape.setOrigin(15, 5);

	float oppAngle = angle - 90;
	particule.shape.setRotation(oppAngle);
	return particule;
}

void UpdateTrail(std::vector<TrailParticule>::iterator& trailIt,const float& deltaTime) {
	trailIt->timeDisplay -= deltaTime;

	if (trailIt->timeDisplay <= 0) {
		trailIt->isValid = false;
	}
}

void CreatTrail(std::map<int, Torpedo>::iterator& torpedoIt, std::vector<TrailParticule>& allTrailParticules, const float& deltaTime) {
	if (torpedoIt->second.timeTrail >= 0) {
		torpedoIt->second.timeTrail -= deltaTime;
	}
	else {
		allTrailParticules.push_back(CreatParticuleTrail(torpedoIt->second.shap.getPosition(), torpedoIt->second.shap.getRotation()));
		torpedoIt->second.timeTrail = 0.1f;
	}
}