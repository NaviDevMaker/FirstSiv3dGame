#pragma once
#include <Siv3D.hpp>

class Cheese
{
public:
	Cheese(const Emoji emoji,int point,int scale,Vec2 spawnPos)
		: looks{ Texture{emoji} }
	{
		this->point = point;
		this->scale = scale;
		this->spawnPos = spawnPos;
	}

	void CheeseMovement();
private:
	Vec2 spawnPos;
	Texture looks;
	int point{ 0 };
	int scale{ 0 };
	double angle{ 0 };
	const double rotateAmount{5};
	void RotateCheese();
	void Draw() const;
	//なんかfriendってやつもあるらしい,これの場合同じファイル内ならアクセスできるやつかな？
};
