#pragma once
#include <Siv3D.hpp>

//class PlayerController;
class StageProgressChecker
{
public:
	/*StageProgressChecker(PlayerController& player)
		:player{player}{ }*/

	//多分int
	bool IsClearedStage(int32 score);
	void ApplyStageInfo(int32 targetScore) { this->targetScore = targetScore; };
private:
	//const PlayerController& player;
	int32 targetScore;
};
