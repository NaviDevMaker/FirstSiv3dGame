#pragma once
#include <Siv3D.hpp>
#include <unordered_map>
#include "Enemy.hpp"

class PlayerController;
enum EnemyType
{
	Strong,
	Normal,
	Weak
};

class EnemyManager
{
public:
	EnemyManager(PlayerController& player)
		:player{ player }
	{

	}
  void	Update();
  Array<Enemy>& GetEnemies()  { return enemys;}
private:
	Array<Enemy> enemys;//今回は自分で生成して追加、削除するから&（参照）じゃなくていい
	PlayerController& player;
	std::unordered_map<EnemyType, ColorF> colorMap =
	{
		{Weak,ColorF{0,1,0}},
		{Normal,ColorF{0,0,1}},
		{Strong,ColorF{1,0,0}}
	};
	void EnemySpawn();
	ColorF GetRandomEnemyColor() const;
	EnemyType GetRandomEnemyType() const;
	double minX{ 0 };
	double maxX{ 1920 };
	double minY{ 0 };
	double maxY{ 1080 };
	//constexprはグローバル変数（クラスの外）だったらOk,ちなみにコンパイル時に値が決まるらしい
	//static constexpr　は　クラスで共同（Unityのstaticと同じやね、だから一意で共同で使う時にはこれがいいらしい、だから今回の場合はいいのかな？どうなんやろ）
    static constexpr double time{ 5 };
	double elapsedTime{ 0 };
};
