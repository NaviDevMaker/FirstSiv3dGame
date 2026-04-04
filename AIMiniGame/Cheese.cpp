#include "Cheese.hpp"

void Cheese::RotateCheese()
{
	angle += rotateAmount * Scene::DeltaTime();
}

void Cheese::Draw()const
{
	looks.scaled(scale).rotated(angle).drawAt(spawnPos);
}

//Updateの中でやるやつ
void Cheese::CheeseMovement()
{
	RotateCheese();
	Draw();
}
