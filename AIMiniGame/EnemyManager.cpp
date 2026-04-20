#include "EnemyManager.hpp"

void EnemyManager::Update()
{
	EnemySpawn();
	for (auto& enemy : enemys)
	{
		enemy.Update();
	}
}

void EnemyManager::EnemySpawn()
{
	if (enemys.size() != 0) return;
	elapsedTime += Scene::DeltaTime();
	if (elapsedTime < time) return;
	elapsedTime = 0;
	int32 speed = 1000;
	auto x = Random(minX, maxX);
	auto y = Random(minY, maxY);
	Vec2 spawnPos{ x,y };
	Enemy newEnemy{speed,GetRandomEnemyColor(),spawnPos,player};
	enemys << std::move(newEnemy);
}

ColorF EnemyManager::GetRandomEnemyColor() const
{
	auto type = GetRandomEnemyType();
	auto pairs = colorMap.find(type);
	return pairs->second;
}

EnemyType EnemyManager::GetRandomEnemyType() const
{
	auto min = 0;
	auto max = 100;
	auto number = Random(min, max);
	if (number < 50) return EnemyType::Weak;
	else if (number < 85) return EnemyType::Normal;
	return EnemyType::Strong;
}
