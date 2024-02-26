#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "Window.h"
#include "GameObject.h"
#include "MeshGameObject.h"
#include "SceneManager.h"
#include <iostream>

class Engine {
private:
    SceneManager sceneMan;
    static std::unique_ptr<Engine> instance;


    std::unique_ptr<Window> mainWindow;

public:
    Engine();

    static std::unique_ptr<Engine>& getInstance() {
        return instance;
    }

    std::shared_ptr<Scene> GetCurrentScene() {
        return sceneMan.GetActiveScene();
    }

    void addObject(std::shared_ptr<GameObject> obj) {
        sceneMan.AddGameObjectToScene(obj);
    }

    static void load(int sizeX, int sizeY, const char* title)
    {
        Engine::instance = std::make_unique<Engine>();
        instance->mainWindow = std::make_unique<Window>(sizeX, sizeY, title);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            // Handle GLAD initialization failure
        }
        // Set clear color (fully transparent black)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // Enable blending for alpha transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Z indexing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
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
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                sceneMan.LoopScene(deltaTime);

                Input::Update();
                mainWindow->swapBuffers(); // only swap buffers at 60 FPS
            }

        }

    }
};