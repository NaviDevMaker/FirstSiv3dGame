#pragma once
#include <Siv3D.hpp>
#include <unordered_map>

//これでUnityみたいにログ出せるようになる
//staticはインスタンスがないから非staticメンバ変数にはアクセスできない,だからcountMapもstaticにする必要がある
class DebugLogClass
{
public:
    static void DebugLog(const String& message)
	{
		//関数の外に出したくない、でも毎回リセットさせたくないときに使える
		//寿命はプログラム全体だけどスコープは関数内のみ
		//今回の場合はcountをリセットさせたくないから使用
		static std::unordered_map<String, int> countMap;
		static Array<String> messageOrder;
		static Array<Font> fonts;
		static int messageCount;
		if (countMap.contains(message)) countMap[message]++;
		else
		{
			messageOrder << message;
			countMap[message] = 1;
			fonts << Font{ fontSize};
			messageCount++;
		}

		for (auto i = 0; i < messageCount; i++)
		{
			//auto it = countMap.begin();

			//std::unordered_map<String, int>::iterator ってうやつらしい、なんで * と -> 使えるの？
			//イテレータって何？
			//👉 「要素を指すオブジェクト」
			//ポインタにめちゃくちゃ似てるけど別物
			
			//イテレータは内部で
		    //👉 operator*
			//👉 operator->
			//がオーバーロードされてる だから * と　-> が使えるらしい
				

			//std::advance(it, i);
			auto& mes = messageOrder[i];
			auto& count = countMap[mes];//it->second;
			auto pos = Vec2{ 0,fontSize * i };
			
			auto& font = fonts[i];
			// 追加テスト：文字が本来占有しているはずの四角い領域を「赤色の半透明」で塗る
			font(U"{}:x{}"_fmt(mes, count)).region(pos).draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });		
			font(U"{}:x{}"_fmt(mes, count)).draw(pos);
			
		}
	}
   //inline
   //Main.cpp → x
   //Enemy.cpp → x

   //👉 同じ定義 → Ok  もしなかったら      例)Mainのなか　DebugLogClass::fontSize 　　　　Enemyの中　DebugLogClass::fontSize 定義が２個以上あってダメ

   
   //static 単体の場合、cppに定義が必要　static Aの場合→ Example::A = 10; 
	//各ログの時に呼ぶとそれまでのログが消えるから
	/*static void ClearLog()
	{
		ClearPrint();
	}*/
private:
	inline static  int fontSize = 20;
//    static std::unordered_map<String, int> countMap; //外で定義が必要
};

//メモ
//constexpr コンパイル時に値が確定してる必要がある       const 実行時に値が決まってもいいが変更できない　const a = GetValue() みたいなのはOK ちなみにこれがC#との違い
//
