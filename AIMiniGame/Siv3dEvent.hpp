#pragma once
#include <Siv3D.hpp>
#include <functional>

//Unity風のイベント設定するためのEventクラス
//引数は無し
class Siv3dEvent
{
public:
	//関数の登録
	void Add(const std::function<void()> function)
	{
		functions << function;
	}

	//関数の発火
	void Invoke()
	{
		for (const auto& function : functions)
		{
			function();
		}
	}
private:
	Array<std::function<void()>> functions;
};

// const std::function<void()>& にしている理由
//
// 1. &（参照渡し）
// std::function をコピーせず受け取れるため無駄なコピーコストを防げる。
//
// 2. const
// 関数内で function の中身を書き換えないことを明示できる。
// また、ラムダ式のような一時オブジェクトも受け取れる。
//
// 例:
// Add([](){ Print << U"Hello"; });
//
// 3. 非const参照だと問題
// std::function<void()>& にすると、一時オブジェクトを受け取れず
// ラムダ式を直接渡しにくくなる。
//
// そのため、イベント登録用の引数では
// const std::function<void()>& がよく使われる。
