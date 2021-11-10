
#include "GeneratorLevel.h"
#include <iostream>
#include <vector>

std::vector<Planet> NewLevel() {
	// int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;

	int planets = ((double)rand() / RAND_MAX) * (double(MAX_PLANET) - double(MIN_PLANET)) + MIN_PLANET;
	std::vector<Planet> allPlanets;
	std::cout << "Nombre de planet :" << planets << std::endl;

	for (int i = 0; i < planets; i++) {
		Planet newPlanet;
		while (!newPlanet.isValide) {
			// initialisation aléatoire des valeur
			float radius = ((double)rand() / RAND_MAX) * (double(MAX_RADIUS) - double(MIN_RADIUS)) + double(MIN_RADIUS);
			newPlanet.radius = radius;
			newPlanet.pShape.setOrigin(radius, radius);
			float posX = ((double)rand() / RAND_MAX) * ((double(WIDTH) - double(radius)) - double(radius)) + double(radius);
			float posY = ((double)rand() / RAND_MAX) * ((double(HEIGHT) - double(radius)) - double(radius)) + double(radius);
			newPlanet.position = { posX, posY };

			
			// vérification
			bool collideWithOther = false;
			for (Planet p : allPlanets) {
				float dist = std::sqrt(p.position.x * newPlanet.position.x + p.position.y * newPlanet.position.y);
				if (dist + (radius + SECURITY_RADIUS) + (p.radius + SECURITY_RADIUS) <= 0) {
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