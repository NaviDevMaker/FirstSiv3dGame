#pragma once
#include <Siv3D.hpp>
#include "BattleState.hpp"
#include "ResultType.hpp"
class SetEnvironment
{
public:
    void Update(BattleState currentBattleState,ResultType resultType);
	void ApplyStageInfo(const Texture& battleTexture);
private:
	//Appフォルダからのpath
	Texture battle;
	const Texture gameOver{U"background_GAMEOVER.png"};
	const Texture stageClear{ U"background_STAGECLEAR.png" };
	const Texture wait{U"background_WAIT.png"};
	void Draw(BattleState currentBattleState, ResultType resultType);
};
