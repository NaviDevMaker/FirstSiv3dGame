#pragma once
#include <Siv3D.hpp>
#include <unordered_map>
enum StatusType
{
	Invincible
};

//statusMap[type]の場合はC++の場合、keyがなかったらそれのコントラクタなしで生成する。
// (コンパイルの時点でコードを確認するのかな？その時に)
//となるとconst doubleのあるものが含まれてる場合は初期値を設定しなければならない
//statusMap.at statusMap,find の場合はなかったらエラーが出るだけなのでよい
struct Status
{
	bool isActive;
	const double effectTime;
	double elapsedTime;
};

class PlayerStatusManager
{
public:
	PlayerStatusManager()
	{

	}
	void ActivateFlag(StatusType type);
	bool GetActiveStatus(StatusType type);
	void Update();
private:
	std::unordered_map<StatusType, Status> statusMap
	{
		{StatusType::Invincible,Status{false,5,0}}
	};
	void CountDownStatus();
	void DeactivateFlag(StatusType type);
};

// 注意：unordered_map の operator[] を使うと、
// 指定した key が存在しない場合に「値をデフォルト構築して追加する」挙動になる。
// そのため、Value型（この場合は Status）は「引数なしコンストラクタ」で生成できる必要がある。
//
// 今回の Status は
//     const double effectTime;
// を持っており、初期値がないためデフォルト構築（Status()）ができない。
// その結果、operator[] 内部での生成処理が成立せずコンパイルエラーになる。
//
// 重要なのは、今回 Invincible は初期化時に map に入れているが、
// 「実行時に必ず存在する」ことと「operator[] が要求する仕様」は別という点。
// operator[] は「存在しない場合の生成処理」も含めてコンパイルされるため、
// 実際にその分岐に入らなくてもエラーになる。
//
// そのため、本クラスでは operator[] は使わず、
// 既に存在する前提でアクセスする at() を使用している。
// at() は存在しない場合に例外を投げるだけで、新規生成を行わないため安全。
