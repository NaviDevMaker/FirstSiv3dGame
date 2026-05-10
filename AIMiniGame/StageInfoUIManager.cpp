#include "StageInfoUIManager.hpp"

void StageInfoUIManager::Update() const
{
	Draw();
}

void StageInfoUIManager::UpdateStageNumber()
{
	stageNumber++;
}

void StageInfoUIManager::ApplyStageInfo(int32 targetScore)
{
	this->targetScore = targetScore;
}

void StageInfoUIManager::Draw() const
{
	const Vec2 stageFontPos{ Scene::Width() * 0.72, 50 };
	const Vec2 targetScoreFontPos{ Scene::Width() * 0.52, 120 };
	stageFont(U"STAGE{}"_fmt(stageNumber)).draw(stageFontPos);
	targetScoreFont(U"TARGETSCORE:{}"_fmt(targetScore)).draw(targetScoreFontPos);
}
