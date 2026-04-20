#pragma once
#include <Siv3D.hpp>
#include "AstarPathFinding.hpp"
#include <functional>

class PlayerController;
class Enemy
{
public:
	Enemy(int32 speed, ColorF colorF, Vec2 spawnPos, PlayerController& player);
		
   void	Update();
private:
	
	int32 speed;
	Texture looks;//見た目
	ColorF colorF;//キャラの色
	Vec2 pos;
	std::reference_wrapper<PlayerController> player;
	AstarPathFinding astar;
    void Draw(Vec2& nor);
    void UpdatePosition(Vec2& nor);
	//bool DetectPlayerMove();
	//Vec2 previousPos;
	Array<Vec2> path;
	int pathIndex{ 0 };
	static constexpr double chaseTime{ 0.05 };
	double elapsedTime{0};

	void Rotate(Vec2& nor);
	int rlDir{ -1 };
	double angle{0};
	bool isMirror{ false };
	bool isFliped{ false };
public:
	Circle hit;//当たり判定
};
