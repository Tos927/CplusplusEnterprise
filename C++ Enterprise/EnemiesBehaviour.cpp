#include <iostream>
#include "EnemiesBehaviour.h"
#include <map>

void InitializeEnemy(Enemy& enemy, int type) {

	switch (type)
	{
		case 0: {
			// Apparence
			enemy.type = TypeOfEnemies::SimpleEnemy;
			enemy.shape = sf::CircleShape(20, 3);
			enemy.shape.setOrigin(20, 20);
			enemy.shape.setFillColor(sf::Color::Transparent);
			enemy.shape.setOutlineThickness(2);
			enemy.shape.setOutlineColor(sf::Color::Blue);
			
			break;
		}
		
		case 1: {
			// Apparence
			enemy.type = TypeOfEnemies::HeavyEnemy;
			enemy.shape = sf::CircleShape(20, 5);
			enemy.shape.setOrigin(20, 20);
			enemy.shape.setFillColor(sf::Color::Transparent);
			enemy.shape.setOutlineThickness(2);
			enemy.shape.setOutlineColor(sf::Color::Red);
			

			// Système de tire
			enemy.speedBullet = 200.f;
			enemy.rate = 3.f;
			enemy.defaultRate = 3.f;
			enemy.semiRate = 0.2f;
			enemy.defaultSemiRate = 0.2f;
			enemy.nbBulletSemi = 4;
			enemy.defaultNbBulletSemi = 4;

			// Vie
			enemy.life = 250;
			break;
		}

		case 2: {
			// Apparence
			enemy.type = TypeOfEnemies::BomberEnemy;
			enemy.shape.setRadius(10);
			enemy.shape.setOrigin(10, 10);
			enemy.shape.setFillColor(sf::Color::Transparent);
			enemy.shape.setOutlineThickness(2);
			enemy.shape.setOutlineColor(sf::Color::Red);
			

			// Pas de tire.
			enemy.speed = 70;
			enemy.damage = 50;
			break;
		}

		case 3: {
			// Apparence
			enemy.type = TypeOfEnemies::TorpedoLuncherEnemy;
			enemy.shape = sf::CircleShape(15, 4);
			enemy.shape.setOrigin(15, 15);
			enemy.shape.setFillColor(sf::Color::Transparent);
			enemy.shape.setOutlineThickness(2);
			enemy.shape.setOutlineColor(sf::Color::Cyan);
			

			// Tire des torpille
			enemy.rate = 5.f;
			enemy.defaultRate = 5.f;

			// Vie
			enemy.life = 150;
			break;
		}

	}
}


/// <summary>
/// Permet de créer un nouvel ennemi d'un certain type à une position précise. 0 : Simple ; 1 : Heavy ; 2 : Bomber ; 3 : TorpedoLuncher.
/// </summary>
void CreatNewEnemy(std::vector<Enemy>& allEnemies, sf::Vector2f position, const int& type) {
	Enemy newEnemy;
	InitializeEnemy(newEnemy, type);
	newEnemy.shape.setPosition(position);
	allEnemies.push_back(newEnemy);
}


/// <summary>
/// Permet de créer une nouvelle torpille initialisée et à des coordonnées précises. Sera stocké dans une map (int, Torpedo) contenant tout les topilles du jeu.
/// </summary>
/// <returns>Clef de la nouvelle torpille stocké dans allTorpedo, type integer</returns>
int CreatNewTorpedo(std::map<int, Torpedo>& allTorpedo, sf::Vector2f startPosition) {
	Torpedo newTorpedo;
	newTorpedo.shap = sf::CircleShape(5, 3);
	newTorpedo.shap.setPosition(startPosition);
	newTorpedo.shap.setOrigin(5, 5);
	newTorpedo.shap.setFillColor(sf::Color::Transparent);
	newTorpedo.shap.setOutlineThickness(2);

	int key = 0;

	if (allTorpedo.size() != 0) {
		std::map<int, Torpedo>::iterator it = allTorpedo.end();
		it--;
		key = it->first + 1;
	}

	allTorpedo[key] = newTorpedo;
	return key;
}


/// <summary>
/// Deplace l'object référencé de sa position initiale aux coordonnées ciblées (relatif ou absolue). Peut avoir une vitesse et peut tourner l'object de référence vers l'objet cible.
/// </summary>
void MoveToPoint(sf::CircleShape& origin, const sf::Vector2f& target, const int& speed, bool isRotate, const float& deltaTime) {
	double radians = atan2(target.y - origin.getPosition().y, target.x - origin.getPosition().x);

	sf::Vector2f direction;
	direction.x = cos(radians) * speed * deltaTime;
	direction.y = sin(radians) * speed * deltaTime;

	origin.move(direction);

	if (isRotate) {
		origin.setRotation((radians * 180 / 3.141592653589793238463) + 90);
	}
}


void Shoot(Enemy& enemy, std::vector<Bullets>& enemyBullets, float angle , const float& deltaTime) {
	enemy.rate -= deltaTime;

	if (enemy.rate < 0) {
		enemy.semiRate -= deltaTime;

		if (enemy.semiRate < 0) {

			if (enemy.nbBulletSemi > 0) {

				CreateBullet(enemyBullets, enemy.speedBullet, enemy.damage, enemy.shape, angle);

				enemy.semiRate = enemy.defaultSemiRate;
				enemy.nbBulletSemi--;
			}
			else {
				enemy.rate = enemy.defaultRate;
				enemy.semiRate = enemy.defaultSemiRate;
				enemy.nbBulletSemi = enemy.defaultNbBulletSemi;
			}
		}
	}
}


bool CollideWithShip(Ship& ship, sf::Vector2f originePos, int radius) {
	sf::Vector2f shipPos = ship.ship.getPosition();
	float distance = std::sqrt(pow(shipPos.x - originePos.x, 2) + pow(shipPos.y - originePos.y, 2));

	if (distance <= radius + ship.ship.getRadius()) {
		return true;
	}

	return false;
}

bool CollideWithFrendlyBullet(std::vector<Bullets>& allBullets, sf::CircleShape origine, bool destroyBullet) {
	bool isOnContact = false;

	std::vector<Bullets>::iterator bulletIt = allBullets.begin();
	while (bulletIt != allBullets.end()) {
		sf::Vector2f shipPos = bulletIt->bullet.getPosition();
		float distance = std::sqrt(pow(shipPos.x - origine.getPosition().x, 2) + pow(shipPos.y - origine.getPosition().y, 2));


		if (distance <= origine.getRadius()) {
			isOnContact = true;

			// détruire la balle si le paramètre est true
			if (destroyBullet) {
				bulletIt = allBullets.erase(bulletIt);
				continue;
			}
			else {
				bulletIt++;
				continue;
			}
		}
		bulletIt++;
	}
	return isOnContact;
}

void TakeDamage(Ship& ship, int damage, int tableaux) {
	ship.currentLife -= damage + (5*tableaux);
	// actualiser UI
}

void GainResources(RessourcesStorage& ressource, int gain, int tableaux, int& totalScore, int& levelMultiplicator, Ship& ship)
{
	int enemyPoint = 15;
	ressource.ownResource += gain + (5 * tableaux);
	ressource.nameResource.setString(ressource.resource + std::to_string(ressource.ownResource));
	totalScore += enemyPoint * levelMultiplicator;
	ship.currentLife += (ship.currentLife * 0.01);
}

// ------------------------------------------------------------------------------ //
// ------------------------------ Enemy Mouvement  ------------------------------ //
// ------------------------------------------------------------------------------ //


void StratHeavyMove(std::vector<Enemy>::iterator& enemyIt, std::vector<Enemy>& allEnemy, std::vector<Bullets>& shipBullets, Ship& ship, InfoShip& info, std::vector<Bullets>& enemyBullets, sf::Vector2f shipPosition, RessourcesStorage& ressource, const float& deltaTime, int tableaux, Points& points) {
	// Système de tire par rafale
	double radians = atan2(shipPosition.y - enemyIt->shape.getPosition().y, shipPosition.x - enemyIt->shape.getPosition().x);

	Shoot((*enemyIt), enemyBullets, radians * 180 / 3.141592653589793238463, deltaTime);


	if (CollideWithFrendlyBullet(shipBullets, enemyIt->shape, true)) {
		enemyIt->life -= info.atkPoints;
		if (enemyIt->life <= 0) {
			GainResources(ressource, 150, tableaux, points.totalPoints, points.levelMultiplicator, ship);
			enemyIt->isValid = false;
		}
	}

	if (CollideWithShip(ship, enemyIt->shape.getPosition(), enemyIt->shape.getRadius())) {
		enemyIt->life -= 50;
		if (enemyIt->life <= 0) {
			GainResources(ressource, 150, tableaux, points.totalPoints, points.levelMultiplicator, ship);
			TakeDamage(ship, enemyIt->damage, tableaux);
			enemyIt->isValid = false;
		}
		else {
			ship.canTakeDamage = false;
		}
	}
}


void StratBomberMove(std::vector<Enemy>::iterator& enemyIt, std::vector<Enemy>& allEnemy, std::vector<Bullets>& allbullets, Ship& ship, InfoShip& info, RessourcesStorage& ressource, const float& deltaTime, int tableaux, Points& points) {
	// L'ennemi ce dirige sur la position du vaiseau
	MoveToPoint(enemyIt->shape, ship.ship.getPosition(), enemyIt->speed, false, deltaTime);

	// -------------- TODO -------------- //
	// déplacement subite lorsque le joueur fait face à l'ennemie

	if (CollideWithShip(ship, enemyIt->shape.getPosition(), enemyIt->shape.getRadius()) && ship.canTakeDamage) {
		TakeDamage(ship, enemyIt->damage, tableaux);
		enemyIt->isValid = false;
	}

	if (CollideWithFrendlyBullet(allbullets, enemyIt->shape, true)) {
		GainResources(ressource, 150, tableaux, points.totalPoints, points.levelMultiplicator, ship);
		enemyIt->isValid = false;
	}
}


void StratTorpedoLuncherMove(std::vector<Enemy>::iterator& enemyIt, std::vector<Enemy>& allEnemy, std::map<int, Torpedo>& enemyTorpedo, InfoShip& info, std::vector<Bullets>& allBullets, sf::Vector2f shipPosition, RessourcesStorage& ressource, const float& deltaTime, int tableaux, Points& points, Ship& ship) {

	std::map<int, Torpedo>::iterator it = enemyTorpedo.find(enemyIt->torpedoKey);

	if (it == enemyTorpedo.end()) {
		enemyIt->rate -= deltaTime;
		if (enemyIt->rate < 0) {
			enemyIt->torpedoKey = CreatNewTorpedo(enemyTorpedo, enemyIt->shape.getPosition());
			enemyIt->rate = enemyIt->defaultRate;
		}
	}

	if (CollideWithFrendlyBullet(allBullets, enemyIt->shape, false)) {
		enemyIt->life -= info.atkPoints;
		if (enemyIt->life <= 0) {
			GainResources(ressource, 150, tableaux, points.totalPoints, points.levelMultiplicator, ship);
			enemyIt->isValid = false;
		}
	}
}
