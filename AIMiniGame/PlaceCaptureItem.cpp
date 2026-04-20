#include "PlaceCaptureItem.hpp"
#include "Enemy.hpp"
#include "CaptureEffect.hpp"
//内部でCaptureEffectを生成するのでincludeが必要

void PlaceCaptureItem::Update(Array<Enemy>& enemys,Effect& effect)
{
	if (isUsed) return;
	CaptureEnemy(enemys,effect);
	Draw();
}

void PlaceCaptureItem::Draw()
{
	hit.center = spawnPos;
	hit.draw(ColorF{1,0,0});
	looks.drawAt(spawnPos);
}

void PlaceCaptureItem::CaptureEnemy(Array<Enemy>& enemys,Effect& effect)
{
	for(int32 i = static_cast<int32>(enemys.size()) - 1;i >= 0 ;i--)
	{
		auto& enemy = enemys[i];
		if (hit.intersects(enemy.hit))
		{
			//エフェクトの生成
			effect.add<CaptureEffect>(spawnPos);
			enemys.remove_at(i);
			isUsed = true;
			break;
		}
	}
}
