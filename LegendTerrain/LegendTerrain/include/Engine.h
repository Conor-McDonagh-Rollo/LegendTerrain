#ifndef ENGINE_H
#define ENGINE_H

#include "Sprite.h"
#include "Plane.h"
#include <iostream>

class Engine
{
public:
    Engine(const char* title);


    void clearScreen() { // Clear screen to a nice godot blue
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    GLFWwindow* getWindow() { return window; }
private:

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    GLFWwindow* window = nullptr;


    // Static member function for GLFW callback
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};



#endif