#include "Enemy.hpp"
#include "DebugLogClass.hpp"
#include "PlayerController.hpp"

Enemy::Enemy(int32 speed, ColorF colorF, Vec2 spawnPos, PlayerController& player
			, bool isDiagonal)
	:speed{ speed }
	, colorF{ colorF }
	, looks{ Texture{U"🐀"_emoji} }
	, pos{ spawnPos }
	, hit{ spawnPos,looks.width() / 2 }
	, player{ player }
	,isDiagonal{isDiagonal}
	//, previousPos{ player.pos }//ポジション触るからinclude必要
{

}
void Enemy::Update()
{
	Vec2 nor{ 0,0};
	UpdatePosition(nor);
	Draw(nor);
}

void Enemy::UpdatePosition(Vec2& nor)
{
	const double deltaTime = Scene::DeltaTime();
	pathElapsedTime += deltaTime;

	if (path.isEmpty() || pathElapsedTime >= pathRefreshInterval)
	{
		pathElapsedTime = 0;
		path = astar.FindPath(pos, player.get().pos,isDiagonal);
		pathIndex = 0;
	}

	//Print << U"Start" << path.size();
	if (pathIndex >= path.size()) return;
	Vec2 target = path[pathIndex];
	double length = (target - pos).length();
	if (length < 0.0001) return;
	nor = (target - pos).normalize();
	const double moveDistance = speed * deltaTime;
	if (length <= moveDistance)
	{
		pos = target;
		pathIndex++;
	}
	else
	{
		//Print << nor;
		pos += nor * moveDistance;
	}
}

void Enemy::Draw(Vec2& nor)
{
	//if (!isDrawable) return;
	if (nor != Vec2{ 0,0 })
	{
		Rotate(nor);
	}
	hit.center = pos;
	hit.draw(ColorF{ 1,0,0 });
	DebugLogClass::DebugLog(U"isMirror:{}"_fmt(isMirror));
	if (isMirror) looks.mirrored().rotated(0).drawAt(pos, colorF);
	else
	{
	  if(isFliped)	looks.flipped().rotated(angle).drawAt(pos, colorF);
	  else looks.rotated(angle).drawAt(pos, colorF);
	}
	//isDrawable = false;
}

void Enemy::Rotate(Vec2& nor)
{
	double horizontalThreHold = 0.1;
	double verticalThreHold = 0.5;
	auto isLeft = nor.x  < -horizontalThreHold;
	auto isRight = nor.x  > horizontalThreHold;
	auto isUp = nor.y < -verticalThreHold;
	auto isDown = nor.y > verticalThreHold;

	if (isLeft) //左を向く場合
	{
		DebugLogClass::DebugLog(U"Left");
		isMirror = false;
		rlDir = -1;
		angle = 0;
	}
    else if (isRight)//右を向く場合
	{
		DebugLogClass::DebugLog(U"Right");
		isMirror = true;
		rlDir = 1;
		angle = 0;
	}
	else if (isUp)//上向く場合
	{
		angle = Math::HalfPi;
		isMirror = false;
	}
	else if (isDown)//下向く場合
	{
		angle = -Math::HalfPi;
		isMirror = false;
	}
	isFliped = rlDir == 1;//右方向の時には上下反転する必要がある
}

//bool Enemy::DetectPlayerMove()
//{
//	if (player.pos != previousPos)
//	{
//		previousPos = player.pos;
//		return true;
//	}  
//	return false;
//}
