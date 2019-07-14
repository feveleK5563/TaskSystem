#include "Utility.h"
#include <random>
#include <memory>
#include <windows.h>

namespace Util
{
    std::random_device rd;
    std::mt19937 mtrand(rd());

    //�͈͓��Ń����_���Ȓl���擾����(lowerLimit�ȏ�upperLimit�ȉ�)
    int GetRand(int lower_limit, int upper_limit)
    {
        std::uniform_int_distribution<> randRange(lower_limit, upper_limit);
        return randRange(mtrand);
    }

    Console::Console()
    {
        AllocConsole();
        freopen_s(&in_, "CONIN$", "r", stdin);      //�W�����͂��R���\�[���ɂ���
        freopen_s(&out_, "CONOUT$", "w", stdout);   //�W���o�͂��R���\�[���ɂ���
    }
    Console::~Console()
    {
        std::fclose(in_);
        std::fclose(out_);
        FreeConsole();
    }
}