#pragma once
#include "FastNoiseLite.h"
#include <random>

class Noise {
public:
	Noise()
	{
		instance = this;
	}

	void Load()
	{
		FastNoiseLite _noise;
		_noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
		_noise.SetFrequency(1);

		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, std::numeric_limits<int>::max());
		_noise.SetSeed(distr(eng));

		noise = _noise;
	}

	FastNoiseLite noise;
	static Noise* instance;
};