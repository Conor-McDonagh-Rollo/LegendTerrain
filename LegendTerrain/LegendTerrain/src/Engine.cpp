#include "../include/Engine.h"

Engine::Engine(const char* title)
{
    // glfw: initialize and configure
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        // Handle initialization failure
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    glfwWindowHint(GLFW_ALPHA_BITS, 8); // 8 bits for the alpha channel
    glfwWindowHint(GLFW_DEPTH_BITS, 24); // 24 bits for the depth buffer
    glfwWindowHint(GLFW_STENCIL_BITS, 8); // 8 bits for the stencil buffer

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // Handle window creation failure
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
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
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}