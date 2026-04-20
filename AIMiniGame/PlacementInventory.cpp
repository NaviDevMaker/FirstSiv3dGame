#include "PlacementInventory.hpp"
#include "DebugLogClass.hpp"

bool PlacementInventory::TryUseCaptureItem()
{
	if (captureItemData.IsUsable())
	{
		//DebugLogClass::DebugLog(U"使われました");
		return true;
    }
	return false;
}

void PlacementInventory::AddCaptureItem(int32 amount)
{
	captureItemData.AddCaptureItem(amount);
}

void PlacementInventory::ReduceCaptureItem(int32 amount)
{
	captureItemData.ReduceItemCount(amount);
}

int32 PlacementInventory::GetCaptureItemCount() const
{
	return captureItemData.GetCaptureItemCount();
}
