#pragma once
#include <Siv3D.hpp>

struct CheeseSpawnEffect : IEffect
{
	CheeseSpawnEffect(const double effectTime,const ColorF color)
		:effectTime{effectTime}
		,color{color}
	{ }

	const double effectTime;
	const Texture looks{ U"🧀"_emoji };
	const ColorF color;

	static constexpr double baseAlpha{ 0.2 };
	static constexpr double alphaRatio{0.8};
	bool update(double t) override
	{
		auto t01 = Math::Clamp(t / effectTime,0.0,1.0);
		auto  currentAlpha = baseAlpha + alphaRatio * t01;
		ColorF cheeseColor{ color.r,color.g,color.b,currentAlpha };
		return t < effectTime;
	}
};
