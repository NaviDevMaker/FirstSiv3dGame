#pragma once
#include <Siv3D.hpp>
#include "PlayerController.hpp"
#include "ItemManager.hpp"
#include "EnemyManager.hpp"
#include "SetEnvironment.hpp"
#include "BattleResultController.hpp"
#include "StageManager.hpp"
#include "InputUtility.hpp"
#include "StageProgressChecker.hpp"
#include "StageInfoUIManager.hpp"

class GameManager
{
public:
	GameManager();
	
   void	Update(Effect& effect);
   void Setup();
private:
	PlayerController player;
	ItemManager itemManager;
	EnemyManager enemyManager;
	SetEnvironment environment;
	BattleResultController battleResultController;
	StageManager stageManager;
	StageProgressChecker stageProgressChecker;
	StageInfoUIManager stageUIInfoUIManager;

	void UpdatePlayer(Effect& effect);
	void UpdateEnemy(Effect& effect);
	void UpdateItem();

	void OnBattleState(Effect& effect);
	void OnWaitState();
	void OnResultState(Effect& effect);

	void ApplyStageInfo();

	bool TryHandleStageClear();
	bool TryStartBattleFromWait();
	bool TryRestartFromResult(Effect& effect);

	void Reset(Effect& effect);
};
