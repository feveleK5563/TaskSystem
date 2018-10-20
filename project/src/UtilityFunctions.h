#pragma once

namespace UTIL
{
	//生ポインタを安全にdeleteする
	template<class T>void SafeDelete(T& t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}

	//生ポインタを安全にdeleteする(配列版)
	template<class T>void SafeDeleteArr(T& t)
	{
		if (t != nullptr)
		{
			delete[] t;
			t = nullptr;
		}
	}

	//範囲内でランダムな値を指定個数分取得する
	int GetRand(int lowerLimit, int upperLimit);
}