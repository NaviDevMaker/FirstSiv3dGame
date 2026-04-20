#pragma once
#include <Siv3D.hpp>
#include "Cheese.hpp" //これ宣言でArrayにCheese使うから必要っぽい
#include "CaptureMouthItem.hpp"
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
	void Update();
	Array<Cheese>& GetCheeses() { return cheeses; }
	Array<CaptureMouthItem>& GetCaptureIterms() { return captureItems; }
private:
	Array<Cheese> cheeses;
	Array<CaptureMouthItem> captureItems;
	const Array<double> scales{ 0.5,1.0,1.5 };
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
	double GetRandomScale() const;
	int GetAmount(AmountType type) const;
	void SpawnCheese();
	void SpawnCaptureItem();
	void SpawnItems();
	void MoveItems();
	ItemInfo cheeseInfo{0,3};
	ItemInfo captureItemInfo{0,1};//テスト用情報
};


