#pragma once
#include <Siv3D.hpp>

class ScoreController
{
public:
	void UpdateScore(int32 cheesePoint);
	void Update();
	int32 GetCurrentScore() { return score; };
	void Reset();
private:
	void DrawScoreText() const;
	int32 score{ 0 };
	Font font{ 80 };
};
