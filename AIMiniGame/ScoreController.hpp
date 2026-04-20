#pragma once
#include <Siv3D.hpp>

class ScoreController
{
public:
	void UpdateScore(int cheesePoint);
	void Update();
private:
	void DrawScoreText() const;
	int score{ 0 };
	Font font{ 80 };
};
