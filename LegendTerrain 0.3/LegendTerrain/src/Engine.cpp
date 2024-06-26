#include "../include/Engine.h"
#include "../include/Shader.h"
Engine* Engine::instance = nullptr;
std::unique_ptr<Camera> Engine::mainCamera = nullptr;
std::shared_ptr<Shader> Engine::defaultShader = nullptr;

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

    // Z indexing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    shaders.push_back(Shader());

    Engine::mainCamera = std::make_unique<Camera>(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0, 2, 2));

    Engine::instance = this;
    defaultShader = std::make_shared<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

    Input::Initialize(window, SCR_WIDTH, SCR_HEIGHT, mainCamera.get());
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Engine::start()
{
    float targetFrameTime = 1.0 / 60.0; // 60 FPS
    float lastFrameTime = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // process input as fast as we can
        glfwPollEvents();

        if (deltaTime < targetFrameTime) {
            clearScreen();

            sceneMan.LoopScene(deltaTime);

            Input::Update();
            glfwSwapBuffers(window); // only swap buffers at 60 FPS
        }

    }
}

void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    
}

void Engine::clearScreen()
{
    glClearColor(0.659f, 0.969f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 viewtest = mainCamera->GetViewMatrix();
    glm::mat4 projectiontest = mainCamera->GetProjectionMatrix();
    shaders[0].setMat4("view", viewtest);
    shaders[0].setMat4("projection", projectiontest);
}