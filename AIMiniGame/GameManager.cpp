#include "GameManager.hpp"

//drawAtとdrawの違いメモ
//drawはテクスチャの左上基準、drawAtは中心が基準
void GameManager::Update(Effect& effect)
{
	environment.Update();
	itemManager.Update();
	auto& cheeses = itemManager.GetCheeses();
	auto& enemys = enemyManager.GetEnemies();
	auto& captureItems = itemManager.GetCaptureIterms();
	player.Update(cheeses,enemys,captureItems,effect);
	enemyManager.Update();
}
