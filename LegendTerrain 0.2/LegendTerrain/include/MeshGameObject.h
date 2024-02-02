#pragma once
#include "GameObject.h"
#include "Mesh.h"

class MeshGameObject : public GameObject 
{
public:
	MeshGameObject();

private:
	Mesh mesh;
};