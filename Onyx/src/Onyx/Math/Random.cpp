#include "onyxpch.h"
#include "Random.h"

#include <random>
#include <ctime>

namespace Onyx::Math {

	std::mt19937 s_RandomNumberGenerator = std::mt19937(time(0));
	std::uniform_int_distribution<uint32_t> s_RealNumberDistribution = std::uniform_int_distribution<uint32_t>();

	uint32_t Random::NextInt()
	{
		return NextInt(0, INT32_MAX);
	}

	uint32_t Random::NextInt(uint32_t max)
	{
		return NextInt(0, max);
	}

	uint32_t Random::NextInt(uint32_t min, uint32_t max)
	{
		std::uniform_int_distribution<int32_t> distribution(min, max);
		return distribution(s_RandomNumberGenerator);
	}

}
