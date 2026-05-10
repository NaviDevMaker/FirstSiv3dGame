#pragma once
#include <Siv3D.hpp>
#include "StageData.hpp"
#include "StageEnemyInfo.hpp"
#include "ItemInfo.hpp"
#include "EnemyType.hpp"
#include "EnemyMoveType.hpp"

//現在のステージの情報を持ってたり次のステージに進める
class StageManager
{
public:
	StageManager();
	void ClearStage();

	//return nullのようなものはないからポインターを返すようにする
	//今回の場合は基本存在は確定だから適してないかも
    const StageData* GetNextStageData() const
	{
		if (currentStageData.has_value()) return &currentStageData.value();
		return nullptr;
	};
private:
	int32 currentStageNumber{0};

	Array<StageData> stageDatas;

	//引数なしのデフォルトコントラクタがないものでも　「値が存在するかもしれないし、存在しないかもしれない」
	//を表す型 Optionalによって可能
	Optional<StageData> currentStageData;
	void UpdateCurrentStage();
	void InitializeStageDatas();
};
