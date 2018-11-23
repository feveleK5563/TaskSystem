#pragma once
#include <cstdio>
#include <iostream>

//以下のマクロの作成者はtonarinohitoなので問題があったらtonarinohitoのせい
#ifdef _DEBUG
//デバッグ時にコンソールを表示する
#define ShowConsole() Utility::Console c
//デバッグ時にコンソール画面へ出力
#define DOUT std::cout
//ファイル名と行数をコンソール画面へ出力
#define FILE_AND_LINE std::cout << __FILE__ << ":" << __LINE__ << std::endl

#else
//デバッグ用のあれこれを無視する
#define NDEBUG	//assert無効
#define ShowConsole() __noop
#define DOUT false && std::cout
#define FILE_AND_LINE false

#endif
#include <assert.h>


namespace Utility
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

	//範囲内でランダムな値を取得する
	int GetRand(int lowerLimit, int upperLimit);

	//コンソール画面を出し、cout,cinを許可する
	class Console final
	{
	private:
		std::FILE* in;
		std::FILE* out;

	public:
		Console();
		~Console();
	};
}