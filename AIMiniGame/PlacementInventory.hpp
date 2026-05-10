#pragma once
#include <Siv3D.hpp>
#include "CaptureItemData.hpp"

//キャプチャーアイテムと生成の中間を担うクラス、ここでデータから生成可能かを判断し、それをPlacementItemManagerクラスに送る
//アイテムの数を管理
//データを持つクラスに見た目は入れない！！(UI表示とか)
class PlacementInventory
{
public:
	bool TryUseCaptureItem();
	void AddCaptureItem(int32 amount = 1);
	void ReduceCaptureItem(int32 amount = 1);
	int32 GetCaptureItemCount() const;
	void Reset();
private:
	CaptureItemData captureItemData;
};
