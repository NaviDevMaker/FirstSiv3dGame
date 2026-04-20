#include "Cheese.hpp"

void Cheese::RotateCheese()
{
	angle += rotateAmount * Scene::DeltaTime();
}

void Cheese::Draw()const
{
	cheeseCircle.draw(ColorF{ 1,0,0 });
	looks.scaled(scale).rotated(angle).drawAt(spawnPos);
}

//Updateの中でやるやつ
void Cheese::Update()
{
	RotateCheese();
	Draw();
}
