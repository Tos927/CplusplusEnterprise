
#include "GeneratorLevel.h"
#include <iostream>
#include <vector>

std::vector<Planet> NewLevel(int planetMax, int planetMin, float radiusMax, float radiusMin, float security) {

	int planets = ((double)rand() / RAND_MAX) * (double(planetMax) - double(planetMin)) + planetMin;
	std::vector<Planet> allPlanets;
	std::cout << "--- NOUVEAU NIVEAU --- Nombre de planet :" << planets << std::endl;

	for (int i = 0; i < planets; i++) {
		Planet newPlanet;
		while (!newPlanet.isValide) {
			// initialisation al�atoire des valeur
			float radius = ((double)rand() / RAND_MAX) * (double(radiusMax) - double(radiusMin)) + double(radiusMin);
			newPlanet.radius = radius;
			newPlanet.pShape.setOrigin(radius, radius);
			float posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
			float posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
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
			
		}
		allPlanets.push_back(newPlanet);
		std::cout << "Succet !" << std::endl;
	}

	return allPlanets;
}