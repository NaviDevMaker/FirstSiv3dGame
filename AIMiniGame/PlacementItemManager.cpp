#include "PlacementItemManager.hpp"
#include "PlayerController.hpp"
#include "DebugLogClass.hpp"
#include "InputUtility.hpp"
//生成されたアイテムのUpdate毎の処理
void PlacementItemManager::Update(Array<Enemy>& enemys,Effect& effect)
{
	if(InputUtility::IsUseCaptureItem()) TryPlaceCaptureItem();
	HandlePlacedCaptureItem(enemys, effect);
	DrawUI();
}

void PlacementItemManager::ReduceCaptureItem()
{
	placementInventory.ReduceCaptureItem();
}

void PlacementItemManager::AddCaptureItem()
{
	placementInventory.AddCaptureItem();
}

void PlacementItemManager::DrawUI()
{
	DebugLogClass::DebugLog(U"{}"_fmt(placementInventory.GetCaptureItemCount()));
	placementUIManager.Update(placementInventory.GetCaptureItemCount());
}
//キャプチャーアイテムを置く
void PlacementItemManager::TryPlaceCaptureItem()
{
	if (placementInventory.TryUseCaptureItem())
	{
		placedCaptureItems << PlaceCaptureItem{ U"🪤"_emoji,player.pos};
		ReduceCaptureItem();
	}
}

//キャプチャーアイテムのチェック
// 注意：placedCaptureItems.size() の戻り値は符号なし整数型（size_t系）になる場合がある。
// その状態で auto i = size() - 1; とすると、i も符号なし型として推論される。
// 符号なし整数は 0 未満になれないため、for文の条件式
// i >= 0
// は常に true になる可能性がある。
// 例：i が 0 の状態で i-- すると、-1 にはならず最大値へアンダーフローする。
// 0 → 4294967295 → 4294967294 ...
// その結果、ループが終了せず無限ループ扱いになる。
// 対策として、逆順ループで削除処理を行う場合は
// int32 など符号付き整数型を明示して使用する。
// 例：
// for (int32 i = static_cast<int32>(placedCaptureItems.size()) - 1; i >= 0; --i)
void PlacementItemManager::HandlePlacedCaptureItem(Array<Enemy>& enemys,Effect& effect)
{
	for(int32 i = static_cast<int32>(placedCaptureItems.size()) - 1; i >= 0;i--)
	{
		auto& placedCaptureItem = placedCaptureItems[i];
		placedCaptureItem.Update(enemys, effect);
		if (placedCaptureItem.IsUsed()) placedCaptureItems.remove_at(i);
	}
}

void PlacementItemManager::Reset()
{
	placementInventory.Reset();
}
