#include "GeneratorLevel.h"
#include <iostream>
#include <vector>

/// <summary>
/// Cr�er de fa�on al�atoire un nouvel ensemble de plan�te de nombre et taille pr�d�finie. Une marge de s�curit� peut �tre ajout�e entre chaques plan�tes.
/// </summary>
/// <returns>Retourne un nouveau tableau contenant les diff�rentes plan�tes.</returns>
std::vector<Planet> NewLevel(int planetMax, int planetMin, float radiusMax, float radiusMin, float security, int bomberMax, int bomberMin, int torpedoMax, int torpedoMin, int heavyMax, int heavyMin, std::vector<Enemy>& allEnemies) {

	int planets = ((double)rand() / RAND_MAX) * (double(planetMax) - double(planetMin)) + planetMin;
	int bomberNbr = ((double)rand() / RAND_MAX) * (double(bomberMax) - double(bomberMin)) + bomberMin;
	int torpedoNbr = ((double)rand() / RAND_MAX) * (double(torpedoMax) - double(torpedoMin)) + torpedoMin;
	int heavyNbr = ((double)rand() / RAND_MAX) * (double(heavyMax) - double(heavyMin)) + heavyMin;
	std::vector<Planet> allPlanets;
	std::cout << "--- NOUVEAU NIVEAU --- Nombre de planet :" << planets << std::endl;

	float posX = 0;
	float posY = 0;
	float radius = 0;

	for (int i = 0; i < planets; i++) {
		Planet newPlanet;
		while (!newPlanet.isValide) {
			// initialisation al�atoire des valeur
			radius = ((double)rand() / RAND_MAX) * (double(radiusMax) - double(radiusMin)) + double(radiusMin);
			newPlanet.radius = radius;
			newPlanet.pShape.setOrigin(radius, radius);
			posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
			posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
			newPlanet.position = { posX, posY };

			
			// v�rification
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
			newPlanet.pShape.setFillColor(sf::Color::Color(211, 211, 211));
			
		}
		allPlanets.push_back(newPlanet);
		std::cout << "Succet !" << std::endl;
	}
	for (int j = 0; j < heavyNbr; j++)
	{
		posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
		posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
		CreatNewEnemy(allEnemies, sf::Vector2f(posX + radius + 10, posY + radius), 1);
		std::cout << "ennemy create" << std::endl;
	}
	for (int k = 0; k < bomberNbr; k++)
	{
		posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
		posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
		CreatNewEnemy(allEnemies, sf::Vector2f(posX + radius, posY + radius + 20), 2);
		std::cout << "ennemy create" << std::endl;
	}
	for (int l = 0; l < torpedoNbr; l++)
	{
		posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
		posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
		CreatNewEnemy(allEnemies, sf::Vector2f(posX + radius + 15, posY + radius + 15), 3);
		std::cout << "ennemy create" << std::endl;
	}
	return allPlanets;
}