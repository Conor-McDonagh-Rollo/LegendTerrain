#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GameObject.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Input.h"
#include <iostream>
#include <map>
class Engine;
class Sprite;
class Plane;
class Terrain;
class Shader;

class Engine
{
public:
    Engine(const char* title);

    static std::shared_ptr<Shader> defaultShader;
    static std::unique_ptr<Camera> mainCamera;
    void clearScreen(); 

    GLFWwindow* getWindow() { return window; }

    static Engine& getInstance() {
        return *instance;
    }

    std::shared_ptr<Scene> GetCurrentScene() {
        return sceneMan.GetActiveScene();
    }

    void addObject(std::shared_ptr<GameObject> obj) {
        sceneMan.AddGameObjectToScene(obj);
    }

    void stop()
    {
        glfwSetWindowShouldClose(window, 1);
    }
    void start();
private:

    // settings
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;

    GLFWwindow* window = nullptr;

    std::vector<Shader> shaders;

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    // Static member function for GLFW callback
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    SceneManager sceneMan;
    static Engine* instance;
};



#endif