#include "CaptureMouthItem.hpp"

void CaptureMouthItem::UpdateItemPosition()
{
	floatAmount += Scene::DeltaTime() * floatSpeed;
	auto y = Math::Sin(floatAmount) * moveAmount;
	pos.y = spawnPos.y + y;
}

void CaptureMouthItem::Update()
{
	UpdateItemPosition();
	Draw();
}

void CaptureMouthItem::Draw() 
{
	hit.center = pos;
	hit.draw(ColorF{1,0,0});
	looks.scaled(scale).drawAt(pos);
}
