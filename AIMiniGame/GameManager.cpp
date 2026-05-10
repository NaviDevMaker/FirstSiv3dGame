#include "GameManager.hpp"
#include "DebugLogClass.hpp"

class StageData;
struct ItemInfo;
struct StageEnemyInfo;

GameManager::GameManager()
	:player{ U"😺"_emoji }
	, enemyManager{ this->player }
{
	// battleResultController は GameManager クラスのメンバー変数。
	// メンバー変数はローカル変数ではないため、
	// [&battleResultController] のように個別キャプチャはできない。
	// ラムダ内でメンバー変数を使いたい場合は、
	// [this] にすることで、ラムダ内から
	// this->battleResultController にアクセスできる。

	player.RegisterOnDead([this]()
	{
		//Print << U"OnDead called";
		battleResultController.GameOver();
		battleResultController.ChangeState(BattleState::Result);
		battleResultController.ChangeResultType(ResultType::GameOver);
		//Print << U"GameOver finished";
	});

	/*player.RegisterOnStageClear([this]()
	{
		stageManager.ClearStage();
	});*/

}

//Gameの一番最初にやる処理
void GameManager::Setup()
{
	battleResultController.WaitState();
	ApplyStageInfo();
}

//drawAtとdrawの違いメモ
//drawはテクスチャの左上基準、drawAtは中心が基準
void GameManager::Update(Effect& effect)
{
	DebugLogClass::DebugLog(U"{}"_fmt(static_cast<int32>(battleResultController.GetCurrentState())));
	environment.Update(battleResultController.GetCurrentState(),battleResultController.GetCurrentType());
	switch(battleResultController.GetCurrentState())
	{
		case BattleState::Wait:
			OnWaitState();
			break;
		case BattleState::Battle:
			OnBattleState(effect);
			break;
		case BattleState::Result:
			OnResultState(effect);
			break;
	}
}

void GameManager::OnWaitState()
{
	if(TryStartBattleFromWait()) return;
	battleResultController.Update();
}

void GameManager::OnBattleState(Effect& effect)
{
	if (TryHandleStageClear()) return;
	UpdateItem();
	UpdatePlayer(effect);
	UpdateEnemy(effect);
	stageUIInfoUIManager.Update();
}

void GameManager::OnResultState(Effect& effect)
{
	if (TryRestartFromResult(effect)) return;
	battleResultController.Update();
}

void GameManager::ApplyStageInfo()
{
	const StageData& currentStageData = *stageManager.GetNextStageData();
	const StageEnemyInfo& stageEnemyInfo = currentStageData.GetStageEnemyInfo();
	const ItemInfo& cheeseItemInfo = currentStageData.GetCheeseItemInfo();
	const ItemInfo& captureItemInfo = currentStageData.GetCaptureItemInfo();
	enemyManager.ApplyStageInfo(stageEnemyInfo);
	itemManager.ApplyStageInfo(cheeseItemInfo,captureItemInfo);
	environment.ApplyStageInfo(currentStageData.GetBattleTexture());
	stageProgressChecker.ApplyStageInfo(currentStageData.GetTargetScore());
	stageUIInfoUIManager.ApplyStageInfo(currentStageData.GetTargetScore());
}

void GameManager::UpdatePlayer(Effect& effect)
{
	auto& cheeses = itemManager.GetCheeses();
	auto& enemys = enemyManager.GetEnemies();
	auto& captureItems = itemManager.GetCaptureItems();
	player.Update(cheeses, enemys, captureItems, effect);
}

//敵系のUpdate処理
void GameManager::UpdateEnemy(Effect& effect)
{
	enemyManager.Update(effect);
}

//アイテム系のUpdate処理
void GameManager::UpdateItem()
{
	itemManager.Update();
}

//判定＋状態遷移＋早期リターン　まで含む"1つのイベント処理"なのでわけるべき
bool GameManager::TryHandleStageClear()
{
	if (stageProgressChecker.IsClearedStage(player.GetCurrentScore()))
	{
		stageManager.ClearStage(); //StageDataの更新
		battleResultController.StageClear();
		battleResultController.ChangeState(BattleState::Result);
		battleResultController.ChangeResultType(ResultType::StageClear);
		stageUIInfoUIManager.UpdateStageNumber();
		return true;
	}

	return false;
}

bool GameManager::TryStartBattleFromWait()
{
	if (!InputUtility::IsConfirmPressed()) return false;
	battleResultController.ChangeState(BattleState::Battle);
	return true;
}

bool GameManager::TryRestartFromResult(Effect& effect)
{
	if (!InputUtility::IsConfirmPressed()) return false;
	Reset(effect);
	ApplyStageInfo();
	battleResultController.ChangeState(BattleState::Wait);
	battleResultController.ChangeResultType(ResultType::None);
	battleResultController.WaitState();
	return true;
}

//ステージ開始時にScoreやHp、などを初期値にリセットする
void GameManager::Reset(Effect& effect)
{
	effect.clear();
	player.Reset();
	itemManager.Reset();
	enemyManager.Reset();
}
