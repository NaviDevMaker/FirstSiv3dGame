#include <Siv3D.hpp>

class PlayerController;
struct  PlayerHitEffect:IEffect
{
	PlayerController&  player;
	explicit PlayerHitEffect(PlayerController& player)
		:player{player}{ }

	bool update(double t) override
	{
		constexpr double effectTime = 0.5;
		constexpr double maxRadius = 150;

		const double x = Min(t / effectTime, 1.0);
		const double radius = maxRadius * x;
		const double alpha = 1 - x;
		const ColorF frameColor{ 1.0,0.2,0.2,alpha };
		const ColorF circleColor{ 1.0,0.0,0.0,0.6 * alpha };

		Circle{player.pos,radius }.drawFrame(6.0 * (1.0 - x), frameColor);
		Circle{player.pos,Max(0.0,radius - 10)}.draw(circleColor);
		return t < effectTime;
	}
};

// C++では
// Class obj = value;
// という書き方が、単なる代入ではなく
// 「value を使って obj を生成する」意味になる場合がある。

// 例:
//class Damage
//{
//public:
//	Damage(int value) {}
//};

//Damage d = 10; // int から Damage を生成している

// これは 1引数コンストラクタが
// 暗黙的な型変換として利用されるため。

// 内部的には以下に近い意味になる:
// Damage d(10);
// または
// Damage d = Damage(10);

// 意図しない自動生成を防ぎたい場合は explicit を付ける。

//class Damage2
//{
//public:
//	explicit Damage2(int value) {}
//};

//Damage2 d2 = 10; // NG
//Damage2 d3(10);  // OK
