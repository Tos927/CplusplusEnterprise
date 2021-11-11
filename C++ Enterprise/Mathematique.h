#pragma once
#include <SFML/Graphics.hpp>

sf::Vector2f Interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor);
float Distance(const sf::Vector2f& pointA, const sf::Vector2f& pointB);
sf::Vector2f Direction(const float& angleInDeg);
float DegToRad(const float& angleInDeg);