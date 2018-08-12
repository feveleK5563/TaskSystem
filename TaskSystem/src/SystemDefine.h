#pragma once
#include <random>
#include <memory>
#include <vector>
#include "Math.h"

namespace SystemDefine
{
	const int windowSizeX(1280);	//ウィンドウサイズX
	const int windowSizeY(720);		//ウィンドウサイズY

	//画面外判定(引数に矩形を指定、画面外に出ていたらtrue)
	bool WindowOutBox(const Math::Box2D& hitBase);
	//画面内判定(引数に矩形を指定、画面内にいたらtrue)
	bool WindowInBox(const Math::Box2D& hitBase);

	//生ポインタを安全にdeleteする
	template<class T> void SafeDelete(T& t);
	//生ポインタを安全にdeleteする(配列版)
	template<class T> void SafeDeleteArr(T& t);

	//範囲内でランダムな値を指定個数分取得する
	int GetRand(int lowerLimit, int upperLimit);
};