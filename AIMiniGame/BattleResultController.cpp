#include "BattleResultController.hpp"

void BattleResultController::GameOver()
{
	//currentState = BattleState::Result;
	resultUIManager.GameOverUI();
}

void BattleResultController::StageClear()
{
	resultUIManager.StageClearUI();
}

void BattleResultController::WaitState()
{
	resultUIManager.WaitStateUI();
}

void BattleResultController::ChangeState(BattleState nextState)
{
	currentState = nextState;
}

void BattleResultController::ChangeResultType(ResultType nextType)
{
	currentType = nextType;
}

void BattleResultController::Update()
{
	switch (currentState)
	{
		case BattleState::Wait:
			resultUIManager.Draw(currentType);
			break;
		case BattleState::Battle:
			break;
		case BattleState::Result:
			resultUIManager.Draw(currentType);
			break;
	}
}


