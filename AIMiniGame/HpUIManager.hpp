#pragma once
#include <Siv3D.hpp>

class HpUIManager
{
public:
	HpUIManager(int& hp)
		:hp{ hp }
	{

	}
	void Update() const;
private:
	const Font font{ 80 };
	int& hp;
};
