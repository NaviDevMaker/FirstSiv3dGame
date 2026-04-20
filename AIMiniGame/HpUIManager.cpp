#include "HpUIManager.hpp"
//
//void HpUIManager::UpdateHpUI(int* hp) const
//{
//	//引数で受け取ったアドレスの実体（*hp）をこのクラスのhpに代入
//	this -> hp = *hp;
//}

void HpUIManager::Update() const
{
	font(U"HP:{}"_fmt(hp)).draw(50, 120);
}
