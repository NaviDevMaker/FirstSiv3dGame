#pragma once
#include <Siv3D.hpp>
#include "StageEnemyInfo.hpp"
#include "ItemInfo.hpp"

//各ステージのデータを格納
//struct ItemInfo;//classとの違いはデフォルトがpublic か　privateとかだから前方宣言OK
//struct StageEnemyInfo;

enum class EnemyType;
class StageData
{
public:
	//一時オブジェクト渡すからconstを忘れないでね、ここポイント
	StageData(const Texture& background,const StageEnemyInfo& stageEnemyInfo
	          ,const ItemInfo& cheeseItemInfo,const ItemInfo& captureItemInfo
			  ,int32 targetScore)
		:background{background}
		,stageEnemyInfo{stageEnemyInfo}
		,cheeseItemInfo{cheeseItemInfo}
		,captureItemInfo{captureItemInfo}
		,targetScore{targetScore}
	{ }
	const ItemInfo& GetCheeseItemInfo() const { return cheeseItemInfo; };
	const ItemInfo& GetCaptureItemInfo() const { return captureItemInfo; };
	const StageEnemyInfo& GetStageEnemyInfo() const { return stageEnemyInfo; };
	const Texture& GetBattleTexture() const { return background; };
	int32 GetTargetScore() const { return targetScore; };
private:
	//Texture はSiv3D側で中身を共有する作りなので、コピーしても巨大画像を毎回丸ごと複製する感覚ではない。
	//だから StageData に値で持たせてOK。

	Texture background;	

	//const T&は　&に入れることができないから&はいらない。また、今回の構造体はdoubleやintといった軽い値なのでこちらで持ってて問題ない
	StageEnemyInfo stageEnemyInfo;
	ItemInfo cheeseItemInfo;
	ItemInfo captureItemInfo;
	int32 targetScore;
};
