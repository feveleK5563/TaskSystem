#include "Utility.h"
#include <random>
#include <memory>
#include <windows.h>

namespace Utility
{
	std::random_device rd;
	std::mt19937 mtrand(rd());

	//範囲内でランダムな値を取得する(lowerLimit以上upperLimit以下)
	int  GetRand(int lowerLimit, int upperLimit)
	{
		std::uniform_int_distribution<> randRange(lowerLimit, upperLimit);
		return randRange(mtrand);
	}

	Console::Console()
	{
		AllocConsole();
		freopen_s(&in, "CONIN$", "r", stdin);		//標準入力をコンソールにする
		freopen_s(&out, "CONOUT$", "w", stdout);	//標準出力をコンソールにする
	}
	Console::~Console()
	{
		std::fclose(in);
		std::fclose(out);
		FreeConsole();
	}
}