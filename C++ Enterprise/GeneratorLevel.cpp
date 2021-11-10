
#include "GeneratorLevel.h"
#include <iostream>
#include <vector>

std::vector<Planet> NewLevel(int planetMax, int planetMin, float radiusMax, float radiusMin, float security) {
	// int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;

	int planets = ((double)rand() / RAND_MAX) * (double(planetMax) - double(planetMin)) + planetMin;
	std::vector<Planet> allPlanets;
	std::cout << "Nombre de planet :" << planets << std::endl;

	for (int i = 0; i < planets; i++) {
		Planet newPlanet;
		while (!newPlanet.isValide) {
			// initialisation aléatoire des valeur
			float radius = ((double)rand() / RAND_MAX) * (double(radiusMax) - double(radiusMin)) + double(radiusMin);
			newPlanet.radius = radius;
			newPlanet.pShape.setOrigin(radius, radius);
			float posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
			float posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
			newPlanet.position = { posX, posY };

			
			// vérification
			bool collideWithOther = false;
			for (Planet p : allPlanets) {
				float dist = std::sqrt(p.position.x * newPlanet.position.x + p.position.y * newPlanet.position.y);
				if (dist + (radius + security) + (p.radius + security) <= 0) {
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
	}

	return allPlanets;
}