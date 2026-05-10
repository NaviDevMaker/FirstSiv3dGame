#pragma once
#include <Siv3D.hpp>

class StageInfoUIManager
{
public:
	void Update() const;
	void UpdateStageNumber();
	void ApplyStageInfo(int32 targetScore);
private:
	void Draw() const;
	Font stageFont{ 60 };
	Font targetScoreFont{ 60 };
	int32 stageNumber{ 1 };
	int32 targetScore{ 0 };
};
