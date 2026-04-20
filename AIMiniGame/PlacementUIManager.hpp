#pragma once
#include <Siv3D.hpp>

class PlacementUIManager
{
public:
	void Update(int32 captureItemCount);
private:
	void Draw() const;
	int32 captureItemCount{ 0 };
	Font font{ 80 };
};
