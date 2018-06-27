#include "SystemDefine.h"

const int SystemDefine::windowSizeX = 1280;	//ウィンドウサイズX
const int SystemDefine::windowSizeY = 720;	//ウィンドウサイズY

//画面外判定(引数に画像サイズを指定、画面外に出ていたらtrue)
bool SystemDefine::WindowOutBox(const Math::Box2D& hitBase)
{
	Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
	return !windowBox.Hit(hitBase);
}

//画面内判定(引数に画像サイズを指定、画面内にいたらtrue)
bool SystemDefine::WindowInBox(const Math::Box2D& hitBase)
{
	Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
	return windowBox.In(hitBase);
}

//安全にdeleteする
template<class T>void SystemDefine::SafeDelete(T& t)
{
	if (t != nullptr)
	{
		delete t;
		t = nullptr;
	}
}

//安全にdeleteする(配列版)
template<class T>void SystemDefine::SafeDeleteArr(T& t)
{
	if (t != nullptr)
	{
		delete[] t;
		t = nullptr;
	}
}