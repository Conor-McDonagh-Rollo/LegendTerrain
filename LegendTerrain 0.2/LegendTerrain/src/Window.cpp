#include "../include/Window.h"

std::vector<Window*> Window::windows;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const std::string& title) {
    if (windows.empty()) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_ALPHA_BITS, 8); // 8 bits for the alpha channel
    glfwWindowHint(GLFW_DEPTH_BITS, 24); // 24 bits for the depth buffer
    glfwWindowHint(GLFW_STENCIL_BITS, 8); // 8 bits for the stencil buffer

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        if (windows.empty()) {
            glfwTerminate();
        }
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    

    Input::Initialize(window);

    windows.push_back(this);
}