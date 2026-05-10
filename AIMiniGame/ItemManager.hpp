#pragma once
#include <Siv3D.hpp>
#include "Cheese.hpp" //これ宣言でArrayにCheese使うから必要っぽい
#include "CaptureMouthItem.hpp"
#include <unordered_map> //辞書使う時に必要らしい
//C++は上から見ていく、だからItemInfoの宣言がメンバー変数より下だったらアウト
#include "ItemInfo.hpp"
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
	void ApplyStageInfo(const ItemInfo& cheeseItemInfo,const ItemInfo& captureItemInfo);
	Array<Cheese>& GetCheeses() { return cheeses; }
	Array<CaptureMouthItem>& GetCaptureItems() { return captureItems; }
	void Reset();
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

	std::unordered_map<AmountType, ColorF> colorMap
	{
		{Small,ColorF{1,0,0}},
		{Middle,ColorF{1.0, 0.65, 0.0}},
		{Big,ColorF{1.0, 0.9, 0.2}}
	};

	Vec2 GetRandomPos() const;
	double GetRandomScale() const;
	int GetAmount(AmountType type) const;
	ColorF GetCheeseColor(AmountType type) const;
	void SpawnCheese();
	void SpawnCaptureItem();
	void SpawnItems();
	void MoveItems();
	ItemInfo cheeseInfo{0,3};
	ItemInfo captureItemInfo{0,1};//テスト用情報
};


