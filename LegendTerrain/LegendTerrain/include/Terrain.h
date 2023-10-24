#ifndef TERRAIN_H
#define TERRAIN_H

#include "Plane.h"

class Terrain : public Plane
{
public:
	Terrain(glm::vec3 pos = { 0,0,0 }, int detail = 1);
};

#endif
