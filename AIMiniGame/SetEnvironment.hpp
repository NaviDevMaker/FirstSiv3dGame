#pragma once
#include <Siv3D.hpp>

class SetEnvironment
{
public:
    void Update();
private:
	//Appフォルダからのpath
	const Texture background{ U"background_Siv3d.png" };
	void Draw() const;
};
