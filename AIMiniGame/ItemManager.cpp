#include "ItemManager.hpp"
#include "Cheese.hpp"

void ItemManager::SpawnItems()
{
	//関数でも同じクラス内なら使える
	SpawnCheese();
	SpawnCaptureItem();
}

void ItemManager::SpawnCheese()
{
	cheeseInfo.time += Scene::DeltaTime();
	if (cheeseInfo.time < cheeseInfo.spawnTime) return;
	cheeseInfo.time = 0;
	double scale = GetRandomScale();
	auto type = static_cast<AmountType>(scale * 2);
	int amount = GetAmount(type);
	Vec2 pos;
	pos = GetRandomPos();
	//Cheese newCheese{ U"🧀"_emoji,amount,scale,pos};
	//std::move(newCheese);
	cheeses << Cheese{ U"🧀"_emoji,amount,scale,pos };//newCheese;
}

void ItemManager::SpawnCaptureItem()
{
	captureItemInfo.time += Scene::DeltaTime();
	if (captureItemInfo.time < captureItemInfo.spawnTime) return;
	captureItemInfo.time = 0;
	Vec2 pos;
	pos = GetRandomPos();
	captureItems << CaptureMouthItem{ U"🪤"_emoji,pos };
}

Vec2 ItemManager::GetRandomPos() const
{
	double x = Random(minX, maxX);
	double y = Random(minY, maxY);
	Vec2 spawnPos{ x,y };
	return spawnPos;
}

double ItemManager::GetRandomScale() const
{
	int number = Random(0, 100);
	if (number < 33) return scales[0];//最小
	else if (number < 66) return scales[1];//普通
	return scales[2];//最大
	//return Random(minScale, maxScale);
}

int ItemManager::GetAmount(AmountType type) const
{
	auto it = amountMap.find(type);//std::pair<const AmountType, int>らしい
	if (it != amountMap.end())
	{
		//firstはkeyでsecondはvalue
		//Print << it->second;
		return it->second;
	}
	return 0;
}
//これがconstじゃないのはCheeseMovementの中のさらにその中の関数でCheeseの位置を変えてる、それはつまりcheeseの状態が変わってる、だからダメ
void ItemManager::MoveItems()
{
	for (size_t i = 0; i < cheeses.size(); i++)
	{
		//配列はcopyだから、参照するためにpointer使わないといけない。Unity脳になってた。Unityだったらこれ別に参照できるようになるんだけどね
		auto& targetCheese = cheeses[i];
		targetCheese.Update();
	}

	for (size_t i = 0; i < captureItems.size(); i++)
	{
		auto& captureItem = captureItems[i];
		captureItem.Update();
	}
}

void ItemManager::Update()
{
	SpawnItems();
	MoveItems();
}
