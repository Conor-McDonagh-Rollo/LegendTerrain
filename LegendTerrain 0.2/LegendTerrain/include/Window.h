#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../include/Input.h"

class Window {
private:
    GLFWwindow* window;
    static std::vector<Window*> windows;

public:
    Window(int width, int height, const std::string& title) {
        if (windows.empty()) {
            if (!glfwInit()) {
                throw std::runtime_error("Failed to initialize GLFW");
            }
            
        }

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            if (windows.empty()) {
                glfwTerminate();
            }
            throw std::runtime_error("Failed to create GLFW window");
        }

        Input::Initialize(window);
        /*
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        glfwWindowHint(GLFW_ALPHA_BITS, 8); // 8 bits for the alpha channel
        glfwWindowHint(GLFW_DEPTH_BITS, 24); // 24 bits for the depth buffer
        glfwWindowHint(GLFW_STENCIL_BITS, 8); // 8 bits for the stencil buffer

        // Set clear color (fully transparent black)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        // Enable blending for alpha transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Z indexing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        */

        windows.push_back(this);
    }

    ~Window() {
        auto it = std::find(windows.begin(), windows.end(), this);
        if (it != windows.end()) {
            windows.erase(it);
        }
        glfwDestroyWindow(window);

        if (windows.empty()) {
            glfwTerminate();
        }
    }

    void makeContextCurrent() {
        glfwMakeContextCurrent(window);
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(window);
    }

    void swapBuffers() {
        glfwSwapBuffers(window);
    }

    static void pollEvents() {
        glfwPollEvents();
    }

    static bool isContextCurrent(const Window& wnd) {
        return glfwGetCurrentContext() == wnd.window;
    }

    static bool hasOpenWindows() {
        return !windows.empty();
    }
};