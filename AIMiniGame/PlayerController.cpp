#include "PlayerController.hpp"

void PlayerController::UpdatePlayerLooks()
{
	if (KeyA.pressed()) pos.x -= speed * Scene::DeltaTime();
	else if (KeyD.pressed()) pos.x += speed * Scene::DeltaTime();
	else if (KeyW.pressed()) pos.y -= speed * Scene::DeltaTime();
	else if (KeyS.pressed()) pos.y += speed * Scene::DeltaTime();

	Draw();
}

void PlayerController::UpdateHp()
{
	hp--;
}

void PlayerController:: Update(Array<Cheese>& cheeses, Array<Enemy>& enemys,Array<CaptureMouthItem>& captureItems
							  ,Effect& effect)
{
	HandleEnemyCollision(enemys);
	HandleCheeseCollision(cheeses,effect);
	HandleCaptureItemCollision(captureItems);

	hit.draw(ColorF{ 1,0,0 });
	UpdatePlayerLooks();

	placementItemManager.Update(enemys,effect);
	scoreController.Update();
	playerStatusManager.Update();
}

void PlayerController::Draw()
{
	if (!playerStatusManager.GetActiveStatus(StatusType::Invincible))
	{
		if (blinkElapsedTime != 0) blinkElapsedTime = 0;
		hit.center = pos;
		looks.drawAt(pos);
	}
	else
	{
		BlinkDraw();
	}
}

void PlayerController::HandleCheeseCollision(Array<Cheese>& cheeses,Effect& effect)
{
	int32 cheesePoint{ 0 };
	if (hitDetecter.DetectHitCheese(cheeses, cheesePoint,effect))
	{
		scoreController.UpdateScore(cheesePoint);
	}
}

void PlayerController::HandleEnemyCollision(Array<Enemy>& enemys)
{
	if (hitDetecter.DetectHitEnemy(enemys) && !playerStatusManager.GetActiveStatus(StatusType::Invincible))
	{
		UpdateHp();
		playerStatusManager.ActivateFlag(StatusType::Invincible);
	}
	hpUIManager.Update();
}

void PlayerController::HandleCaptureItemCollision(Array<CaptureMouthItem>& captureItems)
{
	if(hitDetecter.DetectHitCaptureitem(captureItems))
	{
		placementItemManager.AddCaptureItem();
	}
}

void PlayerController::BlinkDraw()
{
	 blinkElapsedTime += Scene::DeltaTime();
	 //偶数の時に描画　= 奇数の時描画しない
	 //blinkDuration倍の時に描画する
	 
	 if (static_cast<int32>(blinkElapsedTime / blinkDuration) % 2 == 0)
	 {
		 hit.center = pos;
		 looks.drawAt(pos);
	 }
}

