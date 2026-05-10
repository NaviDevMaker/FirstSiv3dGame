#include "CaptureItemData.hpp"

void CaptureItemData::AddCaptureItem(int32 amount)
{
	captureItemCount+= amount;
}

bool CaptureItemData::IsUsable() const
{
	return captureItemCount > 0;
}

void CaptureItemData::ReduceItemCount(int32 amount)
{
	captureItemCount -= amount;
}

void CaptureItemData::Reset()
{
	captureItemCount = 0;
}
