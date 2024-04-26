#pragma once
#include "FastNoiseLite.h"
#include <random>
#include <iostream>

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
        _noise.SetFrequency(0.2f);

        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(0, std::numeric_limits<int>::max());
        _noise.SetSeed(distr(eng));

        noise = _noise;
    }

    float GetHeight(float x, float y, int octaves = 12, float persistence = 0.5f, float lacunarity = 1.0f) {
        float amplitude = 2.0f;
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

    float GetMaskedHeight(float x, float y, int octaves = 12, float persistence = 0.5f, float lacunarity = 1.0f) {
        float baseHeight = GetHeight(x, y, octaves, persistence, lacunarity);
        float mask = noise.GetNoise(x * 1.5, y * 1.5); // frequency for large features

        if (mask > 0.2) {  // rarity
            float featureHeight = GetHeight(x, y, 3, 0.8f, 1.5f); // settings for pronounced features
            baseHeight += featureHeight * (mask - 0.5) * 4; // scale ^^^
        }

        if (baseHeight < 0.f)
        {
            baseHeight *= 0.1f;
        }

        return baseHeight;
    }
};