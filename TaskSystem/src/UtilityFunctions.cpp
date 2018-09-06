#include "UtilityFunctions.h"
#include <random>
#include <memory>

namespace UTIL
{
	std::random_device rd;
	std::mt19937 mtrand(rd());

	//�͈͓��Ń����_���Ȓl���w������擾����(lowerLimit�ȏ�upperLimit�ȉ�)
	int  GetRand(int lowerLimit, int upperLimit)
	{
		std::uniform_int_distribution<> randRange(lowerLimit, upperLimit);
		return randRange(mtrand);
	}
}