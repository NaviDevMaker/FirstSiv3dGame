#pragma once
#include <Siv3D.hpp>
#include "Cheese.hpp" //これ宣言でArrayにCheese使うから必要っぽい
#include <unordered_map> //辞書使う時に必要らしい
//C++は上から見ていく、だからItemInfoの宣言がメンバー変数より下だったらアウト
struct  ItemInfo
{
	double time;
	double spawnTime;
	int effectAmount{0};
};

enum AmountType
{
	Small = 1,
	Middle = 2,
	Big = 3
};
class ItemManager
{
public:
	void SpawnItems();
	void MoveItems();
private:
	const int maxScale{ 3 };
	const int minScale{ 1 };
	std::unordered_map<AmountType, int> amountMap
	{
		{Small,5},
		{Middle,10},
		{Big,15}
	};
	double minX{ 0 };
	double maxX{ 1920 };
	double minY{ 0 };
	double maxY{ 1080 };
	Vec2 GetRandomPos() const;
	int GetRandomScale() const;
	int GetAmount(AmountType type) const;
	void SpawnCheese();
	Array<Cheese> cheeses;
	ItemInfo cheeseInfo{0,3};
};


