#include "../include/SceneManager.h"
std::shared_ptr<Scene> SceneManager::currentScene;

SceneManager::SceneManager()
{
	AddScene("Default");
	if (!scenes.empty()) {
		if (scenes.front()->name == "Default")
		{
			SetScene("Default");
		}
		else
		{

		}
	}
	else {
		// handle errors
	}
}

std::shared_ptr<Scene> SceneManager::AddScene(const char* _name)
{
	auto newScene = std::make_shared<Scene>(std::string(_name));
	scenes.push_back(newScene);
	return newScene;
}

void SceneManager::SetScene(const char* _name)
{
	currentScene = GetScene(_name);
	for (auto& obj : currentScene->objects) {
		obj->awake();
		obj->start();
	}

}

std::shared_ptr<Scene> SceneManager::GetScene(const char* _name)
{
	auto it = std::find_if(scenes.begin(), scenes.end(), [&](std::shared_ptr<Scene> scene) { return scene->name == _name; });
	if (it != scenes.end())
	{
		std::shared_ptr<Scene> foundScene = *it;
		return foundScene;
	}
	return *scenes.begin();
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return currentScene;
}

void SceneManager::AddGameObjectToScene(std::shared_ptr<GameObject>& _obj)
{
	currentScene->objects.push_back(_obj);
	_obj->on_object_add();
}

void SceneManager::LoopScene(float dt)
{
	for (auto& obj : currentScene->objects) {
		obj->update(dt);
		obj->render();
	}
}

void SceneManager::RemoveGameObjectFromScene(std::shared_ptr<GameObject>& _obj)
{
	_obj->on_object_remove();
	currentScene->objects.remove_if([&](std::shared_ptr<GameObject>& objToFind) { return objToFind->name == _obj->name; });
}
