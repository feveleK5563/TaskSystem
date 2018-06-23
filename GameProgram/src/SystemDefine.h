#pragma once
#include "Math.h"

class SystemDefine
{
public:
	static const int windowSizeX;	//ウィンドウサイズX
	static const int windowSizeY;	//ウィンドウサイズY

	//画面外判定(引数に矩形を指定、画面外に出ていたらtrue)
	static bool WindowOutBox(const Math::Box2D& hitBase);
	//画面内判定(引数に矩形を指定、画面内にいたらtrue)
	static bool WindowInBox(const Math::Box2D& hitBase);

	//安全にdeleteする
	template<class T> static void SafeDelete(T& t);
	//安全にdeleteする(配列版)
	template<class T> static void SafeDeleteArr(T& t);
};