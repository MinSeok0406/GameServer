#pragma once
#include <random>

class Utils
{
public:
	template<typename T>
	static T GetRandom(T min, T max)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());

		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> distrubution(min, max);
			return distrubution(generator);
		}
		else
		{
			std::uniform_real_distribution<T> distrubution(min, max);
			return distrubution(generator);
		}
	}
};

