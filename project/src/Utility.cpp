#include "Utility.h"
#include <random>
#include <memory>
#include <windows.h>

namespace Util
{
    std::random_device rd;
    std::mt19937 mtrand(rd());

    //範囲内でランダムな値を取得する(lowerLimit以上upperLimit以下)
    int GetRand(int lower_limit, int upper_limit)
    {
        std::uniform_int_distribution<> randRange(lower_limit, upper_limit);
        return randRange(mtrand);
    }

    Console::Console()
    {
        AllocConsole();
        freopen_s(&in_, "CONIN$", "r", stdin);      //標準入力をコンソールにする
        freopen_s(&out_, "CONOUT$", "w", stdout);   //標準出力をコンソールにする
    }
    Console::~Console()
    {
        std::fclose(in_);
        std::fclose(out_);
        FreeConsole();
    }
}