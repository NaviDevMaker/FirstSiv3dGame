#include "SetEnvironment.hpp"

void SetEnvironment::Draw(BattleState currentBattleState, ResultType resultType)
{
	
	switch (currentBattleState)
	{
	    case BattleState::Wait:
			wait.resized(Scene::Size()).draw();
			break;
		case BattleState::Battle:
			battle.resized(Scene::Size()).draw();
			break;
		case BattleState::Result:
			if (resultType == ResultType::GameOver) gameOver.resized(Scene::Size()).draw();
			else if (resultType == ResultType::StageClear) stageClear.resized(Scene::Size()).draw();
			break;
	}	
}

void SetEnvironment::Update(BattleState currentBattleState, ResultType resultType)
{
	Draw(currentBattleState,resultType);
}

//Battle画面のTextuteの設定
void SetEnvironment::ApplyStageInfo(const Texture& battleTexture)
{
	battle = battleTexture;
}
