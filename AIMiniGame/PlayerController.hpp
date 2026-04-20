#pragma once
//pragma once の意味
//を書くと
//👉同じヘッダが何回 #include されても
//👉最初の1回だけ有効になる
#include <Siv3D.hpp>
#include "HitDetecter.hpp"
#include "ScoreController.hpp"
#include "HpUIManager.hpp"
#include "PlayerStatusManager.hpp"
#include "PlacementItemManager.hpp"

class Cheese;
class CaptureMouthItem;
class Enemy;
class PlayerController
{
public:
	PlayerController(const Emoji& emoji)
		: looks{ Texture{emoji} }
		, hitDetecter(*this)
		, hit{ Circle{pos,looks.width() / 2} }
		,hpUIManager{hp}
		,placementItemManager{*this}
	{

	}
  	Texture looks;
	Vec2 pos{0,0};
    const double speed{500};
	void Update(Array<Cheese>& cheeses,Array<Enemy>& enemys,Array<CaptureMouthItem>& captureItems
				,Effect& effect);
	Circle hit;
private:
	ScoreController scoreController;
	HitDetecter hitDetecter;
	HpUIManager hpUIManager;
	PlayerStatusManager playerStatusManager;
	PlacementItemManager placementItemManager;

	void UpdatePlayerLooks();//見た目の変更
	void UpdateHp();
	void Draw();
	void BlinkDraw();
	void HandleCheeseCollision(Array<Cheese>& cheeses,Effect& effect);
	void HandleEnemyCollision(Array<Enemy>& enemys);
	void HandleCaptureItemCollision(Array<CaptureMouthItem>& captureItems);
	int hp{ 5 };
	static constexpr double blinkDuration{ 0.05 };
	double blinkElapsedTime{ 0 };
};
