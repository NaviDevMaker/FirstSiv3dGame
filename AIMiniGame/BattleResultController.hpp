#pragma once
#include <Siv3D.hpp>
#include "ResultUIManager.hpp"
#include "BattleState.hpp"
#include "ResultType.hpp"

class BattleResultController
{
public:
	void GameOver();
	void StageClear();
	void WaitState();
	BattleState GetCurrentState() { return currentState; }
	ResultType GetCurrentType() { return currentType; }
	void Update();
	void ChangeState(BattleState nextState);
	void ChangeResultType(ResultType nextType);
private:
	ResultUIManager resultUIManager;
	BattleState currentState{BattleState::Wait};
	ResultType currentType{ ResultType::None };
};
