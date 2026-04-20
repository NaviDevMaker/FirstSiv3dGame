#pragma once
#include <Siv3D.hpp>

class CaptureMouthItem
{
public:
	CaptureMouthItem(const Emoji& emoji, Vec2& spawnPos)
		:looks{emoji}
		,spawnPos{spawnPos}
		,pos{this->spawnPos}
		, hit{ Circle{spawnPos,looks.width() * scale / 2}}
	{

	}
	void Update();
private:
	Texture looks;
	Vec2 spawnPos;
	Vec2 pos;
	static constexpr double scale{ 0.5 };
	static constexpr double floatSpeed{5};//速さ（MathのSinに渡すやつ）
	static constexpr double moveAmount{5};//振れ幅（動き上限）
	double floatAmount{ 0 };//インスタンスごとに必要だから関数の中のstaticも使えない
	void UpdateItemPosition();
	void Draw();
public:
	Circle hit;//中身が構造体らしいからconstだとだめっぽい
};

//C++における代入演算子（operator=）は、オブジェクト全体を一括でコピーしているように見えて、実際には各メンバ変数ごとに値を代入する処理として展開されます。
//例えば、クラスが複数のメンバ変数を持つ場合、a = b; という代入は内部的に a.x = b.x; 、a.y = b.y; のように各メンバへの代入処理として行われます。
//このため、クラス内に const 修飾されたメンバ変数が含まれている場合、そのメンバは初期化後に変更することができないため、代入処理が成立しません。
//結果としてコンパイラは、そのクラスに対するコピー代入演算子を自動生成できないと判断し、該当する関数を削除（deleted）します。
//したがって、const メンバを持つクラスは「生成（コンストラクタによる初期化）」は可能である一方、「既存オブジェクトへの代入」は行えないという特性を持ちます。
//これは、C++における「constは変更不可である」という設計原則と、代入処理の内部構造が一致していないために生じる挙動です。
