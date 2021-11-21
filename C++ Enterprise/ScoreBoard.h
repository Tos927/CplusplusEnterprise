#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ShipBehaviour.h"
#include "GeneratorLevel.h"
#include "EnemiesBehaviour.h"

struct Points
{
	int levelMultiplicator = 1;
	int totalPoints = 0;
};

void UpdateScoreBoard(sf::Text ScoreBoardText, Points& points);