#pragma once
#include <Siv3D.hpp>


//UIのアルファとかもしかしたらこれからそれ以外のやつを更新する
class HelperUIManager
{
public:
	void UpdateAlpha();
	double GetAlpha() const { return alpha; }
	void ResetAlpha(double value = 1.0) { alpha = Math::Clamp(value, static_cast<double>(min), static_cast<double>(max)); }
private:
	const double speed{ 0.5 };
	double alpha{ 1.0 };
	const int32 max{ 1 };
	const int32 min{ 0 };
	int type = -1;
};
