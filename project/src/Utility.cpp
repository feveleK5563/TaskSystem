#include "Utility.h"
#include <random>
#include <memory>
#include <windows.h>

namespace Utility
{
	std::random_device rd;
	std::mt19937 mtrand(rd());

	//�͈͓��Ń����_���Ȓl���擾����(lowerLimit�ȏ�upperLimit�ȉ�)
	int  GetRand(int lowerLimit, int upperLimit)
	{
		std::uniform_int_distribution<> randRange(lowerLimit, upperLimit);
		return randRange(mtrand);
	}

	Console::Console()
	{
		AllocConsole();
		freopen_s(&in, "CONIN$", "r", stdin);		//�W�����͂��R���\�[���ɂ���
		freopen_s(&out, "CONOUT$", "w", stdout);	//�W���o�͂��R���\�[���ɂ���
	}
	Console::~Console()
	{
		std::fclose(in);
		std::fclose(out);
		FreeConsole();
	}
}