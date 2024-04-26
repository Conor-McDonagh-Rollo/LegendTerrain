#pragma once
#include "FastNoiseLite.h"
#include <random>

class Noise {
public:
    FastNoiseLite noise;
    static Noise* instance;

    Noise() {
        instance = this;
    }

    void Load() {
        FastNoiseLite _noise;
        _noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        _noise.SetFrequency(0.3f);

        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(0, std::numeric_limits<int>::max());
        _noise.SetSeed(distr(eng));

        noise = _noise;
    }

    float GetHeight(float x, float y, int octaves = 12, float persistence = 0.5f, float lacunarity = 1.0f) {
        float amplitude = 1.0f;
        float frequency = 1.0f;
        float noiseHeight = 0.0f;

        for (int i = 0; i < octaves; i++) {
            float sampleX = x * frequency;
            float sampleY = y * frequency;
            float singleOctaveNoise = noise.GetNoise(sampleX, sampleY);
            noiseHeight += singleOctaveNoise * amplitude;

            amplitude *= persistence;
            frequency *= lacunarity;
        }

        return noiseHeight;
    }
};