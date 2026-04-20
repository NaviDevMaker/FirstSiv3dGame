#include "ScoreController.hpp"


void ScoreController::UpdateScore(int cheesePoint)
{
	score += cheesePoint;
	/*Print << score;*/
	
}

void ScoreController::DrawScoreText() const
{
	font(U"Score:{}"_fmt(score)).draw(50, 50);
}

void ScoreController::Update()
{
	DrawScoreText();
}
