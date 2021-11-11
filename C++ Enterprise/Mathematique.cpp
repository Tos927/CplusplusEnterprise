
#include "Mathematique.h"

#define PI 3.141592653589793238463


sf::Vector2f Interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor) {
	if (factor > 1.f) {
		factor = 1.f;
	}

	else if (factor < 0.f) {
		factor = 0.f;
	}

	return pointA + (pointB - pointA) * factor;
}


float DegToRad(const float& angleInDeg) {
	float rad = angleInDeg / 180.0f * float(PI);
	return rad;
}


sf::Vector2f Direction(const float& angleInDeg) {
	sf::Vector2f dir;
	dir.x = cos(DegToRad(angleInDeg));
	dir.y = sin(DegToRad(angleInDeg));
	return dir;
}


float Distance(const sf::Vector2f& pointA, const sf::Vector2f& pointB) {
	float distance = std::sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
	return distance;
}