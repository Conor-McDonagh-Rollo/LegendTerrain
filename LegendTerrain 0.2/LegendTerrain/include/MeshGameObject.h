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

	void SetTexture(std::string path) {
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->Set(path);
		mesh.SetTexture(texture);
	}

	void SetShader(std::string vertex_s, std::string frag_s) {
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertex_s, frag_s);
		mesh.SetShader(shader);
	}

private:
	Mesh mesh;
};