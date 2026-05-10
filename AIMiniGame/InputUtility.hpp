#pragma once
#include <Siv3D.hpp>

class InputUtility
{
public:
	static bool IsConfirmPressed();
	static bool IsMoveRight();
	static bool IsMoveLeft();
	static bool IsMoveDown();
	static bool IsMoveUp();
	static bool IsUseCaptureItem();
};
