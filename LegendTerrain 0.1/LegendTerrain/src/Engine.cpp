#include "../include/Engine.h"

#include "../include/Sprite.h"
#include "../include/Plane.h"
#include "../include/Terrain.h"
#include "../include/Mesh.h"

Camera* Engine::mainCamera = nullptr;

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

    mainCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0, 2, 2));
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX = 800.0f / 2.0; // Set to window width divided by 2
    static float lastY = 600.0f / 2.0; // Set to window height divided by 2
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top

    lastX = xpos;
    lastY = ypos;

    mainCamera->ProcessMouseMovement(xoffset, yoffset);
}

void Engine::clearScreen()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    // Temporary: Set the View and Projection matrices
    glm::mat4 view = glm::lookAt(
        // Camera position in World Space
        glm::vec3(0, 4, 1),
        // and looks at the origin
        glm::vec3(0, 0, 0),
        // Head is up (set to 0,-1,0 to look upside-down)
        glm::vec3(0, 1, 0)
    );
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // 45-degree FOV, 4:3 aspect ratio, near clip 0.1, far clip 100
    shaders[0].setMat4("view", view);
    shaders[0].setMat4("projection", projection);
    */
    glm::mat4 viewtest = mainCamera->GetViewMatrix();
    glm::mat4 projectiontest = mainCamera->GetProjectionMatrix();
    shaders[0].setMat4("view", viewtest);
    shaders[0].setMat4("projection", projectiontest);
}

Object* Engine::makeTerrain(int detail, glm::vec3 position)
{
    Terrain* result = new Terrain(position, detail);
    result->setShader(shaders[0]);
    return result;
}

Object* Engine::makePlane(const char* texture, glm::vec3 position)
{
    Plane* result = new Plane(position, texture);
    result->setShader(shaders[0]);
    return result;
}

Object* Engine::makeSprite(const char* texture, glm::vec3 position)
{
    Sprite* result = new Sprite(position, texture);
    result->setShader(shaders[0]);
    return result;
}

Object* Engine::makeMesh(const char* path)
{
    Mesh* result = new Mesh(path, {0,0,0});
    result->setShader(shaders[0]);
    return result;
}