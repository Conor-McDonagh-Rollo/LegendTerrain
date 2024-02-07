#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "Window.h"
#include "GameObject.h"
#include "MeshGameObject.h"
#include "SceneManager.h"

class Engine {
private:
    SceneManager sceneMan;
    static Engine instance;

    Engine();

    std::unique_ptr<Window> mainWindow;

public:
    static Engine& getInstance() {
        return instance;
    }

    std::shared_ptr<Scene> GetCurrentScene() {
        return sceneMan.GetActiveScene();
    }

    void addObject(std::shared_ptr<GameObject> obj) {
        sceneMan.AddGameObjectToScene(obj);
    }

    void load(int sizeX, int sizeY, const char* title)
    {
        mainWindow = std::make_unique<Window>(sizeX, sizeY, title);
    }

    void start()
    {

        float targetFrameTime = 1.0 / 60.0; // 60 FPS
        float lastFrameTime = 0.0;

        while (!mainWindow->shouldClose())
        {
            // Calculate delta time
            float currentTime = glfwGetTime();
            float deltaTime = currentTime - lastFrameTime;
            lastFrameTime = currentTime;

            // process input as fast as we can
            mainWindow->pollEvents();

            if (deltaTime < targetFrameTime) {

                sceneMan.LoopScene(deltaTime);

                Input::Update();
                mainWindow->swapBuffers(); // only swap buffers at 60 FPS
            }

        }

    }
};