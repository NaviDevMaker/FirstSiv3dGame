#include "PlayerStatusManager.hpp"

void PlayerStatusManager::ActivateFlag(StatusType type)
{
	auto& status = statusMap.at(type);
	status.isActive = true;
}

void PlayerStatusManager::DeactivateFlag(StatusType type)
{
	auto& status = statusMap.at(type);
	status.isActive = false;
}

bool PlayerStatusManager::GetActiveStatus(StatusType type)
{
	if (!statusMap.contains(type)) return false;
	return statusMap.at(type).isActive;
}

void PlayerStatusManager::CountDownStatus()
{
	for (std::pair<const StatusType,Status>& pair : statusMap)
	{
		auto& status = pair.second;
		if (status.isActive)
		{
			status.elapsedTime += Scene::DeltaTime();
			if (status.elapsedTime >= status.effectTime)
			{
				auto& type = pair.first;
				DeactivateFlag(type);
				status.elapsedTime = 0;
			}
		}
	}
}

void PlayerStatusManager::Update()
{
	CountDownStatus();
}

void PlayerStatusManager::Reset()
{
	for (std::pair<const StatusType, Status>& pair : statusMap)
	{
		auto& type = pair.first;
		auto& status = pair.second;
		status.elapsedTime = 0;
		DeactivateFlag(type);
	}
}
