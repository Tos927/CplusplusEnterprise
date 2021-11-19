
#include "GeneratorLevel.h"
#include "ShipBehaviour.h"
#include "EnemiesBehaviour.h"
#include <iostream>
#include <vector>


/// <summary>
/// Créer de façon aléatoire un nouvel ensemble de planète de nombre et taille prédéfinie. Une marge de sécurité peut être ajoutée entre chaques planètes.
/// </summary>
/// <returns>Retourne un nouveau tableau contenant les différentes planètes.</returns>
std::vector<Planet> NewLevel(int planetMax, int planetMin, float radiusMax, float radiusMin, float security, int bomberMax, int bomberMin, int torpedoMax, int torpedoMin, int heavyMax, int heavyMin, std::vector<Enemy>& allEnemies) {

	int planets = ((double)rand() / RAND_MAX) * (double(planetMax) - double(planetMin)) + planetMin;
	int bomberNbr = ((double)rand() / RAND_MAX) * (double(bomberMax) - double(bomberMin)) + planetMin;
	int torpedoNbr = ((double)rand() / RAND_MAX) * (double(torpedoMax) - double(torpedoMin)) + planetMin;
	int heavyNbr = ((double)rand() / RAND_MAX) * (double(heavyMax) - double(heavyMin)) + planetMin;
	std::vector<Planet> allPlanets;
	std::cout << "--- NOUVEAU NIVEAU --- Nombre de planet :" << planets << std::endl;

	float posX = 0;
	float posY = 0;
	float radius = 0;

	for (int i = 0; i < planets; i++) {
		Planet newPlanet;
		while (!newPlanet.isValide) {
			// initialisation aléatoire des valeur
			radius = ((double)rand() / RAND_MAX) * (double(radiusMax) - double(radiusMin)) + double(radiusMin);
			newPlanet.radius = radius;
			newPlanet.pShape.setOrigin(radius, radius);
			posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
			posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
			newPlanet.position = { posX, posY };

			
			// vérification
			bool collideWithOther = false;
			for (Planet p : allPlanets) {
				float dist = std::sqrt(pow(p.position.x - newPlanet.position.x, 2) + pow(p.position.y - newPlanet.position.y, 2));

				std::cout << "Distance : " << dist << std::endl;
				std::cout << "Nouvelle " << newPlanet.position.x << "   " << newPlanet.position.y << "        Ancienne " << p.position.x << "    " << p.position.y << std::endl;

				if (dist <= (radius + security) + (p.radius + security)) {
					std::cout << "Touche !"<< std::endl;
					collideWithOther = true;
				}
			}

			if (collideWithOther) {
				continue;
			}

			newPlanet.isValide = true;
			newPlanet.pShape.setPosition(newPlanet.position);
			newPlanet.pShape.setRadius(newPlanet.radius);
			
		}
		allPlanets.push_back(newPlanet);
		std::cout << "Succet !" << std::endl;
	}
	for (int i = 0; i < heavyNbr; i++)
	{
		CreatNewEnemy(allEnemies, sf::Vector2f(posX + radius + 10, posY + radius), 1);
	}
	for (int i = 0; i < bomberNbr; i++)
	{
		CreatNewEnemy(allEnemies, sf::Vector2f(posX + radius, posY + radius + 20), 2);
	}
	for (int i = 0; i < torpedoNbr; i++)
	{
		CreatNewEnemy(allEnemies, sf::Vector2f(posX + radius + 15, posY + radius + 15), 3);
	}

	return allPlanets;
}