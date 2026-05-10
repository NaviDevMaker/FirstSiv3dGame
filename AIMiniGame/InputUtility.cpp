#include "InputUtility.hpp"

bool InputUtility::IsConfirmPressed()
{
	return KeyEnter.down();
}

bool InputUtility::IsMoveRight()
{
	return KeyD.pressed();
}

bool InputUtility::IsMoveLeft()
{
	return KeyA.pressed();
}

bool InputUtility::IsMoveUp()
{
	return KeyW.pressed();
}

bool InputUtility::IsMoveDown()
{
	return KeyS.pressed();
}

bool InputUtility::IsUseCaptureItem()
{
	return MouseL.down();
}
