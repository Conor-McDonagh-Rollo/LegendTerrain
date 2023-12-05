#ifndef TERRAIN_H
#define TERRAIN_H

#include "Textured_Object.h"
#include "../dependencies/PerlinNoise.hpp"

class Terrain : public Textured_Object
{
public:
	Terrain(glm::vec3 pos = { 0,0,0 }, int detail = 1);
	void DisplaceVerticies();

	const siv::PerlinNoise::seed_type seed = 123456u;
	const siv::PerlinNoise perlin{ seed };
};

#endif
