#pragma once
#include <vector>
#include <memory>
#include "Window.h"
#include "GameObject.h"

class Engine {
private:
    std::vector<std::shared_ptr<GameObject>> objects;
    static Engine instance;

    Engine() = default;

    std::unique_ptr<Window> mainWindow;

public:
    static Engine& getInstance() {
        return instance;
    }

    void addObject(std::shared_ptr<GameObject> obj) {
        objects.push_back(obj);
    }

    void start(int sizeX, int sizeY, const char* title)
    {
        mainWindow = std::make_unique<Window>(sizeX, sizeY, title);

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

                for (auto& obj : objects) {
                    obj->update(deltaTime);
                    obj->render();
                }

                Input::Update();
                mainWindow->swapBuffers(); // only swap buffers at 60 FPS
            }

        }

    }
};