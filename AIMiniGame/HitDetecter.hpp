#pragma once
#include <Siv3D.hpp>
#include "Cheese.hpp"
#include "Enemy.hpp"
#include "CaptureMouthItem.hpp"

// なんでわざわざ前方宣言使うの？ 循環includeを防ぐため 「前方宣言 = 名前だけ予約」
//「PlayerControllerっていうクラスが存在するよ」ってコンパイラに教えてるだけ

//❌ include必須な場合
//実体を持つ メンバ関数使う（hpp内で）
class PlayerController;
class HitDetecter
{
public:
	//           完全版（これが全て）
	//      書き方	    意味
	//       &x	    アドレス取得
	//	    T& x	参照（別名）
	//	    T* x	ポインタ（アドレスを入れる箱）
	//	     *p	ポインタの中身
	// 
	//                     表
	//          引数	渡すもの　　　　　　　例
	//           T&        実体	　　　　player,  *this
	//	         T*      アドレス　　　　&player, this
	//
	HitDetecter(PlayerController& player);
	bool DetectHitCheese(Array<Cheese>& cheeses,int& point,Effect& effect) const;
	bool DetectHitEnemy(Array<Enemy>& enemys) const;
	bool DetectHitCaptureitem(Array<CaptureMouthItem>& captureItems) const;
private:
	PlayerController& player; //参照・ポインタなら中身いらない,PlayerController player; ならinclude必要
};
