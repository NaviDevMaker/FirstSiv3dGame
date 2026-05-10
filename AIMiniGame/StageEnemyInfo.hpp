#pragma once
#include <Siv3D.hpp>

enum class EnemyType;
enum class EnemyMoveType;
struct StageEnemyInfo
{
	double spawnInterval{ 1.0 };
	//EnemyType はクラスではなく enum class（実体サイズが決まる型） なので、Array<EnemyType> をメンバーにしても成立
	Array<EnemyType> spawnableEnemyTypes;
	Array<EnemyMoveType> moveTypes;
};
