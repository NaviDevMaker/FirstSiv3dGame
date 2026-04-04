#pragma once
#include <Siv3D.hpp>
#include "PlayerController.hpp"
class HitDetecter
{
public:
	HitDetecter(PlayerController& player);
private:
	PlayerController& player;
	void DetectHitCheese() const;
	void DetectHitEnemy() const;
};
