#include "StageManager.hpp"
#include "DebugLogClass.hpp"


StageManager::StageManager()
{
	InitializeStageDatas();
	currentStageData = stageDatas[0];
}

void StageManager::ClearStage()
{
	UpdateCurrentStage();
}

void StageManager::UpdateCurrentStage()
{
	if (stageDatas.isEmpty()) return;
	if ((currentStageNumber + 1) >= static_cast<int32>(stageDatas.size())) return;
	currentStageNumber++;
	currentStageData = stageDatas[currentStageNumber];
	DebugLogClass::DebugLog(U"currentStageNumber: {}"_fmt(currentStageNumber));
}

void StageManager::InitializeStageDatas()
{
	stageDatas << StageData{ Texture{U"background_Stage1.png"}
							,StageEnemyInfo{5,Array<EnemyType>{EnemyType::Weak}
							,Array<EnemyMoveType>{EnemyMoveType::RightAngle}}
							,ItemInfo{0,2}
							,ItemInfo{0,3},30 };

	stageDatas << StageData{ Texture{U"background_Stage2.png"}
							,StageEnemyInfo{5,Array<EnemyType>{EnemyType::Weak,EnemyType::Normal}
							,Array<EnemyMoveType>{EnemyMoveType::RightAngle}}
							,ItemInfo{0,2}
							,ItemInfo{0,3},60 };

	stageDatas << StageData{ Texture{U"background_Stage3.png"}
							,StageEnemyInfo{5,Array<EnemyType>{EnemyType::Weak,EnemyType::Normal,EnemyType::Strong}
							,Array<EnemyMoveType>{EnemyMoveType::RightAngle}}
							,ItemInfo{0,4}
							,ItemInfo{0,3},60 };
}


