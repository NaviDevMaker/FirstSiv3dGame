#pragma once
#include <Siv3D.hpp>

//爆弾のデータ（数など）を管理する
class CaptureItemData
{
public:
  void	AddCaptureItem(int32 amount = 1);
  void  ReduceItemCount(int32 amount = 1);
  bool  IsUsable() const;
  int32 GetCaptureItemCount() const { return captureItemCount; }
private:
	int32 captureItemCount{0};
	
};
