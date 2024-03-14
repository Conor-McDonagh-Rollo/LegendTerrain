#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "Window.h"
#include "GameObject.h"
#include "MeshGameObject.h"
#include "SceneManager.h"
#include "Camera.h"
#include <iostream>

class Engine {
private:
    SceneManager sceneMan;
    static std::unique_ptr<Engine> instance;


    std::unique_ptr<Window> mainWindow;

    void clearScreen()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainCamera->ProcessMouseMovement(Input::GetMousePosition(), false);

        glm::mat4 viewtest = mainCamera->GetViewMatrix();
        glm::mat4 projectiontest = mainCamera->GetProjectionMatrix();
        defaultShader->SetUniform("view", viewtest);
        defaultShader->SetUniform("projection", projectiontest);
    }

public:
    Engine();

    static std::shared_ptr<Shader> defaultShader;
    static std::unique_ptr<Camera> mainCamera;

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

        defaultShader = std::make_shared<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

        mainCamera = std::make_unique<Camera>(sizeX, sizeY, glm::vec3(0, 2, 2));
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
                clearScreen();

                sceneMan.LoopScene(deltaTime);

                Input::Update();
                mainWindow->swapBuffers(); // only swap buffers at 60 FPS
            }

        }

    }
};