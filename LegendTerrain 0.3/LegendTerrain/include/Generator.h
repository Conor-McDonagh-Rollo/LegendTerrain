#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include "Terrain.h"
#include "Camera.h"
#include <map>

class Generator : public GameObject
{
public:
	Generator();
	void run();

private:
	void update(float dt) override;
	void generateTerrain(const glm::vec3& position);

	std::vector<std::shared_ptr<Terrain>> terrain;
	std::map<std::pair<int, int>, bool> currentTerrain;

	Camera* mainCamera = nullptr;
	const int GEN_DIST = 2;
};

#endif