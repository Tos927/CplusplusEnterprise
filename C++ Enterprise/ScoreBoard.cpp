#include "ScoreBoard.h"

void UpdateScoreBoard(sf::Text& ScoreBoardText, Points& points) 
{
	ScoreBoardText.setString("Score : " + std::to_string(points.totalPoints));
}