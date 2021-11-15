
#include <iostream>
#include "EnemiesBehaviour.h"
#include "ShipBehaviour.h"
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
			enemy.rate = 3.f;
			enemy.defaultRate = 3.f;
			enemy.semiRate = 0.2f;
			enemy.defaultSemiRate = 0.2f;
			enemy.nbBulletSemi = 4;
			enemy.defaultNbBulletSemi = 4;

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
			break;
		}

		case 3: {
			// Apparence
			enemy.type = TypeOfEnemies::TorpedoLuncherEnemy;
			enemy.shape = sf::CircleShape(15, 4);
			enemy.shape.setOutlineColor(sf::Color::Cyan);
			enemy.shape.setOrigin(15, 15);

			// Tire des torpille
			enemy.rate = 5.f;
			enemy.defaultRate = 5.f;
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


void StratHeavyMove(Enemy& enemy, sf::Vector2f shipPosition, const float& deltaTime) {
	// Système de tire par rafale
	Shoot(enemy, deltaTime);
}


std::vector<Enemy>::iterator StratBomberMove(std::vector<Enemy>::iterator& enemyIt, Ship& ship, std::vector<Enemy>& allEnemy, const float& deltaTime) {
	// L'ennemi ce dirige sur la position du vaiseau
	MoveToPoint((*enemyIt).shape, ship.ship.getPosition(), (*enemyIt).speed, false, deltaTime);

	// -------------- TODO -------------- //
	// déplacement subite lorsque le joueur fait face à l'ennemie
	
	if (UpdateEnemy(ship, (*enemyIt).shape)) {
		std::cout << "BOUMMMMMM \n";
		return allEnemy.erase(enemyIt);

		// -------------- TODO -------------- //
		// infoShip.livePoints -= (*enemyIt).damage;
	}

	return enemyIt;
}

void StratTorpedoLuncherMove(Enemy& enemy, std::map<int, Torpedo>& enemyTorpedo, sf::Vector2f shipPosition, const float& deltaTime) {

	std::map<int, Torpedo>::iterator it = enemyTorpedo.find(enemy.torpedoKey);

	if (it == enemyTorpedo.end()) {
		enemy.rate -= deltaTime;
		if (enemy.rate < 0) {
			enemy.torpedoKey = CreatNewTorpedo(enemyTorpedo, enemy.shape.getPosition());
			enemy.rate = enemy.defaultRate;
		}
	}
}


void Shoot(Enemy& enemy, const float& deltaTime) {
	enemy.rate -= deltaTime;

	if (enemy.rate < 0) {
		enemy.semiRate -= deltaTime;

		if (enemy.semiRate < 0) {

			if (enemy.nbBulletSemi > 0) {

				std::cout << "shoot" << std::endl;

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


bool UpdateEnemy(Ship& ship, sf::CircleShape origine) {
	sf::Vector2f shipPos = ship.ship.getPosition();
	float distance = std::sqrt(pow(shipPos.x - origine.getPosition().x, 2) + pow(shipPos.y - origine.getPosition().y, 2));

	if (distance <= origine.getRadius() + ship.ship.getRadius()) {
		return true;
	}

	return false;
}