#pragma once
#include <Siv3D.hpp>
#include "PlayerController.hpp"
#include "ItemManager.hpp"
#include "EnemyManager.hpp"
#include "SetEnvironment.hpp"

class GameManager
{
public:
	GameManager()
		:player{U"😺"_emoji }
		,enemyManager{this->player}
	{

	}
   void	Update(Effect& effect);
private:
	PlayerController player;
	ItemManager itemManager;
	EnemyManager enemyManager;
	SetEnvironment environment;
};
