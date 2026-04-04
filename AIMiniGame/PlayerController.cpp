#include "PlayerController.hpp"

void PlayerController::Update()
{
	if (KeyA.pressed()) pos.x -= speed * Scene::DeltaTime();
	else if (KeyD.pressed()) pos.x += speed * Scene::DeltaTime();
	else if (KeyW.pressed()) pos.y -= speed * Scene::DeltaTime();
	else if (KeyS.pressed()) pos.y += speed * Scene::DeltaTime();
}

void PlayerController::Draw() const
{
	looks.drawAt(pos);
}

