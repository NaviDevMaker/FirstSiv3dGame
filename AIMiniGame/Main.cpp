# include <Siv3D.hpp> // Siv3D v0.6.16
#include "GameManager.hpp"
#include "DebugLogClass.hpp"

//なぜ前方宣言の場合は実体を作れないのか
//A :実体のサイズがわからないから、だから逆にポインターや参照はサイズが固定（8バイトとか）でサイズを知る必要がないから、T&　や　T* ができる
void Main()
{
	Scene::Resize(1920, 1080);
	Window::Resize(1280, 720);
	GameManager gameManager;
	Effect effect;
	while (System::Update())
	{
		gameManager.Update(effect);
		effect.update();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
