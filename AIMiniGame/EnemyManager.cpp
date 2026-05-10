#include "EnemyManager.hpp"
#include "EnemySpawnEffect.hpp"
void EnemyManager::Update(Effect& effect)
{
	QueueEnemySpawn(effect);
	EnemySpawn();
	for (auto& enemy : enemys)
	{
		enemy.Update();
	}
}

//エネミーの生成
void EnemyManager::EnemySpawn()
{
	//if (enemys.size() != 0) return;
	//static constexpr int32 speed{ 100 };

	int32 size = static_cast<int32>(pendingQueue.size());
	if (size <= 0) return;
	for (int32 i = (size - 1); i >= 0; i--)
	{
		auto index = static_cast<size_t>(i);
		auto& pendingSpawn = pendingQueue[index];
		pendingSpawn.elapsedTime += Scene::DeltaTime();
		if (pendingSpawn.elapsedTime >= pendingSpawn.effectTime)
		{
			auto& color = pendingSpawn.targetColor;
			auto& spawnPos = pendingSpawn.spawnPos;
			auto isDiagonal = pendingSpawn.isDiagonal;
			auto speed = pendingSpawn.speed;
			Enemy newEnemy{speed,color,spawnPos,player,isDiagonal};
			enemys << std::move(newEnemy);
			pendingQueue.remove_at(index);
		}
	}
}

void EnemyManager::QueueEnemySpawn(Effect& effect)
{
	static constexpr double effectTime{ 3.0 };

	if (stageEnemyInfo.spawnableEnemyTypes.isEmpty()) return;
	elapsedTime += Scene::DeltaTime();
	if (elapsedTime < stageEnemyInfo.spawnInterval) return;
	elapsedTime = 0;
	const auto x = Random(0.0, static_cast<double>(Scene::Width()));
	const auto y = Random(0.0, static_cast<double>(Scene::Height()));
	Vec2 spawnPos{ x,y };
	const auto type = GetRandomEnemyType();
	const ColorF colorF = GetRandomEnemyColor(type);
	const int32 speed = GetRandomEnemySpeed(type);
	const auto isDiagonal = GetIsDiagonal();
	effect.add<EnemySpawnEffect>(spawnPos, effectTime, colorF);
	pendingQueue << PendingSpawn{ effectTime,0,speed,spawnPos,colorF,isDiagonal};
}

//ステージ情報を更新する
void EnemyManager::ApplyStageInfo(const StageEnemyInfo& stageEnemyInfo)
{
	elapsedTime = 0;
	this->stageEnemyInfo = stageEnemyInfo;
}

//ネズミの色を取得
ColorF EnemyManager::GetRandomEnemyColor(EnemyType type) const
{
	const auto pair = colorMap.find(type);
	if (pair != colorMap.end())
	{
		return pair->second;
	}
	return Palette::White;
}

//ネズミのスピードを取得
int32 EnemyManager::GetRandomEnemySpeed(EnemyType type) const
{
	const auto pair = speedMap.find(type);
	if (pair != speedMap.end())
	{
		return pair->second;
	}
	//デフォルトのスピード
	return 100;
}

bool EnemyManager::GetIsDiagonal() const
{
	const auto& type = stageEnemyInfo.moveTypes;
	if (type.isEmpty()) return static_cast<bool>(EnemyMoveType::RightAngle);
	if (static_cast<int32>(type.size()) == 1) return static_cast<bool>(type.front());
	const auto r = Random(static_cast<size_t>(0), type.size() - 1);
	return static_cast<bool>(type[r]);
}
//生成可能なエネミーのタイプの中からランダムに返す
EnemyType EnemyManager::GetRandomEnemyType() const
{
	const auto& types = stageEnemyInfo.spawnableEnemyTypes;
	if (types.isEmpty())
	{
		return EnemyType::Weak;
	}
	if (static_cast<int32>(types.size()) == 1)
	{
		return types.front();
	}
	const auto index = Random(static_cast<size_t>(0), types.size() - 1);
	return types[index];
}

void EnemyManager::Reset()
{
	enemys.clear();
	pendingQueue.clear();
	elapsedTime = 0;
}
