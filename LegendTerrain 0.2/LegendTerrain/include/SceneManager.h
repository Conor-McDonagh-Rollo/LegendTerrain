#pragma once
#include <list>
#include <string>
#include "GameObject.h"

struct Scene {
	Scene(std::string _sc_name) {
		name = _sc_name;
		objects = std::list<std::shared_ptr<GameObject>>();
	}
	std::string name;
	std::list<std::shared_ptr<GameObject>> objects;
};

class SceneManager
{
private:
	std::list<std::shared_ptr<Scene>> scenes;
	static std::shared_ptr<Scene> currentScene;
public:
	SceneManager();
	std::shared_ptr<Scene> AddScene(const char* _name);
	void SetScene(const char* _name);
	std::shared_ptr<Scene> GetScene(const char* _name);
	std::shared_ptr<Scene> GetActiveScene();
	void LoopScene(float dt);
	void AddGameObjectToScene(std::shared_ptr<GameObject>& _obj);
	void RemoveGameObjectFromScene(std::shared_ptr<GameObject>& _obj);
};