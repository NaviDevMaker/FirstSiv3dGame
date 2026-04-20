#include <Siv3D.hpp>

//ネズミを捕らえた時のエフェクト
//構造体とクラスの違いはC++の場合はアクセス、構造体の場合public、クラスはprivate
//UnityC#でもC++でも軽いものって認識は共通
struct  CaptureEffect:IEffect
{
	CaptureEffect(const Vec2& spawnPos)
		:spawnPos{ spawnPos }

	{

	}


	const Vec2 spawnPos;
	//経過時間(t)がeffectTimeより小さい間エフェクトを出す
	bool update(double t) override
	{
		constexpr double effectTime = 0.3;
		constexpr double maxScale = 100;//Unityのscaleの感覚と違うわ
		double t01 = t / effectTime;
		auto targetScale = maxScale * t01;
		Circle{ spawnPos,targetScale}.draw();
		return t < effectTime;
	}
};

// Vec2& は「変更可能な参照」。
// 既に存在する名前付き変数（左辺値）しか受け取れない。
// 例:
//Vec2 pos{ 100, 200 };
//Func(pos);            // OK
//Func(Vec2{ 100,200 });  // NG（一時オブジェクト）
//Func(player.pos);     // 戻り値や式によってはNGになる場合あり
// const Vec2& は「読み取り専用参照」。
// 名前付き変数だけでなく、一時オブジェクトや計算結果も受け取れる。
// 例:
//Vec2 pos{ 100, 200 };
//Func(pos);            // OK
//Func(Vec2{ 100,200 });  // OK
//Func(player.pos);     // OK（式や戻り値も受けやすい）
// 今回のように「座標を受け取って内部に保存するだけ」の用途では、
// 引数を変更する必要がないため const Vec2& の方が柔軟で安全。

