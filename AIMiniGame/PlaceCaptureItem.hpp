#pragma once
#include <Siv3D.hpp>

class Enemy;
//生成されるキャプチャーアイテム
class PlaceCaptureItem
{
public:
	PlaceCaptureItem(const Emoji& emoji,const Vec2& spawnPos)
		:looks{emoji}
		,spawnPos{ spawnPos }
		,hit{spawnPos,looks.width() / 2}
	{

	}
	void Update(Array<Enemy>& enemys,Effect& effect);
	bool IsUsed() const { return isUsed; };
private:
   Texture looks;
   Circle hit;
   Vec2 spawnPos{0,0};
   void Draw();
   void CaptureEnemy(Array<Enemy>& enemys,Effect& effect);
   bool isUsed{ false };
};
