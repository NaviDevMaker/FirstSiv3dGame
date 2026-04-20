#include "SetEnvironment.hpp"

void SetEnvironment::Draw() const
{
	background.resized(Scene::Size()).draw();
}

void SetEnvironment::Update()
{
	Draw();
}
