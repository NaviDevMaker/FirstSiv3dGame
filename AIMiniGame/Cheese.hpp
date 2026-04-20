#pragma once
#include <Siv3D.hpp>

class Cheese
{
public:
	Cheese(const Emoji emoji,int point,double scale,Vec2 spawnPos)
		: looks{ Texture{emoji} }
		,cheeseCircle{spawnPos,looks.width() * scale / 2}
	{
		this->point = point;
		this->scale = scale;
		this->spawnPos = spawnPos;
	}
	void Update();
	int point{ 0 };
private:
	Vec2 spawnPos;
	Texture looks;
	double scale{ 0 };
	double angle{ 0 };
	double rotateAmount{5};
	void RotateCheese();
	void Draw() const;
public://順番依存だから
	Circle cheeseCircle;
	
	//なんかfriendってやつもあるらしい,これの場合同じファイル内ならアクセスできるやつかな？
};
