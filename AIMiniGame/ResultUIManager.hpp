#pragma once
#include <Siv3D.hpp>
#include "HelperUIManager.hpp"
#include "ResultType.hpp"

class ResultUIManager
{
public:
	void GameOverUI();
	void StageClearUI();
	void WaitStateUI();
	void Draw(ResultType resultType);
	//void Update();
private:
	Font font{ 120 };
	String content{U""};
	Vec2 fontPos;
	HelperUIManager helperUIManager;
};
