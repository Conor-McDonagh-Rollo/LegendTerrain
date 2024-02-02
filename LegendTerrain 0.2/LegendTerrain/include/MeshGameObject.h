#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "MeshShape.h"

class MeshGameObject : public GameObject 
{
public:
	MeshGameObject(MeshShape ms)
		:	mesh{ms.vertices, ms.indices}
	{

	}

private:
	Mesh mesh;
};