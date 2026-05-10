#include "PlayerController.hpp"
#include "PlayerHitEffect.hpp"
#include "InputUtility.hpp"

void PlayerController::UpdatePlayerLooks()
{
	if (InputUtility::IsMoveLeft()) pos.x -= speed * Scene::DeltaTime();
	else if (InputUtility::IsMoveRight()) pos.x += speed * Scene::DeltaTime();
	else if (InputUtility::IsMoveUp()) pos.y -= speed * Scene::DeltaTime();
	else if (InputUtility::IsMoveDown()) pos.y += speed * Scene::DeltaTime();

	Draw();
}

void PlayerController::UpdateHp()
{
	hp--;
	if (hp <= 0)
	{
		OnPlayerDead.Invoke();
	}
}

void PlayerController::Reset()
{
	ResetPlayerStatus();
	scoreController.Reset();
	placementItemManager.Reset();
}

void PlayerController::ResetPlayerStatus()
{
	hp = initialHp;
	playerStatusManager.Reset();
	blinkElapsedTime = 0;
	pos = Vec2{ 0,0 };
}

void PlayerController:: Update(Array<Cheese>& cheeses, Array<Enemy>& enemys,Array<CaptureMouthItem>& captureItems
							  ,Effect& effect)
{
	HandleEnemyCollision(enemys,effect);
	HandleCheeseCollision(cheeses,effect);
	HandleCaptureItemCollision(captureItems,effect);

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

void PlayerController::HandleEnemyCollision(Array<Enemy>& enemys,Effect& effect)
{
	if (hitDetecter.DetectHitEnemy(enemys) && !playerStatusManager.GetActiveStatus(StatusType::Invincible))
	{
		UpdateHp();
		effect.add<PlayerHitEffect>(*this);
		playerStatusManager.ActivateFlag(StatusType::Invincible);
	}
	hpUIManager.Update();
}

void PlayerController::HandleCaptureItemCollision(Array<CaptureMouthItem>& captureItems,Effect& effect)
{
	if(hitDetecter.DetectHitCaptureitem(captureItems,effect))
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

