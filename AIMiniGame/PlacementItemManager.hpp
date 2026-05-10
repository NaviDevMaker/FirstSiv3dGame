#pragma once
#include <Siv3D.hpp>
#include "PlaceCaptureItem.hpp"
#include "PlacementInventory.hpp"
#include "PlacementUIManager.hpp"
//プレイヤーのアイテムを実際に置く処理

class Enemy;
class PlayerController;
class PlacementItemManager
{
public:
	PlacementItemManager(PlayerController& player)
		:player{player}
	{

	}
	void Update(Array<Enemy>& enemys,Effect& effect);
	void AddCaptureItem();
	void Reset();
private:
	Array<PlaceCaptureItem> placedCaptureItems;
	PlayerController& player;//この存在は確定だから参照でいい
	PlacementInventory placementInventory;
	PlacementUIManager placementUIManager;
	void TryPlaceCaptureItem();
	void HandlePlacedCaptureItem(Array<Enemy>& enemys,Effect& effect);
	void DrawUI();
	void ReduceCaptureItem();
};

//使い分けの基準（超重要）                 
//状況	使うべき
//必ず存在する	参照&
//なくてもいい（nullあり）	ポインタ*
//後から差し替えたい	ポインタ*
//所有権を持つ	unique_ptr
//関数引数で軽く渡す	参照 &


// C++における #include は、指定したファイルの内容をその場に      
// 展開するプリプロセス処理であり、
// ヘッダファイル（.hpp）のみが対象となる。
//そのため、あるヘッダファイルを #include しても、
// 対応する実装ファイル（.cpp）が同時に取り込まれることはない。
//この性質により、クラス同士が相互に関係している場合でも、
// 一方のヘッダで前方宣言（forward declaration）を用いることで
// 循環依存を防ぐことができる。
//例えば、PlayerController.hpp が PlacementItemManager.hpp を
// #include している場合でも、PlacementItemManager.hpp 側で
// PlayerController を前方宣言のみに留めていれば、 再度
// PlayerController.hpp を #include する必要がなくなり、ヘッダ同士の循環参照は発生しない。
//一方で、クラスのメンバ関数の実装（.cpp）においては、実際に
// 相手クラスの関数やメンバへアクセスするため、完全な型情報が
// 必要となる。この場合に限り、対応するヘッダファイルを #include することで問題なく解決できる。

