#pragma once
#include <Siv3D.hpp>

struct CaptureItemSpawnEffect : IEffect
{
	CaptureItemSpawnEffect(const double effectTime)
		:effectTime{ effectTime } {}
	const double effectTime;
	bool update(double t) override
	{
		return t < effectTime;
	}
};
