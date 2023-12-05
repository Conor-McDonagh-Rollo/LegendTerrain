#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Object.h"
#include "Camera.h"
#include <iostream>
class Engine;
class Sprite;
class Plane;
class Terrain;
class Shader;

class Engine
{
public:
    Engine(const char* title);

    Camera* getCamera() { return mainCamera; }
    void clearScreen(); 

    GLFWwindow* getWindow() { return window; }

    Object* makeTerrain(int detail = 5, glm::vec3 position = { 0,0,0 });
    Object* makePlane(const char* texture = "assets/defaults/default_texture.jpg", glm::vec3 position = {0,0,0});
    Object* makeSprite(const char* texture = "assets/defaults/default_texture.jpg", glm::vec3 position = { 0,0,0 });
private:

    // settings
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;

    GLFWwindow* window = nullptr;
    static Camera* mainCamera;

    std::vector<Shader> shaders;

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    // Static member function for GLFW callback
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};



#endif