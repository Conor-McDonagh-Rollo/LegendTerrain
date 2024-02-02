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

        windows.push_back(this);

        Input::Initialize(window);
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