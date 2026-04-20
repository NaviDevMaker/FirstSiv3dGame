#include "PlacementUIManager.hpp"

void PlacementUIManager::Draw() const
{
    font(U"CaptureItem:{}"_fmt(captureItemCount)).draw(50,190);
}

void PlacementUIManager::Update(int32 captureItemCount)
{
	this->captureItemCount = captureItemCount;
	if (captureItemCount != 0)	Draw();
}
