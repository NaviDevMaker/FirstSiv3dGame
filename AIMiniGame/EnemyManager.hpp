#pragma once
#include <Siv3D.hpp>
#include <unordered_map>
#include "Enemy.hpp"
#include "EnemyType.hpp"
#include "EnemyMoveType.hpp"
#include "StageEnemyInfo.hpp"

struct PendingSpawn
{
	double effectTime;
	double elapsedTime{ 0 };
	int32 speed;
	Vec2 spawnPos;
	ColorF targetColor;
	bool isDiagonal;
};

class PlayerController;

class EnemyManager
{
public:
	EnemyManager(PlayerController& player)
		:player{ player }
	{

	}
  void	Update(Effect& effect);
  void ApplyStageInfo(const StageEnemyInfo& stageEnemyInfo);
  Array<Enemy>& GetEnemies()  { return enemys;}
  void Reset();
private:
	Array<Enemy> enemys;//今回は自分で生成して追加、削除するから&（参照）じゃなくていい
	Array<PendingSpawn> pendingQueue;
	PlayerController& player;
	std::unordered_map<EnemyType, ColorF> colorMap =
	{
		{EnemyType::Weak,ColorF{0,1,0}},
		{EnemyType::Normal,ColorF{0,0,1}},
		{EnemyType::Strong,ColorF{1,0,0}}
	};

	std::unordered_map<EnemyType, int32> speedMap
	{
		{EnemyType::Weak,75},
		{EnemyType::Normal,100},
		{EnemyType::Strong,150}
	};

	void QueueEnemySpawn(Effect& effect);
	void EnemySpawn();
	ColorF GetRandomEnemyColor(EnemyType type) const;
	bool GetIsDiagonal() const;
	EnemyType GetRandomEnemyType() const;
	int32 GetRandomEnemySpeed(EnemyType type) const;

	//constexprはグローバル変数（クラスの外）だったらOk,ちなみにコンパイル時に値が決まるらしい
	//static constexpr　は　クラスで共同（Unityのstaticと同じやね、だから一意で共同で使う時にはこれがいいらしい、だから今回の場合はいいのかな？どうなんやろ）
   // static constexpr double time{ 5 };
	StageEnemyInfo stageEnemyInfo{};
	double elapsedTime{ 0 };
};
