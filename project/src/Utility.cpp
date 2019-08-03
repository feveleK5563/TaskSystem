#include "Utility.h"
#include <windows.h>

namespace Util
{
    Console::Console()
    {
        AllocConsole();
        freopen_s(&in_, "CONIN$", "r", stdin);      // 標準入力をコンソールにする
        freopen_s(&out_, "CONOUT$", "w", stdout);   // 標準出力をコンソールにする
    }
    Console::~Console()
    {
        std::fclose(in_);
        std::fclose(out_);
        FreeConsole();
    }
}