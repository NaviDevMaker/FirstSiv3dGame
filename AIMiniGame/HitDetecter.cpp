#include "HitDetecter.hpp"
#include "PlayerController.hpp"
#include "ItemGetEffect.hpp"
HitDetecter::HitDetecter(PlayerController& player)
	: player(player)
{

}

//ルールまとめ
//使い方	include必要？
//Enemy* / Enemy & だけ	❌ 不要（前方宣言OK）
//Array<Enemy>	⚠ 場合による
//enemy.hit みたいに中身使う	✅ 必須
bool HitDetecter::DetectHitEnemy(Array<Enemy>& enemys) const
{
	if (enemys.isEmpty()) return false;
	for (auto& enemy : enemys)
	{
		if (player.hit.intersects(enemy.hit))
		{
			return true;
		}
	}

	return false;
}

//チーズに当たったかの検出
bool HitDetecter::DetectHitCheese(Array<Cheese>& cheeses, int& point,Effect& effect) const
{
	if (cheeses.isEmpty()) return false;
	//再確認、Cheese cheese だとcopyされるから＆が必要
	//読み取りだけなら　for (const Cheese& cheese : cheeses)
	//int32が基本
	for (int32 i = static_cast<int32>(cheeses.size()) - 1; i >= 0; i--)
	{
		auto& cheese = cheeses[i];
		if (player.hit.intersects(cheese.cheeseCircle))
		{
			point = cheese.point;
			//removed_atとの違いに注意
			cheeses.remove_at(i);

			const double yellow = 60.0;
			effect.add<ItemGetEffect>(player.pos,yellow);
			return true;
		}
	}
	
	return false;
}

//キャプチャアイテムに当たった時
bool HitDetecter::DetectHitCaptureitem(Array<CaptureMouthItem>& captureItems,Effect& effect) const
{
	if (captureItems.isEmpty()) return false;
	for (int32 i = static_cast<int32>(captureItems.size()) - 1; i >= 0; i--)
	{
		auto& item = captureItems[i];
		if (player.hit.intersects(item.hit))
		{
			captureItems.remove_at(i);
			const double blue = 240;
			effect.add<ItemGetEffect>(player.pos,blue);
			return true;
		}
	}
	return false;
}
