#include "SystemDefine.h"

namespace SystemDefine
{
	//画面外判定(引数に画像サイズを指定、画面外に出ていたらtrue)
	bool SystemDefine::WindowOutBox(const Math::Box2D& hitBase)
	{
		Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
		return !windowBox.IsHit(hitBase);
	}

	//画面内判定(引数に画像サイズを指定、画面内にいたらtrue)
	bool SystemDefine::WindowInBox(const Math::Box2D& hitBase)
	{
		Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
		return windowBox.IsIn(hitBase);
	}

	//生ポインタを安全にdeleteする
	template<class T>void SystemDefine::SafeDelete(T& t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}

	//生ポインタを安全にdeleteする(配列版)
	template<class T>void SystemDefine::SafeDeleteArr(T& t)
	{
		if (t != nullptr)
		{
			delete[] t;
			t = nullptr;
		}
	}

	std::random_device rd;
	std::mt19937 mtrand(rd());

	//範囲内でランダムな値を指定個数分取得する
	int  SystemDefine::GetRand(int lowerLimit, int upperLimit)
	{
		std::uniform_int_distribution<> randRange(lowerLimit, upperLimit);
		return randRange(mtrand);
	}
}