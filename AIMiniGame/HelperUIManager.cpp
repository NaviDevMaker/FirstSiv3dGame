#include "HelperUIManager.hpp"
#include "DebugLogClass.hpp"

//フォントのアルファ値を更新
void HelperUIManager::UpdateAlpha()
{
	if (speed <= 0.0)
	{
		return;
	}
	const auto amount = type * (speed * Scene::DeltaTime());
	alpha += amount;
	alpha = Math::Clamp(alpha, static_cast<double>(min), static_cast<double>(max));
	if ((alpha <= min && type < 0) || (alpha >= max && type > 0))
	{
		type = -type;
	}
	//DebugLogClass::DebugLog(U"DebugUpdate!!:{}"_fmt(alpha));
}

