#include "ResultUIManager.hpp"

void ResultUIManager::GameOverUI()
{
	content = U"GAME OVER";
	fontPos = Vec2{ Scene::Width() / 2,Scene::Height() / 2 };
	helperUIManager.ResetAlpha();
}

void ResultUIManager::StageClearUI()
{
	content = U"STAGE CLEAR!!";
	fontPos = Vec2{ Scene::Width() / 2, Scene::Height() / 2 };
	helperUIManager.ResetAlpha();
}

void ResultUIManager::WaitStateUI()
{
	content = U"PRESS ENTER KEY!!";
	fontPos = Vec2{ Scene::Width() / 2, Scene::Height() / 2 };
	helperUIManager.ResetAlpha();
}

void ResultUIManager::Draw(ResultType resultType)
{
	switch (resultType)
	{
	case ResultType::None:
		helperUIManager.UpdateAlpha();
		break;
	case ResultType::GameOver:
	case ResultType::StageClear:
		break;
	}

	font(content).drawAt(fontPos, ColorF{ 1.0, 1.0, 1.0, helperUIManager.GetAlpha() });
}

//void ResultUIManager::Update()
//{
//	Draw();
//}
