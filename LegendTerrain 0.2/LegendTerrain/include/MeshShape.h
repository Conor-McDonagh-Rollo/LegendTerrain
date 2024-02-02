#pragma once
#include "Types.h"
#include <vector>

struct MeshShape {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};