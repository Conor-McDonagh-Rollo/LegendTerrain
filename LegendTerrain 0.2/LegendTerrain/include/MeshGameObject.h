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

	void Move(const glm::vec3& delta) {
		position += delta;
		mesh.SetPosition(position);
	}

	void Rotate(const glm::vec3& delta) {
		rotation += delta;
		mesh.SetRotation(rotation);
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

	void SetShader(std::shared_ptr<Shader> shader) {
		mesh.SetShader(shader);
	}

	void render() override {
		mesh.Draw();
	}

	glm::vec3 GetPosition() { return position; }



	void awake() override {};
	void start() override {};
	void update(float dt) override {};
	void on_object_add() override {};
	void on_object_remove() override {};

private:
	glm::vec3 position = {0,0,0};
	glm::vec3 rotation = {0,0,0};
	Mesh mesh;
};