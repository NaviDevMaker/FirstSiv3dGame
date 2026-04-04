#pragma once
#include <Siv3D.hpp>

class PlayerController
{
public:
	PlayerController(const Emoji& emoji)
		: looks{ Texture{emoji} }
	{		
	}
  	Texture looks;
	Vec2 pos{0,0};
    const double speed{300};
	void Update();
	void Draw() const;

};
