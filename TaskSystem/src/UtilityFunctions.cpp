#include "UtilityFunctions.h"
#include <random>
#include <memory>

namespace UTIL
{
	std::random_device rd;
	std::mt19937 mtrand(rd());

	//”ÍˆÍ“à‚Åƒ‰ƒ“ƒ_ƒ€‚È’l‚ğw’èŒÂ”•ªæ“¾‚·‚é(lowerLimitˆÈãupperLimitˆÈ‰º)
	int  GetRand(int lowerLimit, int upperLimit)
	{
		std::uniform_int_distribution<> randRange(lowerLimit, upperLimit);
		return randRange(mtrand);
	}
}