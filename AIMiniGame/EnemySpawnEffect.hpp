#include <Siv3D.hpp>

struct EnemySpawnEffect : IEffect
{
public:
	EnemySpawnEffect(const Vec2& spawnPos,double effectTime,const ColorF& colorF)
		:spawnPos{spawnPos}
		,effectTime{effectTime}
		,colorF{colorF}
	    { }
private:
	const Vec2 spawnPos;
	const double effectTime;
	const Texture looks{U"🐀"_emoji};
	ColorF colorF;
	static constexpr int32 maxRadius{ 90 };
	static constexpr int32 minRadius{ 30 };

	static constexpr double baseRingAlpha{ 0.12 };
	static constexpr double baseMouseAlpha{ 0.35 };

	static constexpr double ringAlphaRatio{ 0.45 };
	static constexpr double mouseAlphaRatio{ 0.60 };

	static constexpr double ringColorRatio{ 0.55 };
	static constexpr double mouseColorRatio{ 0.78 };

	static constexpr double baseRingColor{ 0.08 };
	static constexpr double baseMouseColor{ 0.22 };

	static constexpr double ringThickness{ 7.0 };

	static constexpr double circleAlphaRatio{ 0.35 };
	static constexpr double innerCircleScaleRatio{ 0.78 };
	static constexpr double baseMouseScale{ 0.55 };
	static constexpr double mouseScaleGain{ 0.20 };

	bool update(double t) override
	{
		const double t01 = Math::Clamp(t / effectTime, 0.0, 1.0);
		const double radius = Math::Lerp(static_cast<double>(maxRadius), static_cast<double>(minRadius), t01);

		//リングは時間経過で透明にするために1.0 - t01
		const double ringAlpha = ringAlphaRatio * (1.0 - t01) + baseRingAlpha;
		//ネズミは時間経過で不透明にするように
		const double mouseAlpha = baseMouseAlpha + mouseAlphaRatio * t01;

		ColorF ringColor
		{
			Math::Min(colorF.r * ringColorRatio + baseRingColor, 1.0),
			Math::Min(colorF.g * ringColorRatio + baseRingColor, 1.0),
			Math::Min(colorF.b * ringColorRatio + baseRingColor, 1.0),
			ringAlpha
		};

		ColorF mouseColor
		{
			Math::Min(colorF.r * mouseColorRatio + baseMouseColor, 1.0),
			Math::Min(colorF.g * mouseColorRatio + baseMouseColor, 1.0),
			Math::Min(colorF.b * mouseColorRatio + baseMouseColor, 1.0),
			mouseAlpha
		};

		Circle{ spawnPos, radius }.drawFrame(ringThickness, ringColor);
		Circle{ spawnPos, radius * innerCircleScaleRatio }.draw(ColorF{ ringColor.r, ringColor.g, ringColor.b, ringAlpha * circleAlphaRatio });
		looks.scaled(baseMouseScale + mouseScaleGain * t01).drawAt(spawnPos, mouseColor);
		return t < effectTime;
	}
};
